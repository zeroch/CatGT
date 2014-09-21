__author__ = 'ivan'

from twisted.internet.protocol import Protocol, Factory
from twisted.internet import reactor

latestCommand = "none"

class MultiEcho(Protocol):
   def _init_(self, factory):
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
           latestCommand = data



class MultiEchoFactory(Factory):
   def _init_(self):
       self.echoers = []

   def buildProtocol(self, addr):
       return MultiEcho(self)

reactor.listenTCP(4321, MultiEchoFactory())
reactor.run()

