/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2007 University of Washington
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "diffserv.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("DiffServ");

NS_OBJECT_TEMPLATE_CLASS_DEFINE (DiffServ,Packet);


	bool compareTrafficClass(TrafficClass* a,  TrafficClass*  b){
		return b->getPriorityLevel() < a->getPriorityLevel();
	}
	
	/**
 * Implementation of the templates declared above.
 */

template <typename Item>
TypeId
DiffServ<Item>::GetTypeId (void)
{
  static TypeId tid = TypeId (("ns3::DiffServ<" + GetTypeParamName<DiffServ<Item> > () + ">").c_str ())
    .SetParent<Queue<Item> > ()
    .SetGroupName ("Network")
    .template AddConstructor<DiffServ<Item> > ()
    .AddAttribute ("ConfigPath",
                    "The path of config file.",
                    StringValue ("config.txt"),
                    MakeStringAccessor(&DiffServ<Item>::LoadConfig),
                    MakeStringChecker())
  ;
  return tid;
}

template <typename Item>
DiffServ<Item>::DiffServ () :
  Queue<Item> (),
  NS_LOG_TEMPLATE_DEFINE ("DiffServ")
{
  NS_LOG_FUNCTION (this);
  //isLoad = false;
 // LoadConfig("./load");
}

template <typename Item>
DiffServ<Item>::~DiffServ ()
{
  NS_LOG_FUNCTION (this);
}

template <typename Item>
bool
DiffServ<Item>::Enqueue (Ptr<Item> item)
{
  NS_LOG_INFO (this << item <<"  DiffServ Enqueue------> ");
    Ptr<Packet> p = (Ptr<Packet>)item;
    Classify(p);
    return true;
  //return DoEnqueue (Tail (), item);
}

template <typename Item>
Ptr<Item>
DiffServ<Item>::Dequeue (void)
{
    NS_LOG_INFO (this  <<"  DiffServ Dequeue  <--------- ");
    Ptr<Item>  item = Schedule();
    return item;
}

template <typename Item>
Ptr<Item>
DiffServ<Item>::Remove (void)
{
  NS_LOG_FUNCTION (this);

  Ptr<Item> item = DoRemove (Head ());

  NS_LOG_LOGIC ("Removed " << item);

  return item;
}

template <typename Item>
Ptr<const Item>
DiffServ<Item>::Peek (void) const
{
  NS_LOG_FUNCTION (this);

  return DoPeek (Head ());
}


 //   template <typename Item>
 //   Ptr<Packet> DiffServ<Item>::Schedule(){/
//
 //   }

    template <typename Item>
    Ptr<Packet> DiffServ<Item>::ScheduleDrr(){
      TrafficClass* tc = q_class[curTurn];
      Ptr<Packet> p = tc->DequeueDrr();
      if(p != NULL){
        return p;
      } 
      nextTurn();
      return NULL;
    }

    template <typename Item>
    void DiffServ<Item>::Classify(Ptr<Packet> p){
        for (unsigned i=0; i<q_class.size(); i++){
            TrafficClass* trafficClass = q_class[i];		
            if(trafficClass->match(p)){
                trafficClass->Enqueue(p);
				        std::cout << ">>>>>>>>>>>packet  insert to queue with priority_level "<< trafficClass->getPriorityLevel()<<std::endl;
				        return; // only insert once, inset high priority_queue
            }
        }
    }
	
	template <typename Item>
    void DiffServ<Item>::LoadConfig(std::string path){
		if (isLoad){
			std::cout<<"already load "<<path <<std::endl;
			return ;
		}
       std::cout<<this<<"DiffServ----------> isload  "<<isLoad<<path <<std::endl;
	   Config config;
	   q_class = config.readFileJson(path);
	   
	   quantums.resize(q_class.size());
	   for(unsigned int i = 0; i < q_class.size(); i++){
		   quantums[i] = q_class[i] ->getWeight();
	   }
	   
	   
	   orderTrafficClassByPriority();
	   printTrafficClass();
	   isLoad = true;
	   return ;		
    }
	
	template <typename Item>
	void DiffServ<Item>::orderTrafficClassByPriority(){
		std::sort(q_class.begin(), q_class.end(), compareTrafficClass);
	}

	//template <typename Item>
	//void DiffServ<Item>::nextTurn(){
    //plus traffic quantum
    //double_t quantum = quantums[curTurn];
    //TrafficClass* tc = q_class[curTurn];
    //tc->addWeight(quantum);
    //curTurn = (curTurn + 1) % q_class.size();
	//}
	
	template <typename Item>
	void DiffServ<Item>::printTrafficClass(){
		for(std::vector<TrafficClass*>::iterator it = q_class.begin(); it != q_class.end(); it++ ){
			TrafficClass* c = *it;
			std::cout << " trafficClass  priority  : "<< c->getPriorityLevel()<<std::endl;
		}
	}

	  template <typename Item>
	 Ptr<Packet> DiffServ<Item>::Schedule(){
		   std::cout<<"this should never be called"<<std::endl;
		   return NULL;
		
	}

// The following explicit template instantiation declarations prevent all the
// translation units including this header file to implicitly instantiate the
// DiffServ<Packet> class and the DiffServ<QueueDiscItem> class. The
// unique instances of these classes are explicitly created through the macros
// NS_OBJECT_TEMPLATE_CLASS_DEFINE (DiffServ,Packet) and
// NS_OBJECT_TEMPLATE_CLASS_DEFINE (DiffServ,QueueDiscItem), which are included
// in drop-tail-queue.cc
//extern template class DiffServ<Packet>;
//extern template class DiffServ<QueueDiscItem>;

//NS_OBJECT_TEMPLATE_CLASS_DEFINE (DiffServ,QueueDiscItem);

} // namespace ns3



