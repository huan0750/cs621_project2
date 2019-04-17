#include "Filter.h"
#include "FilterElement.h"

namespace ns3 {

    class Filter {
        public:
            std::vector<FilterElement> elements;

            bool
            Filter::match (Ptr<Packet> p) {
                return true;
            };
    };
}

