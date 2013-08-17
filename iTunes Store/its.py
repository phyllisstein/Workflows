import urllib
import sys
import os
import alp
from alp.item import Item as I


def search_for(query):
    results = []
    s = alp.Settings()
    country = s.get("country", "US")
    args = {'term': query, 'country': country, 'media': 'all', "entity": "allTrack", 'attribute': 'allTrackTerm', 'limit': '10'}
    its_api = "http://itunes.apple.com/search"
    myScraper = alp.Request(its_api, args)
    theResult = myScraper.request.json()
    results.extend(theResult["results"])
    args = {'term': query, 'country': country, 'media': 'all', 'entity': 'allArtist', 'attribute': 'allArtistTerm', 'limit': '10'}
    r = alp.Request(its_api, args)
    results.extend(r.request.json()["results"])

    return results


def artworkCache(url):
    cachePath = alp.cache("artcache")
    if not os.path.exists(cachePath):
        os.makedirs(cachePath)

    (_, filename) = os.path.split(url)
    artPath = os.path.join(cachePath, filename)

    if os.path.exists(artPath):
        return artPath
    else:
        artScraper = alp.Request(url)
        with open(artPath, "wb") as f:
            f.write(artScraper.request.content)
            f.close()
        return artPath


def resultParse(item):
    try:
        i = item['artworkUrl30']
        iconLoc = artworkCache(item['artworkUrl30'])
    except KeyError:
        iconLoc = "icon.png"
    try:
        viewURL = item['trackViewUrl']
    except KeyError:
        try:
            viewURL = item['artistLinkUrl']
        except KeyError:
            viewURL = item['artistViewUrl']
    try:
        title = item['trackName']
        subtitle = u"by %s\u2014$%s" % (item['artistName'], item['trackPrice'])
    except KeyError:
        title = item['artistName']
        try:
            subtitle = u"%s\u2014%s" % (item['artistType'], item['primaryGenreName'])
        except KeyError:
            try:
                subtitle = item['artistType']
            except KeyError:
                subtitle = ""
    directLink = "itms" + viewURL[5:]
    s = alp.Settings()
    if s.get("affiliate_string", None):
        directLink += s.get("affiliate_string")
    return {
        # 'uid': item['trackName'],
        'arg': directLink,
        'title': title,
        'subtitle': subtitle,
        'icon': iconLoc,
        'valid': True
    }


def iTunesSearch():
    q = alp.args()[0]

    items = map(lambda x: resultParse(x), search_for(q))

    feedback = []
    default_search = "itms://phobos.apple.com/WebObjects/MZSearch.woa/wa/search?" + urllib.urlencode({"term": q})
    feedback.append(I(title="Search in iTunes", subtitle="Open iTunes Store and search for \"{0}\"".format(q),
                        arg=default_search, valid=True))
    if len(items):
        for anItem in items:
            feedback.append(I(**anItem))
    else:
        feedback.append(I(title="No Results", subtitle="Your search did not return any results", valid=False))

    alp.feedback(feedback)


if __name__ == "__main__":
    iTunesSearch()
