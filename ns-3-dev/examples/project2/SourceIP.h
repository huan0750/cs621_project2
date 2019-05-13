
#ifndef CS621_PROJECT2_SOURCEIP_H
#define CS621_PROJECT2_SOURCEIP_H


#include <stdint.h>
#include "FilterElement.h"
#include "ns3/ipv4-address.h"


namespace ns3 {

    class SourceIP : public FilterElement {
    private:
        Ipv4Address address;
        std::string protocol;
    public:
        /**
         * Constructor
         * @param ipv4_address
         * @param protocol
         */
        SourceIP(Ipv4Address ipv4_address, std::string protocol) {
            address = ipv4_address;
            this->protocol = protocol;
        }
        /**
         * match packet source IP
         * @param p
         * @return
         */
        bool match(Ptr <Packet> p);
    };

}


#endif //CS621_PROJECT2_SOURCEIP_H
