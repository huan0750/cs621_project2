
#ifndef CS621_PROJECT2_DESTINATIONMASK_H
#define CS621_PROJECT2_DESTINATIONMASK_H



#include <stdint.h>
#include "FilterElement.h"
#include "ns3/ipv4-address.h"


namespace ns3 {

  class DestinationMask : public FilterElement{
  private:
      char const * mask;
	  std::string  protocol;     
  public:
      DestinationMask(char const * 	mask,  std::string protocol){
          this->mask = mask;
		  this->protocol = protocol;
      }
       bool match(Ptr<Packet> p);
  };

}


#endif //CS621_PROJECT2_DESTINATIONMASK_H
