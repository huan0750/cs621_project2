
#ifndef CS621_PROJECT2_SOURCEMASK_H
#define CS621_PROJECT2_SOURCEMASK_H


#include <stdint.h>
#include "FilterElement.h"
#include "ns3/ipv4-address.h"


namespace ns3 {

    class SourceMask : public FilterElement {
    private:
        Ipv4Address start_address;
        Ipv4Mask mask;
        std::string protocol;
    public:
        /**
         * constructor
         *
         * @param start_address
         * @param mask
         * @param protocol
         */
        SourceMask(Ipv4Address start_address, Ipv4Mask mask, std::string protocol) {
            this->mask = mask;
            this->start_address = start_address;
            this->protocol = protocol;
        }

        /**
         * match the source ip range from start_address and mask
         * @param p
         * @return
         */
        bool match(Ptr <Packet> p);
    };

}


#endif //CS621_PROJECT2_SOURCEMASK_H
