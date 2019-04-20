
#ifndef CS621_PROJECT2_SRCMASK_H
#define CS621_PROJECT2_SRCMASK_H



#include <stdint.h>
#include "FilterElement.h"
#include "ns3/ipv4-address.h"


namespace ns3 {

  class SrcMask : public FilterElement{
  private:
      Ipv4Mask ipv4_mask;
	  std::string  protocol;     
  public:
      SrcMask(Ipv4Mask ipv4_mask,  std::string protocol){
          this->ipv4_mask = ipv4_mask;
		  this->protocol = protocol;
      }
       bool match(Ptr<Packet> p);
  };

}


#endif //CS621_PROJECT2_SRCMASK_H
