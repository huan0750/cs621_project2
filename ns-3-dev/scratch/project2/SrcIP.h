
#ifndef CS621_PROJECT2_SRCIP_H
#define CS621_PROJECT2_SRCTIP_H



#include <stdint.h>
#include "FilterElement.h"
#include "ns3/ipv4-address.h"


namespace ns3 {

  class SrcIP : public FilterElement{
  private:
      Ipv4Address address;
	  std::string  protocol;     
  public:
      SrcIP(Ipv4Address ipv4_address,  std::string protocol){
          address = ipv4_address;
		  this->protocol = protocol;
      }
       bool match(Ptr<Packet> p);
  };

}


#endif //CS621_PROJECT2_DETINATIONPORTNUMBER_H
