
#ifndef CS621_PROJECT2_DSTIP_H
#define CS621_PROJECT2_DSTIP_H



#include <stdint.h>
#include "FilterElement.h"
#include "ns3/ipv4-address.h"


namespace ns3 {

  class DstIP : public FilterElement{
  private:
      Ipv4Address address;
	  std::string  protocol;     
  public:
      DstIP(Ipv4Address ipv4_address,  std::string protocol){
          address = ipv4_address;
		  this->protocol = protocol;
      }
       bool match(Ptr<Packet> p);
  };

}


#endif //CS621_PROJECT2_DSTPORTNUMBER_H
