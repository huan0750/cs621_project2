#include "DestinationIP.h"
#include "ns3/ppp-header.h"
#include "ns3/ipv4-header.h"
#include "ns3/udp-header.h"
#include "ns3/tcp-header.h"


namespace ns3 {
    bool DestinationIP::match(Ptr <Packet> p) {
        Ptr <Packet> copy = p->Copy();
        PppHeader ppp;
        copy->RemoveHeader(ppp);
        Ipv4Header iph;
        copy->RemoveHeader(iph);


        if (protocol == "TCP" && iph.GetProtocol() == 0x06) {
            TcpHeader tcpHeader;
            // copy->RemoveHeader (tcpHeader);
            copy->RemoveHeader(iph);
            if (address.IsEqual(iph.GetDestination())) return true;


        } else if (protocol == "UDP" && iph.GetProtocol() == 0x11) {
            UdpHeader udpHeader;
            // copy->RemoveHeader (udpHeader);
            copy->RemoveHeader(iph);
            //std::cout <<"start print udpHeader  "<<std::endl;
            //udpHeader.Print(std::cout);
            std::cout << "packet udpHeader destination ip: " << iph.GetDestination() << std::endl;
            if (address.IsEqual(iph.GetDestination())) return true;
            std::cout << "does not match expected ip " << address << std::endl;


        } else {

            return false;
        }
        return false;
    }
}

