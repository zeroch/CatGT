__author__ = 'ivan'

import socket
import sys
from socket import error as socket_error
import command

messages = command.send_jsons

#create a TCP/IP Socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

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

print >> sys.stderr, 'Starting server on %s port %s' % server_address
sock.bind(server_address)

#Listen for incoming connections
sock.listen(1)


while True:
    # Wait for a connection
    print >> sys.stderr, 'waiting for a connection'
    connection, client_address = sock.accept()
    try:
        print  >> sys.stderr, 'connection from', client_address
        index=0
        while True:
            for message in messages:
                print >>sys.stderr, 'sending %s' % message
                connection.sendall(message)
        else:
            print >> sys.stderr, 'no more messages'
            break
    except socket_error as serr:
        #if we have a disconnect we try to reconnect
        connection.close()
        connection, client_address = sock.accept()
    finally:
        #clean up the connection
        connection.close()