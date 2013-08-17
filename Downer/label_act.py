import os.path
from downer.Constants import *
import alp
from downer.labels import *


def do_feedback():
    args = alp.args()
    path = args[0]
    color = int(args[1])

    set_finder_label(path, color)
    _, name = os.path.split(path)
    name = name.encode("utf-8")
    print "{0} labeled {1}.".format(name, COLORS[color])

if __name__ == "__main__":
    do_feedback()
