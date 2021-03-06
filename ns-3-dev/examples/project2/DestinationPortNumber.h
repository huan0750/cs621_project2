
#ifndef CS621_PROJECT2_DESTINATIONPORTNUMBER_H
#define CS621_PROJECT2_DESTINATIONPORTNUMBER_H



#include <stdint.h>
#include "FilterElement.h"


/**
 * match destination packet port
 */
namespace ns3 {

  class DestinationPortNumber : public FilterElement{
  private:
      uint32_t port;
	  std::string  protocol;     
  public:
      /**
       * Constructor
       *
       * @param destination_port
       * @param protocol
       */
      DestinationPortNumber(uint32_t destination_port,  std::string protocol){
          port = destination_port;
		  this->protocol = protocol;
      }
       bool match(Ptr<Packet> p);
  };

}


#endif //CS621_PROJECT2_DESTINATIONPORTNUMBER_H
