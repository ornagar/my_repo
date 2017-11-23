import socket

clientsocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
clientsocket.connect(("127.0.0.1", 12345))

msg = "Hello World from client"

print('client sending:', msg)
clientsocket.send(msg)

msg = clientsocket.recv(1024)
print "client received: "+msg

clientsocket.close()
