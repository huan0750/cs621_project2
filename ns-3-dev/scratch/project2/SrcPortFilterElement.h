#include "ns3/ipv4-address.h"

class SrcPortFilterElement
{
private:
    uint32_t value;

public:
    bool match(Ptr<Packet> p);
};
