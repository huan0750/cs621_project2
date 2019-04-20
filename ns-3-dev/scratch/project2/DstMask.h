
#ifndef CS621_PROJECT2_DESTMASK_H
#define CS621_PROJECT2_DESTMASK_H



#include <stdint.h>
#include "FilterElement.h"
#include "ns3/ipv4-address.h"


namespace ns3 {

  class DestMask : public FilterElement{
  private:
      Ipv4Mask ipv4_mask;
	  std::string  protocol;     
  public:
      DestIP(Ipv4Address ipv4_address,  std::string protocol){
          ipv4_mask = ipv4_address.GetDest.GetMask;
		  this->protocol = protocol;
      }
       bool match(Ptr<Packet> p);
  };

}


#endif //CS621_PROJECT2_DETINATIONPORTNUMBER_H
