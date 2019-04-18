
#ifndef CS621_PROJECT2_DETINATIONPORTNUMBER_H
#define CS621_PROJECT2_DETINATIONPORTNUMBER_H



#include <stdint.h>
#include "FilterElement.h"


namespace ns3 {

  class DestinationPortNumber : public FilterElement{
  private:
      uint32_t port;
  public:
      DestinationPortNumber(uint32_t destination_port){
          port = destination_port;
      }
      bool match(Ptr<Packet> p){
        return true;
    }
  };

}


#endif //CS621_PROJECT2_DETINATIONPORTNUMBER_H
