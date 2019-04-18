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

#include <vector>
#include <string>

#include "ns3/queue.h"
#include "ns3/ppp-header.h"
#include "ns3/ipv4-header.h"
#include "ns3/udp-header.h"

#include "TrafficClass.h"
#include "DestinationPortNumber.h"
//#include "../../src/point-to-point/model//ppp-header.h"

namespace ns3 {

enum QueueMode {
    QueueModePacket = 0,
    QueueModeByte = 1,
    };

/**
 * \ingroup queue
 *
 * \brief A FIFO packet queue that drops tail-end packets on overflow
 */
template <typename Item>
class DiffServ : public Queue<Item>
{
public:
  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId GetTypeId (void);
  /**
   * \brief DiffServ Constructor
   *
   * Creates a droptail queue with a maximum size of 100 packets by default
   */
  DiffServ ();

  virtual ~DiffServ ();

  virtual bool Enqueue (Ptr<Item> item);
  virtual Ptr<Item> Dequeue (void);
  virtual Ptr<Item> Remove (void);
  virtual Ptr<const Item> Peek (void) const;

private:
  using Queue<Item>::Head;
  using Queue<Item>::Tail;
  using Queue<Item>::DoEnqueue;
  using Queue<Item>::DoDequeue;
  using Queue<Item>::DoRemove;
  using Queue<Item>::DoPeek;

  NS_LOG_TEMPLATE_DECLARE;     //!< redefinition of the log component


  // variable
  QueueMode m_mode;
  std::vector<TrafficClass*> q_class;


  //function
public:
    void SetMode(QueueMode mode);
    QueueMode GetMode();
    Ptr<Packet> Schedule();
    void Classify(Ptr<Packet> p);
	void LoadConfig(std::string path);
	

};


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
  ;
  return tid;
}

template <typename Item>
DiffServ<Item>::DiffServ () :
  Queue<Item> (),
  NS_LOG_TEMPLATE_DEFINE ("DiffServ")
{
  NS_LOG_FUNCTION (this);
  LoadConfig("./load");
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

  return DoEnqueue (Tail (), item);
}

template <typename Item>
Ptr<Item>
DiffServ<Item>::Dequeue (void)
{
    NS_LOG_INFO (this  <<"  DiffServ Dequeue  <--------- ");


  Ptr<Item> item = DoDequeue (Head ());

  if ( item != NULL) {
    Ptr<Packet> p = (Ptr<Packet>)item;
	p = Schedule();
    Ptr<Packet> copy = p->Copy ();
	

	
	/*

    PppHeader ppp;
    NS_LOG_INFO ("PppHeader size:" << sizeof(ppp));
    NS_LOG_INFO ( "packet size before remove ppp "<<copy->GetSize() );
    copy->RemoveHeader (ppp);
    NS_LOG_INFO ( "packet size after remove ppp "<<copy->GetSize() );


    Ipv4Header iph;

    NS_LOG_INFO ( "packet size before remove ip4header "<<copy->GetSize() );
    copy->RemoveHeader (iph);
    NS_LOG_INFO ( "packet size after remove ip4header "<<copy->GetSize() );
    NS_LOG_INFO ("This is the IP header:" << iph);

     UdpHeader udpHeader;
     copy->RemoveHeader (udpHeader);
       NS_LOG_INFO ( "packet size after remove udpheader "<<copy->GetSize() );
       NS_LOG_INFO ("This is the UDP header:" << udpHeader);



     */

    NS_LOG_INFO (" Popped packet " << item << " packet size "<<p->GetSize() );
  }


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


    template <typename Item>
    Ptr<Packet> DiffServ<Item>::Schedule(){
        for (unsigned i=0; i<q_class.size(); i++){
            TrafficClass* trafficClass = q_class[0];
			trafficClass->print();
            Ptr<Packet> p = trafficClass->Dequeue();
            if (p != NULL) {
                return p;
            }
        }
        return NULL;
    }

    template <typename Item>
    void DiffServ<Item>::Classify(Ptr<Packet> p){
        for (unsigned i=0; i<q_class.size(); i++){
            TrafficClass* trafficClass = q_class[0];
            if(trafficClass->match(p)){
                trafficClass->Enqueue(p);
				trafficClass->print();
				return; // only insert once, inset high priority_queue
            }
        }
    }
	
	template <typename Item>
    void DiffServ<Item>::LoadConfig(std::string path){
        std::cout<<path <<std::endl;
		q_class.resize(2);
		
		TrafficClass* trafficClass = new TrafficClass(true);
		trafficClass->setPriorityLevel(0);
		//trafficClass->print();
		q_class[1] = trafficClass;
		
		
		DestinationPortNumber* element = new DestinationPortNumber(80);
		TrafficClass* trafficClass2 = new TrafficClass();
		Filter* filter = new Filter(1);
		filter->Insert(0, element);
		trafficClass2->resizeFilters(1);
		trafficClass2->insertFilter(0, filter);
		trafficClass2->setPriorityLevel(1);
		
		//trafficClass2->print();
		
		q_class[0] = trafficClass2;
		
		
		
		
    }

// The following explicit template instantiation declarations prevent all the
// translation units including this header file to implicitly instantiate the
// DiffServ<Packet> class and the DiffServ<QueueDiscItem> class. The
// unique instances of these classes are explicitly created through the macros
// NS_OBJECT_TEMPLATE_CLASS_DEFINE (DiffServ,Packet) and
// NS_OBJECT_TEMPLATE_CLASS_DEFINE (DiffServ,QueueDiscItem), which are included
// in drop-tail-queue.cc
extern template class DiffServ<Packet>;
//extern template class DiffServ<QueueDiscItem>;

} // namespace ns3

#endif /* DROPTAIL_H */
