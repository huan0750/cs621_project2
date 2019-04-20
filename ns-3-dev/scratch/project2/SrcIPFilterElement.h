#include "ns3/ipv4-address.h"

class SrcIPFilterElement
{
private:
    Ipv4Address value;

public:
    bool match(Ptr<Packet> p);
};
