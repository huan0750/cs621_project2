
#ifndef CS621_PROJECT2_FILTER_H
#define CS621_PROJECT2_FILTER_H

#endif //CS621_PROJECT2_FILTER_H

#include "Filter.h"

namespace ns3 {

    /*
    * the constructor of filter
    */
    Filter::Filter(int elementSize) {
        list = std::vector<FilterElement *>(elementSize);
    }

    /**
     * provide the function to resize the element size
     * */
    void Filter::Resize(int elementSize) {
        list.resize(elementSize);
    }


    /**
     * insert a new filter element into the filter list
     * */
    void Filter::Insert(int pos, FilterElement *element) {
        if (pos >= 0 && pos < (int) list.size()) {
            list[pos] = element;
        }
    }


    /**
     * return true if all the packet properties matches all the filter elements
     * */
    bool Filter::match(Ptr <Packet> p) {
        std::cout << " elemetn size  " << list.size() << std::endl;
        if (list.size() == 0) return false;

        for (std::vector<FilterElement *>::iterator it = list.begin(); it != list.end(); it++) {
            FilterElement *element = *it;
            if (element->match(p) == false) return false;
        }

        return true;   // all elements pass match. so it is ok
    }

}
