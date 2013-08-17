import sys
import subprocess
import os
import alp


def do_action():
    args = alp.args()
    storedFiles = alp.jsonLoad("files.json", default=[])
    storedPaths = alp.jsonLoad("paths.json", default=[])

    if args[0] == "undo":
        action = args[1]
        arg = args[2]

        if action == "add":
            storedFiles.remove(arg)
            alp.jsonDump(storedFiles, "files.json")
            print "Forgot {0}".format(arg)

        elif action == "touch":
            the_dir = subprocess.check_output(["osascript", "getFinder.applescript"])
            the_dir = the_dir[:-1]
            the_file = os.path.join(the_dir, arg)
            try:
                os.remove(the_file)
            except Exception as e:
                alp.log("Failed to delete: {0}".format(e))
                print "Failed to delete: {0}".format(e)

        elif action == "path":
            storedPaths.remove(arg)
            alp.jsonDump(storedPaths, "paths.json")
            print "Forgot {0}".format(arg)

        elif action == "at":
            try:
                os.remove(arg)
            except Exception as e:
                alp.log("Failed to delete: {0}".format(e))
                print "Failed to delete: {0}".format(e)
            else:
                print "Deleted {0}".format(arg)

    else:
        action = args[0]
        arg = args[1]

        if action == "add":
            storedFiles.append(arg)
            alp.jsonDump(storedFiles, "files.json")
        
        elif action == "path":
            storedPaths.append(arg)
            alp.jsonDump(storedPaths, "paths.json")
        
        elif action == "touch":
            the_dir = subprocess.check_output(["osascript", "getFinder.applescript"])
            the_dir = the_dir[:-1]
            target = os.path.join(the_dir, arg)
            cmd = ["touch", target]
            subprocess.call(cmd)

            if len(args) == 3 and args[2] == "open":
                cmd = ["open", target]
                subprocess.call(cmd)

        elif action == "at":
            cmd = ["touch", arg]
            subprocess.call(cmd)

            if len(args) == 3 and args[2] == "open":
                cmd = ["open", arg]
                subprocess.call(cmd)
            else:
                print "Created {0}".format(arg)


if __name__ == "__main__":
    do_action()
