import alp
from alp.item import Item as I


def fetch_stats(url, signature, force=False):
    payload = {
        "action": "stats",
        "filter": "last",
        "limit": 15,
        "format": "json",
        "signature": signature
    }
    r = alp.Request(url, payload=payload, post=True, cache_for=1800)
    if force:
        r.clear_cache()
    r.download()
    try:
        j = r.request.json()
    except Exception as e:
        alp.log("Exception: {0}\nurl={1}".format(e, url))
        return I(title="Network Error", subtitle=str(e), valid=False)

    try:
        count = int(j["stats"]["total_links"])
    except Exception as e:
        alp.log("Exception: {0}\nurl={1}\njson={2}".format(e, url, j))
        return I(title="JSON Error", subtitle=str(e), valid=False)
    if not count > 0:
        alp.log("Error: No Links\nurl={0}\ncount={1}".format(url, count))
        return I(title="No Links!", subtitle="count={0}".format(count), valid=False)

    links = []
    count = 15 if count > 15 else count
    for i in range(1, count+1):
        key = "link_%s" % i
        links.append(j["links"][key])

    return links

def do_feedback():
    args = alp.args()
    settings = alp.Settings()
    url = settings.get("url", None)
    if url:
        k = alp.Keychain("yourls_stats")
        sig = k.retrievePassword("signature")
        links = fetch_stats(url, sig)
        if isinstance(links, I):
            alp.feedback(links)
            return
        feedback = []

    def build_feedback(good_links):
        for l in good_links:
            s = "" if int(l["clicks"]) == 1 else "s"
            subtitle = u"{0} \u2022 {1} click{2}".format(l["shorturl"], l["clicks"], s)
            feedback.append(I(title=l["title"], subtitle=subtitle,
                            valid=True, arg="copy \"{0}\"".format(l["shorturl"])))

    if len(args) == 0 and url:
        build_feedback(links)
    elif len(args):
        q = args[0]
        if "!" in q:
            links = fetch_stats(url, sig, force=True)
            if isinstance(links, I):
                alp.feedback(links)
                return
            q = q.replace("!", "")

        if not url or "=" in q:
            new_settings = q.split(" ")
            url = "foo"
            sig = "bar"
            for ns in new_settings:
                if "=" in ns:
                    k = ns.split("=")[0]
                    v = ns.split("=")[1]
                    if k == "url":
                        if not v.startswith("http://"):
                            v = "http://" + v
                        if v.endswith("php"):
                            pass
                        elif v.endswith("/"):
                            v += "yourls-api.php"
                        else:
                            v += "/yourls-api.php"
                        url = v
                    if k == "signature":
                        sig = v

            valid = True if "=" in q and (url != "foo") and (sig != "bar") else False
            feedback = I(title="Configure Yourls", subtitle="url={0} signature={1}".format(url, sig),
                            valid=valid, arg="configure \"{0}\" \"{1}\"".format(url, sig))
        elif url:
            gl = alp.fuzzy_search(q, links, key=lambda x: u"{0} - {1}".format(x["title"], x["shorturl"]))
            build_feedback(gl)
            if len(feedback) == 0:
                feedback = I(title="No Results", subtitle="No Yourls matched your query.", valid=False)
    else:
        feedback = I(title="Configure Yourls", subtitle="url=foo signature=bar", valid=False)

    alp.feedback(feedback)

if __name__ == "__main__":
    do_feedback()
