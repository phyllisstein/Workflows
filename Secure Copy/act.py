import re
import os
import subprocess
import json
import sys
from libpexpect import pexpect
import PyAl
import codecs


def doUpload(serverData, pathList):
    completed = 0
    failed = 0
    for path in pathList:
        if os.path.isfile(path):
            cmd = "scp \"%s\" %s@%s:%s" % \
                (path, serverData["user"], serverData["address"], serverData["path"])
        elif os.path.isdir(path):
            cmd = "scp -r \"%s\" %s@%s:%s" % \
                (path, serverData["user"], serverData["address"], serverData["path"])
        else:
            print "%s cannot be uploaded." % path
            return
        child = pexpect.spawn(cmd)
        j = child.expect([".*[pP]assword.*", pexpect.EOF, pexpect.TIMEOUT], timeout=15)
        if j == 0:
            child.sendline(serverData["pw"])
            i = child.expect([pexpect.EOF, ".*Permission denied.*"], timeout=None)
            if i == 0:
                child.close()
                completed = completed + 1
                if serverData["url"] != None:
                    (_, filename) = os.path.split(path)
                    remoteURL = serverData["url"] + filename
                    copyCmd = "echo \"%s\" | pbcopy" % remoteURL
                    subprocess.call(copyCmd, shell=True)

            elif i == 1:
                failed = failed + 1
                child.kill(0)
            else:
                failed = failed + 1
                child.kill(0)
        if j == 1:
            child.close()
            completed = completed + 1

            if serverData["url"] != None:
                (_, filename) = os.path.split(path)
                remoteURL = serverData["url"] + filename
                copyCmd = "echo \"%s\" | pbcopy" % remoteURL
                subprocess.call(copyCmd, shell=True)
        if j == 2:
            failed = failed + 1
            child.kill(0)

        if completed > 0 and failed == 0:
            sib = "s" if completed != 1 else ""
            print "%s file%s uploaded." % (completed, sib)
        else:
            com_sib = "s" if completed != 1 else ""
            fail_sib = "s" if failed != 1 else ""
            print "%s file%s uploaded, %s upload%s failed." % (completed, com_sib, failed, fail_sib)


def main():
    serversJSON = PyAl.nonvolatile("servers.json")
    bundleID = PyAl.bundle()

    with open(serversJSON) as f:
        servers = json.load(f)

    if sys.argv[1] == "add":
        name = sys.argv[2]
        user = sys.argv[3]
        pw = sys.argv[4]
        address = sys.argv[5]
        path = sys.argv[6]
        if len(sys.argv) == 8:
            url = sys.argv[7]
            if not url.endswith("/"):
                url = url + "/"
        else:
            url = None

        if not path.endswith("/"):
            path = path + "/"

        serverData = {"user": user, "address": address, "path": path, "url": url}
        servers[name] = serverData

        k = PyAl.Keychain("%s.%s" % (bundleID, address))
        k.storePassword(user, pw)

        with open(serversJSON, "w") as f:
            json.dump(servers, f)

        print "Added %s (%s@%s)" % (name, user, address)

    if sys.argv[1] == "remove":
        name = sys.argv[2]
        delServerData = servers.pop(name)

        k = PyAl.Keychain("%s.%s" % (bundleID, delServerData["address"]))
        k.deletePassword(delServerData["user"])

        with open(serversJSON, "w") as f:
            json.dump(servers, f)

        print "Deleted %s (%s@%s)" % (name, delServerData["user"], delServerData["address"])

    if sys.argv[1] == "finder":
        name = sys.argv[2]
        serverData = servers[name]

        k = PyAl.Keychain("%s.%s" % (bundleID, serverData["address"]))
        serverData["pw"] = k.retrievePassword(serverData["user"])

        pathList = subprocess.check_output(["osascript", "getFinder.applescript"])
        pathList = pathList.split(" , ")

        cleanPaths = []
        for path in pathList:
            if len(path):
                newPath = path[1:]
                if "'" in newPath:
                    newPath = newPath.replace("'", "")
                if ", " in newPath:
                    newPath = newPath.replace(", ", "")
                if "\n" in newPath:
                    newPath = newPath.replace("\n", "")
                cleanPaths.append(newPath)
        doUpload(serverData, cleanPaths)

    if sys.argv[1] == "path":
        name = sys.argv[2]
        pathList = sys.argv[3]

        pathSplit = re.compile(" (?=/|~)")
        pathList = re.split(pathSplit, pathList)

        for path in pathList:
            if "~" in path:
                pathList.remove(path)
                path = os.path.expanduser(path)
                pathList.append(path)

        serverData = servers[name]

        k = PyAl.Keychain("%s.%s" % (bundleID, serverData["address"]))
        serverData["pw"] = k.retrievePassword(serverData["user"])

        doUpload(serverData, pathList)

    if sys.argv[1] == "setdefault":
        name = sys.argv[2]
        serverData = servers[name]

        servers["default"] = serverData

        with open(serversJSON, "w") as f:
            json.dump(servers, f)

        print "Designated %s (%s@%s) default." % (name, serverData["user"], serverData["address"])

    if sys.argv[1] == "default":
        path = sys.argv[2]

        pathList = path.split("\t")

        try:
            serverData = servers["default"]
        except KeyError:
            print "No default server designated."
            return

        k = PyAl.Keychain("%s.%s" % (bundleID, serverData["address"]))
        serverData["pw"] = k.retrievePassword(serverData["user"])

        doUpload(serverData, pathList)


if __name__ == "__main__":
    main()
