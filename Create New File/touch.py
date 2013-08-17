import os
import alp
from alp.item import Item as I


def do_feedback():
    storedNames = alp.jsonLoad("files.json", default=[])
    s = alp.Settings()
    defaultExt = s.get("extension", ".txt")

    args = alp.args()[0]
    args = args.split(" ")
    
    if len(args) == 1 and args[0] == "":
        empty = []
        
        if len(storedNames) > 0:
            for name in storedNames:
                empty.append(I(uid=name, valid=True, autocomplete=name, title=name,
                            subtitle="Create {0} in frontmost Finder window.".format(name),
                            arg="touch \"{0}\"".format(name)))

        empty.append(I(title="Add Filename", subtitle="Store a filename for faster access",
                        autocomplete="|add| ", valid=False))
        empty.append(I(title="Add Path", subtitle="Store a path for use with 'touch filename at'",
                        autocomplete="|path| ", valid=False))

        alp.feedback(empty)

    elif args[0] == "|add|":
        if len(args) >= 2:
            name = " ".join(args[1:])
        else:
            name = ""
        if not "." in name:
            name += defaultExt

        alp.feedback(I(title="Store Filename", subtitle="Store {0} for faster access".format(name),
                        arg="add \"{0}\"".format(name), valid=True))

    elif args[0] == "|path|":
        if len(args) >= 2:
            name = " ".join(args[1:])
        else:
            name = ""

        alp.feedback(I(title=name, subtitle="Store {0} as a location for new files".format(name),
                        arg="path \"{0}\"".format(name), valid=True))

    elif "at" in args:
        i = args.index("at")
        name = args[:i]
        name = " ".join(name)
        if not "." in name:
            name += defaultExt

        feedback = []

        storedPaths = alp.jsonLoad("paths.json", default=[])
        if len(storedPaths) > 0:
            for path in storedPaths:
                (_, tail) = os.path.split(path)
                touch_path = os.path.join(path, name)
                feedback.append(I(title="...{0}/{1}".format(tail, name),
                                    subtitle="{0}{1}".format(path, name),
                                    arg="at \"{0}\"".format(touch_path),
                                    valid=True))
        else:
            feedback.append(I(title="No saved paths!", subtitle="Store a path to use this feature.",
                                valid=False))

        alp.feedback(feedback)

    else:
        name = " ".join(args)
        if not "." in name:
            name += defaultExt

        alp.feedback(I(title=name, subtitle="Create {0} in frontmost finder window.".format(name),
                        valid=True, arg="touch \"{0}\"".format(name), uid=name))


if __name__ == "__main__":
    do_feedback()
