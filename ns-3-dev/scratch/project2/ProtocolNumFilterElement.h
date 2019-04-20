#include "ns3/ipv4-address.h"

class ProtocolNumFilterElement
{
private:
    uint32_t value;

public:
    bool match(Ptr<Packet> p);
};
