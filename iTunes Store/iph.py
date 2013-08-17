import urllib
import sys
import os
import alp
from alp.item import Item as I


def search_for(query):
    s = alp.Settings()
    country = s.get("country", "US")
    args = {'term': query, 'country': country, 'media': 'software', 'limit': '10'}
    its_api = "http://itunes.apple.com/search"
    myScraper = alp.Request(its_api, args)
    theResult = myScraper.request.json()

    return theResult['results']


def artworkCache(url):
    cachePath = alp.cache("artcache")
    if not os.path.exists(cachePath):
        os.makedirs(cachePath)

    (urlFragment, filename) = os.path.split(url)
    (_, prefix) = os.path.split(urlFragment)
    prefix = os.path.basename(os.path.normpath(prefix))
    filename = prefix + filename
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
    iconLoc = artworkCache(item['artworkUrl60'])
    itemID = item['trackId']
    directLink = "itms://phobos.apple.com/WebObjects/MZStore.woa/wa/viewSoftware?id=%s&mt=8" % (itemID)
    s = alp.Settings()
    if s.get("affiliate_string", None):
        directLink += s.get("affiliate_string")
    return {
        'uid': item['trackName'],
        'arg': directLink,
        'title': item['trackName'],
        'subtitle': u"by %s\u2014%s" % (item['artistName'], item['formattedPrice']),
        'icon': iconLoc,
        'valid': True
    }


def iTunesSearch():
    q = alp.args()[0]

    items = map(lambda x: resultParse(x), search_for(q))

    results = []
    default_search = "itms://phobos.apple.com/WebObjects/MZSearch.woa/wa/search?" + urllib.urlencode({"term": q})
    results.append(I(title="Search in iTunes", subtitle="Open iTunes Store and search for \"{0}\"".format(q),
                        arg=default_search, valid=True))
    if len(items):
        for anItem in items:
            results.append(I(**anItem))
    else:
        results.append(I(title="No Results", subtitle="Your search did not return any results", valid=False))

    alp.feedback(results)

if __name__ == "__main__":
    iTunesSearch()
