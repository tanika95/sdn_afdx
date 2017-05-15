

from mininet.topo import Topo

class MyTopo( Topo ):
    "Ima."

    def __init__( self ):

        # Initialize topology
        Topo.__init__( self )

        # Add hosts and switches
        host11 = self.addHost('h11')
        host12 = self.addHost('h12')
        host13 = self.addHost('h13')
        host21 = self.addHost('h21')
        host22 = self.addHost('h22')
        host23 = self.addHost('h23')
        host31 = self.addHost('h31')
        host32 = self.addHost('h32')
        host33 = self.addHost('h33')
        switch1 = self.addSwitch('s1')
        switch2 = self.addSwitch('s2')
        switch3 = self.addSwitch('s3')

        # Add links
        self.addLink(host11, switch1)
        self.addLink(host21, switch2)
        self.addLink(host31, switch3)
        self.addLink(host12, switch1)
        self.addLink(host22, switch2)
        self.addLink(host32, switch3)
        self.addLink(host13, switch1)
        self.addLink(host23, switch2)
        self.addLink(host33, switch3)
        self.addLink(switch1, switch2, bw=1000)
        self.addLink(switch2, switch3, bw=1000)
        self.addLink(switch3, switch1, bw=1000)

topos = { 'mytopo': ( lambda: MyTopo() ) }
