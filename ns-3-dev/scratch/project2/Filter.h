#include "FilterElement.h"

#ifndef CS621_PROJECT2_FILTER_H
#define CS621_PROJECT2_FILTER_H

#endif //CS621_PROJECT2_FILTER_H

class Filter{
private:
    std::vector<FilterElement*> list;


public:
bool match(Ptr<Packet> p);
};
