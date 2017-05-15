from scapy.all import *
import time

for i in range(0, 100):
    packet = Ether(dst='02:fe:b2:62:52:df')/Dot1Q(vlan=1)/Raw(RandString(size=700))
    sendp(packet)
    time.sleep(1)
