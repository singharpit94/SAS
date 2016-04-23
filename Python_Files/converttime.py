'''from datetime import datetime
from pytz import timezone

fmt = "%Y-%m-%d %H:%M:%S %Z%z"

# Current time in UTC
now_utc = datetime.now(timezone('UTC'))
print now_utc.strftime(fmt)

# Convert to US/Pacific time zone
now_pacific = now_utc.astimezone(timezone('US/Pacific'))
print now_pacific.strftime(fmt)

# Convert to Europe/Berlin time zone
now_berlin = now_pacific.astimezone(timezone('Europe/Berlin'))
print now_berlin.strftime(fmt)'''
from pytz import all_timezones
arr={}
i=0;
print len(all_timezones)
for zone in all_timezones:
    arr[i]=zone
    i=i+1
    print arr[i-1]
