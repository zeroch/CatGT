__author__ = 'ivan'


import socket
import sys
from socket import error as socket_error
import command

messages = command.send_jsons

#create a TCP/IP Socket
sock_cat = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock_owner = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#bind the socket to the port
#default server address else command line argument
if not (len(sys.argv) == 1 or len(sys.argv) == 3) :
    print "Invalid Number Of arguments use python Server.py 'ip.address' portNumber"
    print len(sys.argv)
    sys.exit(1)
elif len(sys.argv) == 3:
    try:
        server_address = (sys.argv[1], int(sys.argv[2]))
    except:
        print "Invalid portnumber value. Make sure to input an integer"
        sys.exit(1)
else:
    server_address = ("localhost", 10000)

print >> sys.stderr, 'Starting server on %s port %s' % server_address
sock_cat.bind(server_address)
server_address = (server_address[0], server_address[1]+1)
sock_owner.bind(server_address)
#callback
#Listen for incoming connections
sock_cat.listen(1)
sock_owner.listen(1)

while True:
    # Wait for a connection
    print >> sys.stderr, 'waiting for a connection'
    connection_cat, client_address_cat = sock_cat.accept()
    connection_owner, client_address_owner = sock_owner.accept()
    try:
        print  >> sys.stderr, 'connection from', client_address_cat
        while True:
            data = connection_owner.recv(35)
            connection_cat.sendall(data)
    except socket_error as serr:
        #if we have a disconnect we try to reconnect
        connection_cat.close()
        connection_owner.close()
        connection_cat, client_address_cat = sock_cat.accept()
        connection_owner, client_address_owner = sock_owner.accept()
    finally:
        #clean up the connection
        connection_cat.close()