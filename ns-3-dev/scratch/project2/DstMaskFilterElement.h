#include "ns3/ipv4-address.h"

class DstMaskFilterElement
{
private:
    Ipv4Mask value;

public:
    bool match(Ptr<Packet> p);
};
