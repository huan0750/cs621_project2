#ifndef CS621_PROJECT2_TRAFFICCLASS_H
#define CS621_PROJECT2_TRAFFICCLASS_H



#include <stdint.h>
#include <queue>
#include <vector>
#include "ns3/queue.h"

#include "Filter.h"


namespace ns3 {
  class TrafficClass {
  private:
      uint32_t bytes;
      std::queue<Ptr<Packet>> m_queue;
      bool isDefault;
      ns3::Filter* fil;
      uint32_t packets;
      uint32_t max_bytes;
      uint32_t max_packets;
      double_t weight;
      uint32_t priority_level;
      std::vector<ns3::Filter*> filters;


  public:
      TrafficClass(bool isDefault = false);
	  void resizeFilters(int size);
	  void insertFilter(int pos, ns3::Filter* filter);
	  void print();
      bool Enqueue(Ptr<Packet> p);
      Ptr<Packet> Dequeue();
      bool match(Ptr<Packet> p);
      void setBytes(uint32_t num);
      void setPackets(uint32_t num);
      void setMaxPackets(uint32_t num);
      void setMaxBytes(uint32_t num);
      void setWeight(double_t num);
      void setPriorityLevel(uint32_t num);
      void setIsDefault(bool check);
  };
}


#endif //CS621_PROJECT2_TRAFFICCLASS_H