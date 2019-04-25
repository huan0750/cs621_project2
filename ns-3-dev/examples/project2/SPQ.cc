
#include "SPQ.h"

namespace ns3 {
     NS_LOG_COMPONENT_DEFINE ("SPQ");

    NS_OBJECT_TEMPLATE_CLASS_DEFINE (SPQ,Packet);
	
	 
	 template <typename Item>	  
      Ptr<Packet> SPQ<Item>::Schedule(){
			 std::cout <<"this is a test"<<std::endl;
		 return NULL;
	 }
   
}
