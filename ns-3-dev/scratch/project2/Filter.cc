#ifndef CS621_PROJECT2_FILTER_H
#define CS621_PROJECT2_FILTER_H

#endif //CS621_PROJECT2_FILTER_H

#include "Filter.h"

namespace ns3 {
	  
            Filter::Filter(int elementSize){
				list = std::vector<FilterElement*>(elementSize);
			}
			
			void Filter::Resize(int elementSize){
			    list.resize(elementSize);	
			}
			 
			 
			void Filter::Insert(int pos, FilterElement* element){
				if(pos >= 0 && pos < (int)list.size()){
					list[pos] = element;
				}
			}
			 
   
            bool  Filter::match (Ptr<Packet> p) {
                return true;
            };
   
}
