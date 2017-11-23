import socket

#socket.SOCK_STREAM indicates TCP
serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serversocket.bind(("127.0.0.1", 12345))
serversocket.listen(1)

(clientsocket, address) = serversocket.accept()
msg = clientsocket.recv(1024)
print("server recieved", msg)

print "server sending reply" 
clientsocket.send("server received your message")

serversocket.close()
