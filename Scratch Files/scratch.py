import re
import os
import json
import sys
import PyAl


def main():
    q = sys.argv[1]
    args = q.split(" ")

    if os.path.exists(PyAl.nonvolatile("scratches.json")):
        with open(PyAl.nonvolatile("scratches.json"), "r") as f:
            scratchList = json.load(f)
            f.close()
    else:
        with open(PyAl.nonvolatile("scratches.json"), "w") as f:
            scratchList = {}
            json.dump(scratchList, f)
            f.close()

    if len(args) == 0 or args[0] == "":
        emptyFeedback = PyAl.Feedback()
        emptyFeedback.addInvalidItem(uid="com.danielsh.alfred.scratch.addscratch", autocomplete="add ",
                                    itemDict={"title": "Add Scratch File", "subtitle": "A name, a space, and a path."})
        if len(scratchList) > 0:
            emptyFeedback.addInvalidItem(uid="com.danielsh.alfred.scratch.removescratch", autocomplete="remove ",
                                        itemDict={"title": "Remove Scratch File", "subtitle": "List scratches to delete."})

            for (name, path) in scratchList.iteritems():
                emptyFeedback.addInvalidItem(uid="com.danielsh.alfred.scratch.%s" % name, autocomplete="%s " % name,
                                        itemDict={"title": name, "subtitle": path})

        print emptyFeedback

    elif args[0] == "add":
        addFeedback = PyAl.Feedback()
        if len(args) == 2:
            name = args[1] if len(args[1]) else "[name]"
            path = ""

            addFeedback.addInvalidItem(uid="com.danielsh.alfred.scratch.addscratch.%s" % name, autocomplete="add %s" % name,
                                itemDict={"title": "Add %s" % name, "subtitle": "At [path]"})
        elif len(args) == 3:
            name = args[1]
            path = args[2]

            addFeedback.addValidItem(uid="com.danielsh.alfred.scratch.addscratch.%s" % name, arg="add \"%s\" \"%s\"" % (name, path),
                                itemDict={"title": "Add %s" % name, "subtitle": "At %s" % path})
        elif len(args) > 3:
            name = args[1]
            path = args[2:]
            path = ' '.join(path)

            addFeedback.addValidItem(uid="com.danielsh.alfred.scratch.addscratch.%s" % name, arg="add \"%s\" \"%s\"" % (name, path),
                                itemDict={"title": "Add %s" % name, "subtitle": "At %s" % path})
        print addFeedback

    elif args[0] == "remove":
        removeFeedback = PyAl.Feedback()
        if len(scratchList) > 0:
            for (name, path) in scratchList.iteritems():
                removeFeedback.addValidItem(uid="com.danielsh.alfred.scratch.removescratch.%s" % name, arg="remove \"%s\"" % name,
                                itemDict={"title": "Remove %s" % name, "subtitle": "From %s" % path})
        else:
            return

        print removeFeedback

    else:
        if len(scratchList) == 0:
            return
        else:
            scratchFeedback = PyAl.Feedback()
            if args[0] in scratchList.keys():
                name = args[0]
                path = scratchList[name]
                if len(args) >= 2:
                    toScratch = args[1:]
                    toScratch = ' '.join(toScratch)

                    if '"' in toScratch:
                        toScratch = re.sub("\"", "'", toScratch)
                else:
                    toScratch = ""

                scratchFeedback.addValidItem(uid="com.danielsh.alfred.scratch.%s" % name, arg="scratch \"%s\" \"%s\"" % (name, toScratch),
                                itemDict={"title": "Scratch to %s:" % name, "subtitle": toScratch})
            else:
                return

            print scratchFeedback

if __name__ == '__main__':
    main()
