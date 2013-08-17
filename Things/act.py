import alp
import subprocess


def scpt(innards):
    return u'''
tell application "Things"
    activate
    {0}
end tell'''.format(innards.decode("utf-8"))


def scpt_act(innards):
    return u'''
tell application "Things"
    activate
    set index of window "Things" to 1
    {0}
end tell'''.format(innards.decode("utf-8"))

def wake_up():
    return u'''
tell application "Things"
    launch
end tell'''

def process():
    args = alp.args()

    o = subprocess.call(["osascript", "-e", wake_up()])

    if args[0] == "parse":
        inp = args[1]
        if "\"" in inp:
            inp = inp.replace("\"", "\\\"")        
        o = subprocess.call(["osascript", "-e", scpt("parse quicksilver input \"{0}\"".format(inp.encode("utf-8")))])
        # print "Task added."
    elif args[0] == "show":
        thing = args[1]
        inp = args[2]
        if "\"" in inp:
            inp = inp.replace("\"", "\\\"")
        o = subprocess.call(["osascript", "-e", scpt_act("show ({0} named \"{1}\")".format(thing.encode("utf-8"), inp.encode("utf-8")))])
        # print "Showing..."


if __name__ == "__main__":
    process()
