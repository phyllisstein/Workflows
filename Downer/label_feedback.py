import os.path
from downer.Constants import *
import alp
from alp.item import Item as I


def do_feedback():
    args = alp.args()
    path = args[0]
    feedback = []
    for n, color in COLORS.items():
        icon = os.path.join(alp.local(), "icons", "{0}.png".format(color))
        feedback.append(I(title=color, subtitle=u"Set Finder label to {0}".format(color),
                        icon=icon, valid=True, arg=u"\"{0}\" \"{1}\"".format(path, n)))
    alp.feedback(feedback)

if __name__ == "__main__":
    do_feedback()
