#ifndef CS621_PROJECT2_DRR_H
#define CS621_PROJECT2_DRR_H

#include "diffserv.h"

namespace ns3 {
	
template <typename Item>
	class DRR : public  DiffServ<Item> {
		private:
        using DiffServ<Item>::q_class;
		using DiffServ<Item>::quantums;
		int turn = 0; // initial the turn to be 0
	  
	  
		public:
        /**
        * the constructor of DRR
        * */
        DRR();

        /**
        * the template function which should be called 
        * when the simulator instantiate the queue into the application
        * */
		static TypeId GetTypeId (void);

        /**
        * the schedule function of DRR,
        * override the function of the super class diffserv,
        * try to fetch a packet from traffic queues and return that packet
        * */
		Ptr<Packet> Schedule();

        /**
        * the next turn function,
        * would be called at the end of schedule function,
        * add the quantum to the according traffic queue
        * and increase the turn value
        * */
		void nextTurn();
	};
  
  

/**
 * the template function which should be called 
 * when the simulator instantiate the queue into the application
 * */
template <typename Item>
TypeId
DRR<Item>::GetTypeId (void)
{
  static TypeId tid = TypeId (("ns3::DRR<" + GetTypeParamName<DRR<Item> > () + ">").c_str ())
    .SetParent<Queue<Item> > ()
    .SetGroupName ("Network")
    .template AddConstructor<DRR<Item> > ()
    .AddAttribute ("ConfigPath",
                    "The path of config file.",
                    StringValue ("drr.json"),
					
                    MakeStringAccessor(&DiffServ<Item>::LoadConfig),
                    MakeStringChecker())
  ;
  return tid;
}
}
#endif //CS621_PROJECT2_FILTER_H