#ifndef CS621_PROJECT2_PROTOCOLNUMBER_H
#define CS621_PROJECT2_PROTOCOLNUMBER_H


#include <stdint.h>
#include "FilterElement.h"
#include "ns3/ipv4-address.h"

namespace ns3 {
    class ProtocolNumber : public FilterElement {
    private:
        int32_t protocol_num;
        std::string protocol;
    public:
        ProtocolNumber(int32_t protocol_num, std::string protocol) {
            this->protocol_num = protocol_num;
            this->protocol = protocol;
        }

        bool match(Ptr <Packet> p);
    };
}


#endif //CS621_PROJECT2_PROTOCOLNUMBER_H
