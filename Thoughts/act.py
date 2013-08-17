import time
import sys
import subprocess
import alp


def main():
    verb = sys.argv[1]

    thoughts = alp.jsonLoad("thoughts.json")

    if verb == "copy":
        uuid = sys.argv[2]
        thought = None
        for thought in thoughts:
            if thought["uuid"] == uuid:
                thought = thought["thought"]
                break
        if not thought:
            print "Unknown error."
        else:
            cmd = u"echo \"{0}\" | pbcopy".format(thought)
            subprocess.call(cmd, shell=True)
            print "Recalled \"{0}\"".format(thought)

    elif verb == "save":
        uuid = sys.argv[2]
        thought = sys.argv[3]
        thoughts.append(dict(uuid=uuid, thought=thought))
        alp.jsonDump(thoughts, "thoughts.json")

        print "Remembered %s" % thought

    elif verb == "delete" and sys.argv[2] != "save":
        uuid = sys.argv[3]
        for thought in thoughts:
            if thought["uuid"] == uuid:
                forgotten = thought["thought"]
                thoughts.remove(thought)
                break

        alp.jsonDump(thoughts, "thoughts.json")

        print "Forgot %s" % forgotten

    elif verb == "delete" and sys.argv[2] == "save":
        thought = sys.argv[4]
        print "Never remembered {0}".format(thought)

    else:
        print "Unknown error in act.py"


if __name__ == "__main__":
    main()
