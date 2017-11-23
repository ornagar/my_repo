import httplib
import sys

#get http server ip
http_server = sys.argv[1]
#create connection
conn = httplib.HTTPConnection(http_server)

while True:
	cmd = raw_input('input command (ex. GET index.html): ')
	cmd = cmd.split()
	
	if cmd[0] == 'exit':
		break
	
	#request command to server
	conn.request(cmd[0], cmd[1])
	
	#get response from server
	rsp = conn.getresponse()
	
	#print server response and data
	print(rsp.status, rsp.reason)
	data_received = rsp.read()
	print(data_received)
	
conn.close()
