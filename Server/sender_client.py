__author__ = 'ivan'

import socket
import sys

# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect the socket to the port where the server is listening
server_address = ('localhost', 10001)  #(host,port)
#server_address = ('198.74.55.55',10000) #(host,port)
print >> sys.stderr, 'connecting to %s port %s' % server_address
sock.connect(server_address)

try:
    #while amount_received < amount_expected:
    data = "This is a test string"
    while data:
        print >> sys.stderr, 'received "%s"' % data
        sock.sendall(data)
finally:
    print >> sys.stderr, 'closing socket'
    sock.close()