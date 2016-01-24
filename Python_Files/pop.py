import csv

with open('indiaaus.csv') as f:
    reader=csv.DictReader(f)
    for row in reader:
        p="".join(row['Player Name'].split())
        c="".join(row['Cost'].split())

        r="".join(row['Role'].split())
        n="".join(row['Country'].split())
        c=int(c)
        z=Player(name=p,cost=c,role=r,country=n)
        z.save()
        

