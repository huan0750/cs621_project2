
#include "SPQ.h"

namespace ns3 {

    NS_LOG_COMPONENT_DEFINE ("SPQ");

    NS_OBJECT_TEMPLATE_CLASS_DEFINE (SPQ, Packet);

    template<typename Item>
    SPQ<Item>::SPQ() {
        std::cout << "SPQ construct " << std::endl;
    }

    template<typename Item>
    Ptr <Packet> SPQ<Item>::Schedule() {
        for (unsigned i = 0; i < q_class.size(); i++) {
            TrafficClass *trafficClass = q_class[i];
            Ptr <Packet> p = trafficClass->Dequeue();
            if (p != NULL) {
                std::cout << "<<<<<<<<<<<[SPQ] packet  dequeue from  queue  priority_level "
                          << trafficClass->getPriorityLevel() << std::endl;
                return p;
            }
        }

        return NULL;
    }


}
