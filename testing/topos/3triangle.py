

from mininet.topo import Topo

class MyTopo( Topo ):
    "Triangle."

    def __init__( self ):

        # Initialize topology
        Topo.__init__( self )

        # Add hosts and switches
        host1 = self.addHost('h1')
        host2 = self.addHost('h2')
        host3 = self.addHost('h3')
        switch1 = self.addSwitch('s1')
        switch2 = self.addSwitch('s2')
        switch3 = self.addSwitch('s3')

        # Add links
        self.addLink(host1, switch1)
        self.addLink(host2, switch2)
        self.addLink(host3, switch3)
        self.addLink(switch1, switch2, bw=0.03)
        self.addLink(switch3, switch1, bw=0.04)
        self.addLink(switch2, switch3, bw=0.04)

topos = { 'mytopo': ( lambda: MyTopo() ) }
