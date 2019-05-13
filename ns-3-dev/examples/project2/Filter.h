#ifndef CS621_PROJECT2_FILTER_H
#define CS621_PROJECT2_FILTER_H

#endif //CS621_PROJECT2_FILTER_H


#include <vector>
#include <stdint.h>
#include <queue>
#include "DestinationPortNumber.h"
#include "DestinationIP.h"
#include "DestinationMask.h"
#include "ProtocolNumber.h"
#include "SourceIP.h"
#include "SourceMask.h"
#include "SourcePortNumber.h"

#include "FilterElement.h"


namespace ns3 {
    class Filter {
    private:
        std::vector<FilterElement *> list;


    public:
        /**
         * Constructor of Filter
         * @param elementSize
         */
        Filter(int elementSize);

        /*
         * resize number of  elementSize
         *
         * /param  elementSize  size of elementSize
         *
         */
        void Resize(int elementSize);

        /*
         * insert filter element at position of vector
         *
         * /param  pos  pos of vector of FilterElement
         * /param  element  filter element
         *
         */
        void Insert(int pos, FilterElement *element);

        /*
         * check packet satisfied all filter elements
         *
         * return true when the packet matches all filter elements rules
         *
         */
        bool match(Ptr <Packet> p);


    };
}
