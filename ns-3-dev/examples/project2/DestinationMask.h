
#ifndef CS621_PROJECT2_DESTINATIONMASK_H
#define CS621_PROJECT2_DESTINATIONMASK_H



#include <stdint.h>
#include "FilterElement.h"
#include "ns3/ipv4-address.h"

/**
 * match the destination IP range by  start_address and  mask
 *
 */
namespace ns3 {

  class DestinationMask : public FilterElement{
  private:
      Ipv4Mask mask;
      Ipv4Address start_address;
	  std::string  protocol;     
  public:
      /**
       * Constructor
       *
       * @param start_address
       * @param mask
       * @param protocol  TCP/UDP
       */
      DestinationMask(Ipv4Address start_address, Ipv4Mask mask,  std::string protocol){
          this->mask = mask;
          this->start_address = start_address;
		  this->protocol = protocol;
      }
       bool match(Ptr<Packet> p);
  };

}


#endif //CS621_PROJECT2_DESTINATIONMASK_H
