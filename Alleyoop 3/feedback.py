# -*- coding: utf-8 -*-

from alp.request.requests.exceptions import ConnectionError
from sqlite3 import IntegrityError
import time
import alp
from alp.item import Item as I
import os
import json
import threading
import codecs


class OopThread(threading.Thread):
    def __init__(self, target_url, forced, candidict, local):
        self.target_url = target_url
        self.forced = forced
        self.candidict = candidict
        self.local = local
        self.result = dict(json=None, candidict=self.candidict)
        threading.Thread.__init__(self)

    def run(self):
        try:
            r = alp.Request(self.target_url, cache=False)
        except (IntegrityError, ConnectionError) as e:
            alp.log("Connection to {0} raised exception: {1}.".format(self.target_url, e))
            return
        else:
            if not self.forced:
                r.download()
            else:
                r.clear_cache()
            try:
                j = r.request.json()
            except Exception as e:
                alp.log("{0} threw exception {1}.".format(self.target_url, e))
                return
            self.result = dict(json=r.request.json(), candidict=self.candidict, local=self.local)


def manage_threads(threads, running_results=[]):
    next_threads = []
    for t in threads:
        if t.is_alive():
            next_threads.append(t)
            continue
        running_results.append(t.result)
    threads = next_threads

    if len(threads):
        time.sleep(1)
        manage_threads(threads, running_results)
        return

    print_feedback(running_results)

def do_feedback():
    q = alp.args()
    flowPath = os.path.split(alp.local())[0]
    cache = alp.jsonLoad("cache.json", default={})
    day_secs = 24 * 60 * 60
    force = (len(q) > 0 and q[0] == "|force|")
    t = time.time()
    if (force):
        import shutil
        _c = alp.cache()
        _s = alp.storage()
        shutil.rmtree(_c)
        shutil.rmtree(_s)

    if (cache.get("cache_time", 0) + day_secs > t) and not force:
        candidates = cache.get("cached_workflows", [])
    else:
        candidates = []
        for dirpath, dirnames, filenames in os.walk(flowPath, topdown=False, followlinks=True):
            for aFile in filenames:
                if aFile == "update.json":
                    try:
                        fn = os.path.join(dirpath, "Info.plist")
                        if not os.path.exists(fn):
                            fn = os.path.join(dirpath, "info.plist")

                        plist = alp.readPlist(fn)
                    except IOError as e:
                        alp.log("Exception: Info.plist not found ({0}).".format(e))
                        continue
                    else:
                        name = plist["name"]
                        local_description = plist["description"]
                        the_json = os.path.join(dirpath, aFile)
                        the_icon = os.path.join(dirpath, "icon.png")
                        if name != "Alleyoop":
                            candidates.append(dict(name=name, json=the_json,
                                icon=the_icon, path=dirpath,
                                description=local_description))
                        else:
                            downloads_path = os.path.expanduser("~/Downloads/")
                            candidates.append(dict(name=name, json=the_json,
                                icon=the_icon, path=downloads_path,
                                description=local_description))
        new_cache = dict(cache_time=t, cached_workflows=candidates)
        alp.jsonDump(new_cache, "cache.json")

    threads = []
    for candidict in candidates:
        try:
            with codecs.open(candidict["json"]) as f:
                local = json.load(f, encoding="utf-8")
        except Exception as e:
            alp.log("{0} may no longer exist: {1}".format(candidict["name"], e))
            continue

        ot = OopThread(local['remote_json'], force, candidict, local)
        threads.append(ot)
        ot.start()
    manage_threads(threads)

def print_feedback(results):
    updatables = []
    all_configured = []
    for r in results:
        try:
            j = r['json']
            d = r['candidict']
            l = r['local']
        except Exception as e:
            alp.log("{0} threw exception {1}".format(d['name'], e))
            alp.log(r)
        try:
            version = float(j['version'])
            download_uri = j['download_url']
            description = j['description']
        except Exception as e:
            alp.log("{0} failed with error: {1}".format(d['name'], e))
            continue
        try:
            lv = l['version']
        except Exception as e:
            alp.log("{0} failed with malformed json: {1}".format(d['name'], e))
            alp.log(d)
            continue
        if lv < version:
            updatables.append(dict(name=d['name'], description=description, icon=d['icon'],
                                    download=download_uri, path=d['path'], version=version))
        all_configured.append(dict(name=d['name'], description=description, icon=d['icon'],
                                    download=download_uri, path=d['path'], version=version,
                                    local_d=d['description']))

    items = []
    q = alp.args()
    if not len(q) or (len(q) == 1 and q[0] == "|force|"):
        if not len(updatables):
            alp.feedback(I(title="No Updates Available",
                            subtitle="All your workflows are up-to-date.",
                            valid=False))
            return
        update_all = '"update-all"'
        for updict in updatables:
            update_all += " \"{0}>{1}>{2}\"".format(updict['name'], updict['path'],
                                                    updict['download'])
        n = len(updatables)
        upd_sib = "s" if n != 1 else ""
        items.append(I(title="Update All", subtitle="Download {0} update{s}".format(n, s=upd_sib),
                        valid=True, arg=update_all))
        for up in updatables:
            items.append(I(title=up['name'], subtitle=u"v{0}\u2014{1}".format(up['version'], up['description']),
                            icon=up['icon'], arg=u"\"update\" \"{0}>{1}>{2}\"".format(up['name'], up['path'], up['download']),
                            valid=True))
    elif len(q) == 1 and q[0] == "|all|":
        if not len(all_configured):
            alp.feedback(I(title="No Compatible Workflows", subtitle="No Alleyoop workflows detected",
                            valid=False))
            return
        for c in all_configured:
            items.append(I(title=c['name'], subtitle=u"v{0}\u2014{1}".format(c['version'], c['local_d']),
                            icon=c['icon'], valid=False))
    else:
        if q[0] != "|all|" and q[0] != "|force|":
            if not len(results):
                alp.log("'oop' may be broken.")
                alp.log("len(all_configured)=0")
                alp.log("q='{0}'".format(q))
                alp.log("updatables='{0}'".format(updatables))
                alp.log("results='{0}'".format(results))
                alp.feedback(I(title="Error", subtitle="No compatible workflows were found. See debug.log for info.",
                                valid=False))
                return

            search = q[0]
            results = alp.fuzzy_search(search, updatables, key=lambda x: u"{0} - {1}".format(x['name'], x['local_d']))
            for r in results:
                items.append(I(title=r['name'], subtitle=u"v{0}\u2014{1}".format(r['version'], r['description']),
                                icon=r['icon'], arg="\"update\" \"{0}>{1}>{2}".format(r['name'], r['path'], r['download']),
                                valid=True))
        else:
            if not len(all_configured):
                alp.log("'oop!' may be broken.")
                alp.log("len(all_configured)=0")
                alp.log("q='{0}'".format(q))
                alp.log("updatables='{0}'".format(updatables))
                alp.log("results='{0}'".format(results))
                alp.feedback(I(title="Error", subtitle="No compatible workflows were found. See debug.log for info.",
                                valid=False))
                return

            search = q[1]
            results = alp.fuzzy_search(search, all_configured, key=lambda x: u"{0} - {1}".format(x['name'], x['local_d']))
            for r in results:
                items.append(I(title=r['name'], subtitle=u"v{0}\u2014{1}".format(r['version'], r['local_d']),
                                valid=False))

    if not len(items):
        items.append(I(title="No Results", subtitle="Your query did not return any results.", valid=False))

    alp.feedback(items)


if __name__ == "__main__":
    do_feedback()
