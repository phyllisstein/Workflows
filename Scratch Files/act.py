import subprocess
import os
import json
import sys
import PyAl


def main():
    verb = sys.argv[1]

    if verb == "add":
        name = sys.argv[2]
        path = sys.argv[3]

        if "~" in path:
            path = os.path.expanduser(path)

        with open(PyAl.nonvolatile("scratches.json"), "r") as f:
            scratchList = json.load(f)
            f.close()

        if not os.path.isabs(path):
            path = os.path.join(PyAl.nonvolatile(), path)

        if os.path.isdir(path):
            path = os.path.join(path, name)

        scratchList[name] = path

        with open(PyAl.nonvolatile("scratches.json"), "w") as f:
            json.dump(scratchList, f)
            f.close()

        with open(path, "w") as f:
            f.write("\n")
            f.close()

        print "Added %s (%s)." % (name, path)

    elif verb == "remove":
        with open(PyAl.nonvolatile("scratches.json"), "r") as f:
            scratchList = json.load(f)
            f.close()

        try:
            name = sys.argv[2]
            deleted = scratchList.pop(name)
        except Exception as e:
            print "%s does not exist: %s" % (name, e)
            return

        path = deleted
        os.remove(path)

        with open(PyAl.nonvolatile("scratches.json"), "w") as f:
            json.dump(scratchList, f)

            f.close()

        print "Deleted %s (%s)." % (name, path)

    elif verb == "scratch":
        name = sys.argv[2]
        toScratch = sys.argv[3]

        with open(PyAl.nonvolatile("scratches.json"), "r") as f:
            scratchList = json.load(f)
            f.close()
        try:
            path = scratchList[name]
        except Exception as e:
            print "%s does not exist: %s" % (name, e)
            return

        cmd = 'sed -i "" -e "1i\\ \n - %s" "%s"' % (toScratch, path)

        subprocess.call(cmd, shell=True)

        # print "Scratched to %s (%s)." % (name, path)
        print toScratch

    else:
        print "Unknown error in act.py"


if __name__ == '__main__':
    main()
