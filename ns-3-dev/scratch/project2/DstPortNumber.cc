#include "DstPortNumber.h"
#include "ns3/ppp-header.h"
#include "ns3/ipv4-header.h"
#include "ns3/udp-header.h"
#include "ns3/tcp-header.h"




namespace ns3 {
    bool DstPortNumber::match(Ptr<Packet> p){
		    Ptr<Packet> copy = p->Copy ();
            PppHeader ppp;
			copy->RemoveHeader (ppp);
			Ipv4Header iph;
			copy->RemoveHeader (iph);
			
           //std::cout <<"start print header "<<std::endl;
		   //iph.Print(std::cout);
		    //std::cout<< protocol<<"end print header"<<int(iph.GetProtocol())<<std::endl;
		
            if (protocol == "TCP" && iph.GetProtocol() == 0x06){
							TcpHeader tcpHeader;
			                copy->RemoveHeader (tcpHeader);
							 if (port == int(tcpHeader.GetDestinationPort())) return true;
				
			}else if (protocol == "UDP" && iph.GetProtocol() == 0x11){
							UdpHeader udpHeader;
			                copy->RemoveHeader (udpHeader);
							//std::cout <<"start print udpHeader  "<<std::endl;
		                     //udpHeader.Print(std::cout);
		                     std::cout <<"packet udpHeader port  "<<int(udpHeader.GetDestinationPort())<<std::endl;
							 if (port == int(udpHeader.GetDestinationPort())) return true; 
							 std::cout <<"not matching expect  port "<<port <<std::endl;
							 
					
			}else{
				
				return false;
			}
        return false;
    }
}

