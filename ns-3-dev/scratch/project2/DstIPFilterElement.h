#include "ns3/ipv4-address.h"

class DstIPFilterElement
{
private:
    Ipv4Address value;

public:
    bool match(Ptr<Packet> p);
};
