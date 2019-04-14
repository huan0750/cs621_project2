



#ifndef CS621_PROJECT2_FILTERELEMENT_H
#define CS621_PROJECT2_FILTERELEMENT_H

#endif //CS621_PROJECT2_FILTERELEMENT_H

class FilterElement{
    bool virtual match(Ptr<Packet> p)=0;
};