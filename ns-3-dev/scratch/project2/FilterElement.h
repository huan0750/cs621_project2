#include "ns3/queue.h"

namespace ns3 {
  class FilterElement{
  public:
       virtual bool match(Ptr<Packet> p) = 0;
  };

}
