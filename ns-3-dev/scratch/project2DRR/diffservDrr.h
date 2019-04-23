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

#ifndef DROPTAIL_H
#define DROPTAIL_H

#include <algorithm>
#include <vector>
#include <string>


#include "ns3/queue.h"
#include "ns3/ppp-header.h"
#include "ns3/ipv4-header.h"
#include "ns3/udp-header.h"
#include "ns3/string.h"

#include "TrafficClass.h"
#include "DestinationPortNumber.h"

namespace ns3{
    /**
    * \ingroup queue
    *
    * \brief A FIFO packet queue that drops tail-end packets on overflow
    */
    template <typename Item>
    class DiffServDrr : public DiffServ<Item>
    {
    public:
    /**
    * \brief DiffServ Constructor
    *
    * Creates a droptail queue with a maximum size of 100 packets by default
    */
  DiffServDrr ();

  virtual ~DiffServDrr ();


private:
  using Queue<Item>::Head;
  using Queue<Item>::Tail;
  using Queue<Item>::DoEnqueue;
  using Queue<Item>::DoDequeue;
  using Queue<Item>::DoRemove;
  using Queue<Item>::DoPeek;

  NS_LOG_TEMPLATE_DECLARE;     //!< redefinition of the log component


  // variable
  std::vector<double_t> quantums;
  bool isLoad = false;
  int curTurn = 0;

  //function
public:
    Ptr<Packet> Schedule();
    void LoadConfig(std::string path);
    void nextTurn();

};

template <typename Item>
DiffServDrr<Item>::DiffServDrr () :
  DiffServ<Item> (),
  NS_LOG_TEMPLATE_DEFINE ("DiffServDrr")
{
  NS_LOG_FUNCTION (this);
  //isLoad = false;
 // LoadConfig("./load");
}

template <typename Item>
DiffServDrr<Item>::~DiffServDrr ()
{
  NS_LOG_FUNCTION (this);
}

template <typename Item>
    Ptr<Packet> DiffServDrr<Item>::Schedule(){
      TrafficClass* tc = q_class[curTurn];
      Ptr<Packet> p = tc->DequeueDrr();
      if(p != NULL){
        return p;
      } 
      nextTurn();
      return NULL;
    }

template <typename Item>
	void DiffServ<Item>::nextTurn(){
    //plus traffic quantum
    double_t quantum = quantums[curTurn];
    TrafficClass* tc = q_class[curTurn];
    tc->addWeight(quantum);
    curTurn = (curTurn + 1) % q_class.size();
	}

template <typename Item>
    void DiffServ<Item>::LoadConfig(std::string path){
		if (isLoad){
			std::cout<<"already load "<<path <<std::endl;
			return ;
		}
		
    std::cout<<this<<" ialoadSPQ  "<<isLoad<<path <<std::endl;
		q_class.resize(2);
		
		TrafficClass* trafficClass = new TrafficClass(true);
		trafficClass->setPriorityLevel(0);
		//trafficClass->print();
		q_class[1] = trafficClass;
		
		
		DestinationPortNumber* element = new DestinationPortNumber(53, "UDP");  // 53 DNS high priority 
		TrafficClass* trafficClass2 = new TrafficClass();
		Filter* filter = new Filter(1);
		filter->Insert(0, element);
		trafficClass2->resizeFilters(1);
		trafficClass2->insertFilter(0, filter);
		trafficClass2->setPriorityLevel(1);
		
		//trafficClass2->print();
		
		q_class[0] = trafficClass2;
		
		orderTrafficClassByPriority();
		printTrafficClass();
		isLoad = true;
		
    }


extern template class DiffServDrr<Packet>;

}

#endif /* DROPTAIL_H */

