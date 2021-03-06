#include "TrafficClass.h"

namespace ns3 {



    //constructor

    TrafficClass::TrafficClass(bool isDefault) {
        bytes = 0;
        packets = 0;
        max_bytes = 1024000;
        max_packets = 1000;
        m_queueMode = QueueModePacket;
        this->isDefault = isDefault;
    }


    bool TrafficClass::Enqueue(Ptr <Packet> p) {
        std::cout << "queue mode" << m_queueMode << " max_bytes " << max_bytes << " bytes " << bytes << std::endl;
        if (m_queueMode == QueueModeByte) {
            if (bytes + p->GetSize() <= max_bytes) {

                m_queue.push(p);
                bytes += p->GetSize();
                return true;
            } else {
                return false;
            }
        } else {
            if (packets + 1 <= max_packets) {
                m_queue.push(p);
                packets++;
                return true;
            } else {
                return false;
            }
        }
    }

    Ptr <Packet> TrafficClass::Dequeue() {
        if (m_queue.empty()) {
            return NULL;
        } else {
            Ptr <Packet> p = m_queue.front();
            m_queue.pop();
            if (m_queueMode == QueueModeByte) {
                bytes -= p->GetSize();
            } else {
                packets--;
            }
            return p;
        }
    }

    Ptr <Packet> TrafficClass::DequeueDrr() {
        if (m_queue.empty()) {
            return NULL;
        } else {
            Ptr <Packet> p = m_queue.front();
            double_t size = (double_t)(p->GetSize());
            if (size > weight) {
                return NULL;
            }
            m_queue.pop();
            if (m_queueMode == QueueModeByte) {
                bytes -= p->GetSize();
            } else {
                packets--;
            }
            weight -= size;
            return p;
        }
    }


    uint32_t TrafficClass::getBytes() {
        return this->bytes;

    }

    void TrafficClass::setBytes(uint32_t num) {
        this->bytes = num;

    }

    uint32_t TrafficClass::getPackets() {
        return this->packets;

    }

    void TrafficClass::setPackets(uint32_t num) {
        this->packets = num;

    }

    uint32_t TrafficClass::getMaxPackets() {
        return this->max_packets;

    }

    void TrafficClass::setMaxPackets(uint32_t num) {
        this->max_packets = num;

    }

    uint32_t TrafficClass::getMaxBytes() {
        return this->max_bytes;

    }

    void TrafficClass::setMaxBytes(uint32_t num) {
        this->max_bytes = num;

    }


    void TrafficClass::setPriorityLevel(uint32_t num) {
        this->priority_level = num;
    }

    uint32_t TrafficClass::getPriorityLevel() {
        return priority_level;
    }

    void TrafficClass::setWeight(double_t num) {
        this->weight = num;
    }

    void TrafficClass::addWeight(double_t num) {
        this->weight += num;
    }

    double_t TrafficClass::getWeight() {
        return this->weight;

    }


    bool TrafficClass::match(Ptr <Packet> p) {
        std::cout << "is default " << isDefault << " priority " << priority_level << std::endl;
        if (isDefault) return true;

        for (unsigned int i = 0; i < filters.size(); i++) {
            if (filters[i]->match(p) == true) {
                return true;
            }
        }

        return false;

    }


    void TrafficClass::resizeFilters(int size) {
        filters.resize(size);
    }

    void TrafficClass::insertFilter(int pos, ns3::Filter *filter) {
        filters[pos] = filter;

    }

    void TrafficClass::print() {
        std::cout << "traffic class queue size " << m_queue.size() << "  isDefault " << isDefault
                  << " priority_level " << priority_level << std::endl;
    }

}
