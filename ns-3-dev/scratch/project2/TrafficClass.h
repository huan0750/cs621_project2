//
// Created by zhangyousong on 4/8/19.
//

#ifndef CS621_PROJECT2_TRAFFICCLASS_H
#define CS621_PROJECT2_TRAFFICCLASS_H

#endif //CS621_PROJECT2_TRAFFICCLASS_H

#include <stdint.h>
#include <queue>

#include "Filter.h"

using namespace ns3;

class TrafficClass {
private:
    ns3::Filter* fil;
    std::queue<Ptr<Packet>> m_queue;
    uint32_t bytes;
    uint32_t packets;
    uint32_t max_bytes;
    uint32_t max_packets;
    bool isDefault;
    double_t weight;
    uint32_t priority_level;
    std::queue<Ptr<Packet> > m_queue;
    std::vector<ns3::Filter*> filters;


public:
    TrafficClass(bool isDefault);
    bool Enqueue(Ptr<Packet> p);
    Ptr<Packet> Dequeue();
    void setBytes(uint32_t num);
    void setPackets(uint32_t num);
    void setMaxPackets(uint32_t num);
    void setMaxBytes(uint32_t num);
    void setWeight(double_t num);
    void setPriorityLevel(uint32_t num);
    void setIsDefault(bool check);
    bool match(Ptr<Packet> p);
}
