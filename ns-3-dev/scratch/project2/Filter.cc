#include "Filter.h"
#include "FilterElement.h"

namespace ns3 {

    class Filter {
        public:
            Filter ();
            virtual ~Filter ();
            
            std::vector<FilterElement> elements;

            bool
            Filter::match (Ptr<Packet> p) {
                return true;
            };
    };
}

