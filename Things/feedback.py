# -*- coding: utf-8 -*-

import alp
from alp.item import Item as I
import sqlite3
import tempfile
import shutil
import os


def do_things_dump():
    dumped = {}
    temp = tempfile.mkdtemp()
    target = os.path.join(temp, "things.db")
    libpath = os.path.expanduser("~/Library/Containers/com.culturedcode.things/Data/Library/Application Support/Cultured Code/Things/ThingsLibrary.db") if \
                                os.path.exists(os.path.expanduser("~/Library/Containers/com.culturedcode.things/Data/Library/Application Support/Cultured Code/Things/ThingsLibrary.db")) \
                                else os.path.expanduser("~/Library/Application Support/Cultured Code/Things/ThingsLibrary.db")
    shutil.copyfile(libpath, target)
    things = sqlite3.connect(target)
    t = things.cursor()

    returnables = {}

    returnables["list"] = ["Inbox", "Today", "Next", "Scheduled", "Someday", "Projects"]
    for area in t.execute("SELECT ZTITLE FROM ZTHING WHERE ZFOCUSLEVEL1 == 2 AND ZSTATUS == 0"):
        returnables["list"].append(area[0])

    returnables["project"] = []
    for project in t.execute("SELECT ZTITLE FROM ZTHING WHERE ZTYPE == 1 AND ZTRASHED != 1"):
        returnables["project"].append(project[0])

    returnables["task"] = []
    for task in t.execute("SELECT ZTITLE FROM ZTHING WHERE ZTYPE == 0 AND ZSTATUS == 0 AND ZFOCUSLEVEL1 == 0 AND ZTRASHED != 1"):
        returnables["task"].append(task[0])

    things.close()

    shutil.rmtree(temp)

    return returnables


def do_feedback():
    q = alp.args()

    if len(q) and "+" in q[0][0:2]:
        to_add = q[0].split("+", 1)[1]
        if "\"" in to_add:
            to_add = to_add.replace("\"", "\\\"")
        alp.feedback(I(title="Add Task",
                        subtitle=to_add,
                        arg=u"parse \"{0}\"".format(to_add),
                        valid=True))
        return

    things_data = do_things_dump()

    icons = {"list": os.path.join(alp.local(), "images", "area.png"), \
            "project": os.path.join(alp.local(), "images", "project.png"), \
            "task": os.path.join(alp.local(), "images", "check.png")}
    items = []
    if not len(q) or q[0] == "":
        for area in things_data["list"]:
            de_area = area.encode("ascii", "ignore")
            icon = os.path.join(alp.local(), "images", "{0}.png".format(de_area))
            if not os.path.exists(icon):
                icon = icons["list"]
            if "\"" in area:
                clean = area.replace("\"", "\\\"")
            else:
                clean = area
            items.append(I(title=area,
                            arg=u"show list \"{0}\"".format(clean),
                            icon=icon,
                            uid=area,
                            valid=True))
        for project in things_data["project"]:
            if "\"" in project:
                clean = project.replace("\"", "\\\"")
            else:
                clean = project
            items.append(I(title=project,
                            arg=u"show project \"{0}\"".format(clean),
                            icon=icons["project"],
                            uid=project,
                            valid=True))
        for task in things_data["task"]:
            if task:
                if "\"" in task:
                    clean = task.replace("\"", "\\\"")
                else:
                    clean = task
                split_task = task.encode("ascii", "ignore").split(" ")[0]
                items.append(I(title=task,
                                arg=u"show \"to do\" \"{0}\"".format(clean),
                                icon=icons["task"],
                                uid=u"task-{0}".format(split_task),
                                valid=True))
    else:
        q = q[0]
        items.append(I(title="Add Task",
                        subtitle=q,
                        arg=u"parse \"{0}\"".format(q),
                        valid=True))
        for k, v in things_data.iteritems():
            things = alp.fuzzy_search(q, v)
            for thing in things:
                uid = k if k != "task" else u"task-{0}".format(thing.split(" ")[0])
                icon = icons[k] if not thing in ["Inbox", "Logbook", "Next", \
                    "Projects", "Scheduled", "Someday", "Today"] else os.path.join(alp.local(), "images", "{0}.png".format(thing))
                arg = k if k != "task" else "to do"
                if "\"" in thing:
                    clean_thing = thing.replace("\"", "\\\"")
                else:
                    clean_thing = thing
                items.append(I(title=thing,
                                arg=u"show \"{0}\" \"{1}\"".format(arg, clean_thing),
                                icon=icon,
                                uid=uid,
                                valid=True))

    alp.feedback(items)


if __name__ == "__main__":
    do_feedback()
