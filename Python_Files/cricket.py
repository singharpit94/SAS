import urllib2
from xml.dom import minidom

print('''
		-1. Live Scores
		0. World News
	News specific to a country:	
		1. England
		2. Australia
		3. South Africa
		4. west Indies
		5. New Zealand
		6. India
		7. Pakistan
		8. Sri Lanka
>>> Enter your choice: ''')

num = input()

if num == -1:
	rss = urllib2.urlopen('http://www.espncricinfo.com/rss/livescores.xml').read()
else:
	rss = urllib2.urlopen('http://www.espncricinfo.com/rss/content/feeds/news/'+str(num)+'.xml').read()

rssp = minidom.parseString(rss)

titles = rssp.getElementsByTagName('title')
links = rssp.getElementsByTagName('link')

for i in xrange(1, len(titles)):  # start from 1 to skip first title of espncricinfo
	title = titles[i].childNodes[0].nodeValue
	link = links[i].childNodes[0].nodeValue
	print('\n%d. %s :: %s' %(i, title, link))


