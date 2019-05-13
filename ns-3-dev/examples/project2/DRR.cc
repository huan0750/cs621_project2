#include "DRR.h"

namespace ns3{

    NS_LOG_COMPONENT_DEFINE ("DRR");

    NS_OBJECT_TEMPLATE_CLASS_DEFINE (DRR,Packet);

    /**
     * the constructor of DRR
     * */
    template <typename Item>	  
    DRR<Item>::DRR(){
		std::cout<<"DRR construct "<<std::endl;
	}

    /**
     * the schedule function of DRR,
     * override the function of the super class diffserv,
     * try to fetch a packet from traffic queues and return that packet
     * */
    template <typename Item>
    Ptr<Packet> DRR<Item>::Schedule(){
        // first pick the traffic queue by the turn
      TrafficClass* tc = q_class[turn];
      //try to fetch a packet out of the queue
      Ptr<Packet> p = tc->DequeueDrr();
      if(p != NULL){
          // if the packet is not null, then return this packet
		   std::cout << "**********[DRR] get a packet from "<< tc->getWeight()<<std::endl;
        return p;
      } 
      // if the packet is null, then go to next turn
	  std::cout << "**********cur turn: "<<turn<<std::endl;
      nextTurn();
      return NULL;
    }

    /**
     * the next turn function,
     * would be called at the end of schedule function,
     * add the quantum to the according traffic queue
     * and increase the turn value
     * */
    template <typename Item>
	void DRR<Item>::nextTurn(){
        //plus traffic quantum
        double_t quantum = quantums[turn];
        TrafficClass* tc = q_class[turn];
        tc->addWeight(quantum);
        turn = (turn + 1) % q_class.size();
		std::cout << "**********next turn: "<<turn<<std::endl;
	}

}