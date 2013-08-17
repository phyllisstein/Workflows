import sys
import os
import json
import PyAl
from PyAl import Feedback as F
from PyAl import Item as I


def main():
    serversJSON = PyAl.nonvolatile("servers.json")
    errorItem = I(valid=False, title="No saved servers!", subtitle="You must store a server first.")

    if os.path.exists(serversJSON):
        with open(serversJSON) as f:
            servers = json.load(f)
    else:
        empty = {}
        with open(serversJSON, "w") as f:
            json.dump(empty, f)
        servers = {}

    if len(sys.argv) == 1:
        items = [I(valid=False, autocomplete="add ",
            title="Add Server to Favorites", subtitle="Store server information securely in the Keychain.")]
        if len(servers) > 0:
            items.append(I(valid=False, autocomplete="upload ",
                title="Upload to Server", subtitle="Select a server to upload to."))
            items.append(I(valid=False, autocomplete="remove ",
                title="Remove Server from Favorites", subtitle="Forget a server's information."))
            items.append(I(valid=False, autocomplete="default ",
                title="Set Default Server", subtitle="Designate a default server for file actions."))
        print F(items)

    elif sys.argv[1] == "add":
        if len(sys.argv) == 2:
            name = "[name]"
            user = "[user]"
            pw = ""
            masked = "[password]"
            address = "[address]"
            path = "[path]"
            url = "[baseurl]"
            item = I(valid=False, title="Save %s" % name, subtitle="%s %s %s %s %s %s" % (name, user, masked, address, path, url))

        elif len(sys.argv) == 3:
            name = sys.argv[2]
            user = "[user]"
            pw = ""
            masked = "[password]"
            address = "[address]"
            path = "[path]"
            url = "[baseurl]"
            item = I(valid=False, title="Save %s" % name, subtitle="%s %s %s %s %s %s" % (name, user, masked, address, path, url))

        elif len(sys.argv) == 4:
            name = sys.argv[2]
            user = sys.argv[3]
            pw = ""
            masked = "[password]"
            address = "[address]"
            path = "[path]"
            url = "[baseurl]"
            item = I(valid=False, title="Save %s" % name, subtitle="%s %s %s %s %s %s" % (name, user, masked, address, path, url))

        elif len(sys.argv) == 5:
            name = sys.argv[2]
            user = sys.argv[3]
            pw = sys.argv[4]
            masked = u"\u2022" * len(pw)
            address = "[address]"
            path = "[path]"
            url = "[baseurl]"
            item = I(valid=False, title="Save %s" % name, subtitle="%s %s %s %s %s %s" % (name, user, masked, address, path, url))

        elif len(sys.argv) == 6:
            name = sys.argv[2]
            user = sys.argv[3]
            pw = sys.argv[4]
            masked = u"\u2022" * len(pw)
            address = sys.argv[5]
            path = "[path]"
            url = "[baseurl]"
            item = I(valid=False, title="Save %s" % name, subtitle="%s %s %s %s %s %s" % (name, user, masked, address, path, url))

        elif len(sys.argv) == 7:
            name = sys.argv[2]
            user = sys.argv[3]
            pw = sys.argv[4]
            masked = u"\u2022" * len(pw)
            address = sys.argv[5]
            path = sys.argv[6]
            url = "[baseurl]"
            item = I(valid=True, title="Save %s" % name, subtitle="%s %s %s %s %s %s" % (name, user, masked, address, path, url),
                arg="add \"%s\" \"%s\" \"%s\" \"%s\" \"%s\"" % (name, user, pw, address, path))

        elif len(sys.argv) == 8:
            name = sys.argv[2]
            user = sys.argv[3]
            pw = sys.argv[4]
            masked = u"\u2022" * len(pw)
            address = sys.argv[5]
            path = sys.argv[6]
            url = sys.argv[7]
            item = I(valid=True, arg="add \"%s\" \"%s\" \"%s\" \"%s\" \"%s\" \"%s\"" % (name, user, pw, address, path, url),
                title="Save %s" % name, subtitle="%s %s %s %s %s %s" % (name, user, masked, address, path, url))

        print F(item)

    elif sys.argv[1] == "remove":
        if len(servers) < 1:
            items = errorItem
        else:
            items = []
            for server in servers.keys():
                name = server
                serverDict = servers[name]
                address = serverDict["address"]
                user = serverDict["user"]
                items.append(I(valid=True, arg="remove \"%s\"" % name, uid=name,
                    title="Remove " + name, subtitle="%s@%s" % (user, address)))
        print F(items)

    elif sys.argv[1] == "upload":
        if len(servers) < 1:
            items = errorItem
        else:
            if len(sys.argv) == 2:
                items = []
                for server in servers.keys():
                    if server != "default":
                        name = server
                        serverDict = servers[name]
                        address = serverDict["address"]
                        user = serverDict["user"]
                        items.append(I(valid=False, autocomplete="upload %s" % name,
                            title="Upload to %s" % name, subtitle="%s@%s" % (user, address)))
            elif len(sys.argv) == 3:
                name = sys.argv[2]
                items = I(valid=True, arg="finder \"%s\"" % name, uid=name,
                    title="Finder to %s" % name, subtitle="Upload Finder selection to %s." % name)
            elif len(sys.argv) == 4:
                name = sys.argv[2]
                path = sys.argv[3]
                items = I(valid=True, arg="path \"%s\" \"%s\"" % (name, path), uid=name, icon=path, fileIcon=True,
                    title="Path to %s" % name, subtitle="Upload '%s' to %s." % (path, name))

        print F(items)

    elif sys.argv[1] == "default":
        if len(servers) < 1:
            items = errorItem
        else:
            items = []
            for server in servers.keys():
                name = server
                serverDict = servers[name]
                address = serverDict["address"]
                user = serverDict["user"]
                items.append(I(valid=True, arg="setdefault %s" % name,
                    title="Set '%s' as Default" % name, subtitle="%s@%s" % (user, address)))

        print F(items)


if __name__ == "__main__":
    main()
