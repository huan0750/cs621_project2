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
				std::cout <<" elemetn size  "<< list.size() <<std::endl;
			       if(list.size() == 0 ) return false; 
				   
                   for(std::vector<FilterElement*>::iterator it = list.begin(); it != list.end(); it++){
					   FilterElement* element = *it;
					   if ( element->match(p) == false ) return false;
				   }
				   
				   return true;   // all elements pass match. so it is ok 
            }
   
}
