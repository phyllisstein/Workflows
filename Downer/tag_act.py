import os.path
import alp
from downer.tags import *


def do_feedback():
    args = alp.args()
    path = args[0]
    tags = args[1:]
    set_tags(tags, path)

    _, name = os.path.split(path)
    tag_string = ", ".join(tags)
    name = name.encode("utf-8")
    print "Tagged {0} \"{1}\".".format(name, tag_string)

if __name__ == "__main__":
    do_feedback()
