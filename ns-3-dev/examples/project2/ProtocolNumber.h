#ifndef CS621_PROJECT2_PROTOCOLNUMBER_H
#define CS621_PROJECT2_PROTOCOLNUMBER_H


#include <stdint.h>
#include "FilterElement.h"
#include "ns3/ipv4-address.h"

/**
 * match the protocal number of packet
 * for example UDP 17 (0x11)
 *
 */
namespace ns3 {
    class ProtocolNumber : public FilterElement {
    private:
        int32_t protocol_num;
    public:
        /**
         * Constructor
         *
         * @param protocol_num
         */
        ProtocolNumber(int32_t protocol_num) {
            this->protocol_num = protocol_num;
        }

        bool match(Ptr <Packet> p);
    };
}


#endif //CS621_PROJECT2_PROTOCOLNUMBER_H
