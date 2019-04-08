
#ifndef CS621_PROJECT2_DETINATIONPORTNUMBER_H
#define CS621_PROJECT2_DETINATIONPORTNUMBER_H

#endif //CS621_PROJECT2_DETINATIONPORTNUMBER_H

#include <stdint.h>

class DestinationPortNumber : public FilterElemet {
private:
    uint32_t port;
public:
    DestinationPortNumber(uint32_t destination_port){
        port = destination_port;
    }


};