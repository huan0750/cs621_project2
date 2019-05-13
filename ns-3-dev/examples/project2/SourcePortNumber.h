
#ifndef CS621_PROJECT2_SOURCEPORTNUMBER_H
#define CS621_PROJECT2_SOURCEPORTNUMBER_H


#include <stdint.h>
#include "FilterElement.h"


namespace ns3 {

    class SourcePortNumber : public FilterElement {
    private:
        uint32_t port;
        std::string protocol;
    public:
        /**
         * constructor
         *
         * @param destination_port
         * @param protocol
         */
        SourcePortNumber(uint32_t destination_port, std::string protocol) {
            port = destination_port;
            this->protocol = protocol;
        }

        /**
         * match source packet port number
         *
         * @param p
         * @return
         */
        bool match(Ptr <Packet> p);
    };

}


#endif //CS621_PROJECT2_SOURCEPORTNUMBER_H
