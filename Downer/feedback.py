import time
import os
from downer.tags import *
from downer.labels import *
import alp


def find_downloads():
    paths = []
    downloads = unicode(os.path.expanduser(u"~/Downloads"))
    for fn in os.listdir(downloads):
        if not fn == ".DS_Store" and not fn == ".localized":
            fpath = os.path.join(downloads, fn)
            if os.path.exists(fpath):
                paths.append(fpath)
            else:
                alp.log(u"Could not add '{0}'---is it a broken symlink?".format(fpath))

    returnables = []
    for path in paths:
        path = path.decode("utf-8")
        path = unicode(path)
        _, name = os.path.split(path)
        mod_time = os.path.getctime(path)
        color = get_finder_label(path)
        tags = get_tags(path)
        returnables.append((path, name, mod_time, color, tags))
    return returnables

def do_feedback():
    args = alp.args()
    downloads = find_downloads()
    downloads = sorted(downloads, key=lambda x: x[2], reverse=True)

    def format_results(dl):
        title = dl[1]
        passed = time.time() - dl[2]
        
        if passed >= 86400:
            mod = passed % 86400
            t = (passed - mod) / 86400
            s = "" if t == 1 else "s"
            tstr = "{0} day{1}".format(int(t), s)
        elif passed >= 3600:
            mod = passed % 3600
            t = (passed - mod) / 3600
            s = "" if t == 1 else "s"
            tstr = "{0} hour{1}".format(int(t), s)
        elif passed >= 60:
            mod = passed % 60
            t = (passed - mod) / 60
            s = "" if t == 1 else "s"
            tstr = "{0} minute{1}".format(int(t), s)
        else:
            s = "" if passed == 1 else "s"
            tstr = "{0} second{1}".format(int(passed), s)

        subtitle = "Downloaded: {0} ago. Color: {1}. Tags: {2}.".format(tstr, dl[3], dl[4])
        return alp.Item(title=title, subtitle=subtitle, icon=dl[0], fileIcon=True,
                        valid=True, arg=dl[0])

    feedback = []
    if args[0] == "":
        for dl in downloads:
            item = format_results(dl)
            feedback.append(item)
    else:
        results = alp.fuzzy_search(args[0], downloads, key=lambda x: u"{0} - {1}".format(x[1], x[4]))
        for r in results:
            item = format_results(r)
            feedback.append(item)
    alp.feedback(feedback)

if __name__ == "__main__":
    do_feedback()
