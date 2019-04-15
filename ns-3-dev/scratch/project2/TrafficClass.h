#ifndef CS621_PROJECT2_TRAFFICCLASS_H
#define CS621_PROJECT2_TRAFFICCLASS_H

#endif //CS621_PROJECT2_TRAFFICCLASS_H

#include <stdint.h>
#include <queue>
#include "ns3/queue.h"

namespace ns3 {
  class TrafficClass {
  private:
      uint32_t bytes;
      std::queue<Ptr<Packet>> m_queue;
      bool isDefault;


  public:
      TrafficClass(bool isDefault);
      bool Enqueue(Ptr<Packet> p);
      Ptr<Packet> Dequeue();
      bool match(Ptr<Packet> p);
  };
}
