
#include "SPQ.h"

namespace ns3 {
     NS_LOG_COMPONENT_DEFINE ("SPQ");

    NS_OBJECT_TEMPLATE_CLASS_DEFINE (SPQ,Packet);
	
	 
	 template <typename Item>	  
      Ptr<Packet> DRR<Item>::Schedule(){
			 std::cout <<"schedule test"<<std::endl;
		 return NULL;
	 }
	 
	 template<typename Item>
	 void DRR<Item>::nextTurn(){
		std::cout <<"nextTurn test"<<std::endl;
		 
	 }
	 
	 template <typename Item>
	TypeId
	DRR<Item>::GetTypeId (void)
	{
		static TypeId tid = TypeId (("ns3::DRR<" + GetTypeParamName<DRR<Item> > () + ">").c_str ())
		.SetParent<Queue<Item> > ()
		.SetGroupName ("Network")
		.template AddConstructor<DiffServ<Item> > ()
		.AddAttribute ("ConfigPath",
                    "The path of config file.",
                    StringValue ("drr.json"),
					
                    MakeStringAccessor(&DiffServ<Item>::LoadConfig),
                    MakeStringChecker());
		return tid;
	}
   
}
