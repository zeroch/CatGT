__author__ = 'ivan'

import socket
import sys
import command

messages = command.send_jsons

#create a TCP/IP Socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

#bind the socket to the port

server_address = ('localhost',10000) #(host,port)
#server_address = ('198.74.55.55', 10000)
print >> sys.stderr, 'Starting server on %s port %s' % server_address
sock.bind(server_address)

#Listen for incoming connections
sock.listen(1)

message = messages.pop(0)
while True:
    # Wait for a connection
    print >> sys.stderr, 'waiting for a connection'
    connection, client_address = sock.accept()
    try:
        print  >> sys.stderr, 'connection from', client_address
        print >>sys.stderr, 'sending %s' % message
        

        while (len(messages)>=0):
            connection.sendall(message)
            message = messages.pop(0)
        else:
            print >> sys.stderr, 'no more messages'
            break

        #print >> sys.stderr, 'received "%s"' % data
        #if data:
            #print >> sys.stderr, 'sending data back to client'
            #connection.sendall(data)
        #else:
            #print >>sys.stderr, 'no more data from', client_address
            #break
    finally:
        #clean up the connection
        connection.close()