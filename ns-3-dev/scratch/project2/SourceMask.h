
#ifndef CS621_PROJECT2_SOURCEMASK_H
#define CS621_PROJECT2_SOURCEMASK_H



#include <stdint.h>
#include "FilterElement.h"
#include "ns3/ipv4-address.h"


namespace ns3 {

  class SourceMask : public FilterElement{
  private:
      Ipv4Mask ipv4_mask;
	  std::string  protocol;     
  public:
        SourceMask(Ipv4Mask ipv4_mask,  std::string protocol){
          this->ipv4_mask = ipv4_mask;
		  this->protocol = protocol;
      }
       bool match(Ptr<Packet> p);
  };

}


#endif //CS621_PROJECT2_SOURCEMASK_H
