CONSUMER_KEY = '75q2mu7nnpun00'
CONSUMER_SECRET = 'BAQHWH9PL4713LKm'
USER_TOKEN = '75q2mu7nnpun00'
USER_SECRET = 'BAQHWH9PL4713LKm'
 
auth = linkedin.LinkedInDeveloperAuthentication(CONSUMER_KEY, CONSUMER_SECRET,USER_TOKEN, USER_SECRET,RETURN_URL,permissions=linkedin.PERMISSIONS.enums.values())
 
app = linkedin.LinkedInApplication(auth)[code]
 

 
[code language="python"]
import json
connections = app.get_connections()
 
linkedin_contacts = 'contacts.json'
 
f = open(linkedin_contacts, 'w')
f.write(json.dumps(connections, indent=1))
f.close()
