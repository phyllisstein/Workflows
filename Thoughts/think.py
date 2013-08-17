import uuid
import sys
import alp
from alp.item import Item as I


def main():
    q = sys.argv[1]
    # args = q.split(" ", maxsplit=1)

    thoughts = alp.jsonLoad("thoughts.json", default=[])

    feedback = []
    uid = str(uuid.uuid4())
    addItem = I(title="Add a Thought", subtitle=q,
                arg=u"save \"{0}\" \"{1}\"".format(uid, q), valid=True)

    if len(thoughts) == 0:
        feedback.append(addItem)
    elif len(thoughts) and len(q):
        feedback.append(addItem)
        t = alp.fuzzy_search(q, thoughts, key=lambda x: x["thought"])
        for r in t:
            feedback.append(I(title=r["thought"], subtitle="Copy to clipboard.",
                            arg=u"copy \"{0}\"".format(r["uuid"]), valid=True))
    elif len(thoughts):
        for r in thoughts:
            feedback.append(I(title=r["thought"], subtitle="Copy to clipboard.",
                            arg=u"copy \"{0}\"".format(r["uuid"]), valid=True))

    alp.feedback(feedback)

if __name__ == "__main__":
    main()
