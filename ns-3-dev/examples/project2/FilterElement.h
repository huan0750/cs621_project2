#ifndef CS621_PROJECT2_FILTERELEMENT_H
#define CS621_PROJECT2_FILTERELEMENT_H


#include "ns3/queue.h"


namespace ns3 {

    class FilterElement {
    public:
        /*
         * if the filter element match will return true
         * implement in the child class for special matching logic
         *
         * /param p   packet
         */
        virtual bool match(Ptr <Packet> p) = 0;
    };
}


#endif //CS621_PROJECT2_FILTERELEMENT_H