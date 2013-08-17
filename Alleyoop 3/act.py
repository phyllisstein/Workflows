# -*- coding: utf-8 -*-

import sys
import alp
import tempfile
import shutil
import os
import time
from Foundation import NSDistributedNotificationCenter


def act():
    q = sys.argv[1:]
    tmp = tempfile.mkdtemp()
    stamp = time.strftime("%Y-%m-%d (%H.%M)")

    cache = alp.jsonLoad("cache.json", default={})

    def do_download(address, name):
        r = alp.Request(address, cache=False)
        r.download()
        r.request.encoding = "utf-8"
        f = tempfile.NamedTemporaryFile(suffix=".alfredworkflow", dir=tmp, delete=False)
        f.write(r.request.content)
        f.close()
        d_path = os.path.join(os.path.expanduser("~/Downloads"), "{0} - {1}.alfredworkflow".format(stamp, name))
        shutil.copy(f.name, d_path)

        remme = None
        for wf in cache["cached_workflows"]:
            cached_name = wf.get("name", None)
            if cached_name == name:
                remme = wf
                break
        if remme:
            cache["cached_workflows"].remove(remme)
        alp.jsonDump(cache, "cache.json")

        return d_path


    if q[0] == "update-all":
        to_download = q[1:]
        i = len(to_download)
        for download in to_download:
            name, target_path, remote = download.split(">")
            ret_path = do_download(remote, name)
            i -= 1
            i_sib = "" if i == 1 else "s"
            n = alp.Notification()
            n.notify("Alleyoop", "Downloaded {0}".format(name),
                    "{0} update{1} remaining.".format(i, i_sib))
        NSDistributedNotificationCenter.defaultCenter().postNotificationName_object_("com.apple.DownloadFileFinished", ret_path)
        print "All updates downloaded."

    elif q[0] == "update":
        name, target_path, remote = q[1].split(">")
        ret_path = do_download(remote, name)
        NSDistributedNotificationCenter.defaultCenter().postNotificationName_object_("com.apple.DownloadFileFinished", ret_path)
        print "Saved {0} to Downloads".format(name)

    shutil.rmtree(tmp, True)



if __name__ == "__main__":
    act()
