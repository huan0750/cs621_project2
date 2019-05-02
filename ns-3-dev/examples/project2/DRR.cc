#include "DRR.h"

namespace ns3{

    NS_LOG_COMPONENT_DEFINE ("DRR");

    NS_OBJECT_TEMPLATE_CLASS_DEFINE (DRR,Packet);

    template <typename Item>	  
    DRR<Item>::DRR(){
		std::cout<<"DRR construct "<<std::endl;
	}

    template <typename Item>
    Ptr<Packet> Drr<Item>::Schedule(){
      TrafficClass* tc = q_class[curTurn];
      Ptr<Packet> p = tc->DequeueDrr();
      if(p != NULL){
        return p;
      } 
      nextTurn();
      return NULL;
    }

    template <typename Item>
	void Drr<Item>::nextTurn(){
        //plus traffic quantum
        double_t quantum = quantums[curTurn];
        TrafficClass* tc = q_class[curTurn];
        tc->addWeight(quantum);
        curTurn = (curTurn + 1) % q_class.size();
	}

    // template <typename Item>
    // void Drr<Item>::LoadConfig(std::string path){
		// if (isLoad){
		// 	std::cout<<"already load "<<path <<std::endl;
		// 	return ;
		// }

        // std::cout<<this<<" ialoadSPQ  "<<isLoad<<path <<std::endl;
		// q_class.resize(2);

		// TrafficClass* trafficClass = new TrafficClass(true);
		// trafficClass->setPriorityLevel(0);
		// //trafficClass->print();
		// q_class[1] = trafficClass;


		// DestinationPortNumber* element = new DestinationPortNumber(53, "UDP");  // 53 DNS high priority 
		// TrafficClass* trafficClass2 = new TrafficClass();
		// Filter* filter = new Filter(1);
		// filter->Insert(0, element);
		// trafficClass2->resizeFilters(1);
		// trafficClass2->insertFilter(0, filter);
		// trafficClass2->setPriorityLevel(1);

		// //trafficClass2->print();

		// q_class[0] = trafficClass2;

		// orderTrafficClassByPriority();
		// printTrafficClass();
		// isLoad = true;

    // }
}