#ifndef CS621_PROJECT2_SPQ_H
#define CS621_PROJECT2_SPQ_H

#include "diffserv.h"

namespace ns3 {
	
template <typename Item>
	class DRR : public  DiffServ<Item> {
		private:
        using DiffServ<Item>::q_class;
		using DiffServ<Item>::quantums;
		int turn = 0;
	  
	  
		public:
        DRR();
		static TypeId GetTypeId (void);
		Ptr<Packet> Schedule();
		void nextTurn();
	};
  
  

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
                    MakeStringChecker())
  ;
  return tid;
}