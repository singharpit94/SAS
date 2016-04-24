import smtplib


# Establish a secure session with gmail's outgoing SMTP server using your gmail account
server = smtplib.SMTP( "smtp.gmail.com", 587 )

server.starttls()

server.login( 'arpitsinghnitd@gmail.com', '' )

# Send text message through SMS gateway of destination number
server.sendmail( 'arpitsinghnitd@gmail.com', 'singhpurshotam1@gmail.com', 'Hello' )
