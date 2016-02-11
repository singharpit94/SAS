import datetime
c1=raw_input("Enter Country 1\n")

c2=raw_input("Entry Country 2\n")
date_entry=raw_input("Enter Date in YYYY-MM-DD format \n")
year,month,day=map(int,date_entry.split('-'))
date1=datetime.date(year,month,day)
print(c1,c2,date1)
m=Match(country1=c1,country2=c2,date=date1)
for i in Player.object.all():
	if i.country==c1 or i.country==c2:
		p=PlayerToMatch(match=m,player=i)
		p.save()


