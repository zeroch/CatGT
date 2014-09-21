__author__ = 'ivan'

from twisted.internet.protocol import Protocol, Factory
from twisted.internet import reactor

latestCommand = "none"

class MultiEcho(Protocol):
   def __init__(self, factory):
       self.factory = factory

   def connectionMade(self):
       self.factory.echoers.append(self)

   def dataReceived(self, data):
       self.update_data(data,self.factory.echoers)

   def connectionLost(self, reason):
       self.factory.echoers.remove(self)
   def update_data(self,data,echoers):
       global latestCommand
       global changed
       if data !=latestCommand:
           for echoer in echoers:
               echoer.transport.write(data)
               echoer.transport.write(data)
               print data
           latestCommand = data



class MultiEchoFactory(Factory):
   def __init__(self):
       self.etchoers = []

   def buildProtocol(self, addr):
       return MultiEcho()

reactor.listenTCP(10000, MultiEchoFactory())
reactor.run()

