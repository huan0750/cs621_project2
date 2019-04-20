#include "ns3/ipv4-address.h"

class SrcMaskFilterElement
{
private:
    Ipv4Mask value;

public:
    bool match(Ptr<Packet> p);
};
