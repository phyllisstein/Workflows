from subprocess import call
import alp


def act():
    args = alp.args()
    if args[0] == "configure":
        url = args[1]
        sig = args[2]

        s = alp.Settings()
        s_dict = {"url": url}
        s.set(**s_dict)

        kc = alp.Keychain("yourls_stats")
        if not kc.retrievePassword("signature"):
            kc.storePassword("signature", sig)
        else:
            kc.modifyPassword("signature", sig)

        info = alp.readPlist(alp.local("info.plist"))
        objs = info['objects']
        kw = None
        for o in objs:
            if o['type'] == "alfred.workflow.input.scriptfilter":
                kw = o['config']['keyword']
                break

        if kw:
            scpt = "tell application \"Alfred 2\" to search \"{0}\"".format(kw)
            call(["osascript", "-e", scpt])

        print "Yourls Configured"

    elif args[0] == "copy":
        print args[1]

if __name__ == "__main__":
    act()
