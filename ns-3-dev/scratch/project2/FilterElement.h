#ifndef CS621_PROJECT2_FILTERELEMENT_H
#define CS621_PROJECT2_FILTERELEMENT_H



#include "ns3/queue.h"


namespace ns3 {

  class FilterElement{
  public:
     // FilterElement ();
     // virtual ~FilterElement ();

      virtual bool match(Ptr<Packet> p) = 0;
  };
}


#endif //CS621_PROJECT2_FILTERELEMENT_H