#ifndef CS621_PROJECT2_TRAFFICCLASS_H
#define CS621_PROJECT2_TRAFFICCLASS_H


#include <stdint.h>
#include <queue>
#include <vector>
#include "ns3/queue.h"

#include "Filter.h"

enum QueueMode {
    QueueModePacket = 0,
    QueueModeByte = 1,
};
namespace ns3 {
    class TrafficClass {
    private:
        uint32_t bytes;
        std::queue <Ptr<Packet>> m_queue;
        bool isDefault;
        ns3::Filter *fil;
        uint32_t packets;
        uint32_t max_bytes;
        uint32_t max_packets;
        double_t weight;
        uint32_t priority_level;
        std::vector<ns3::Filter *> filters;
        QueueMode m_queueMode;


    public:
        /**
         * Constructor
         *
         * @param isDefault   default traffic when packet no match other traffic will come here
         */
        TrafficClass(bool isDefault = false);

        /**
         * resize the filter vector size
         *
         * @param size
         */
        void resizeFilters(int size);

        /**
         * insert the filter at postion of vector Filters
         *
         * @param pos
         * @param filter
         */
        void insertFilter(int pos, ns3::Filter *filter);


        /**
         * print traffic for debug
         */
        void print();

        /**
         * push a packet to the traffic queue, when the queue reaches the max size.
         * the packet will be dropped.
         *
         * @param p
         * @return
         */
        bool Enqueue(Ptr <Packet> p);


        /**
         * pop a packet out of the traffic queue, if queue is empty will return NULL
         *
         * @return
         */
        Ptr <Packet> Dequeue();

        /**
         * if packet match this traffic class rules , will return true. or return false
         * Filter || Filter || ...
         *
         * \param p packet
         *
         */
        bool match(Ptr <Packet> p);

        uint32_t getBytes();

        void setBytes(uint32_t num);

        uint32_t getPackets();

        void setPackets(uint32_t num);

        uint32_t getMaxPackets();

        /**
         * set max packets number
         * @param num
         */
        void setMaxPackets(uint32_t num);

        /**
         * set max byts
         * @return
         */
        uint32_t getMaxBytes();

        void setMaxBytes(uint32_t num);

        double_t getWeight();

        void setWeight(double_t num);

        /**
         * return priority level
         * @return
         */
        uint32_t getPriorityLevel();

        // set priority level of traffic class for SPQ
        void setPriorityLevel(uint32_t num);

        void setIsDefault(bool check);

        void addWeight(double_t num);

        /**
         * dequeue for DRR
         * @return
         */
        Ptr <Packet> DequeueDrr();
    };
}


#endif //CS621_PROJECT2_TRAFFICCLASS_H