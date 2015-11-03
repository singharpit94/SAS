import urllib
import bs4
url = raw_input('Enter - ')
html = urllib.urlopen(url).read()
soup = bs4.BeautifulSoup(html)
# Retrieve a list of the anchor tags
# Each tag is like a dictionary of HTML attributes
tags = soup('a')
for tag in tags:
    print tag.get('href', None)
