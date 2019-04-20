
#ifndef CS621_PROJECT2_DSTPORTNUMBER_H
#define CS621_PROJECT2_DSTPORTNUMBER_H



#include <stdint.h>
#include "FilterElement.h"


namespace ns3 {

  class DstPortNumber : public FilterElement{
  private:
      uint32_t port;
	  std::string  protocol;     
  public:
      DstPortNumber(uint32_t destination_port,  std::string protocol){
          port = destination_port;
		  this->protocol = protocol;
      }
       bool match(Ptr<Packet> p);
  };

}


#endif //CS621_PROJECT2_DSTPORTNUMBER_H