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
#include "Config.h"
#include "DestinationPortNumber.h"
//#include "../../src/point-to-point/model//ppp-header.h"

namespace ns3 {

enum QueueMode {
    QueueModePacket = 0,
    QueueModeByte = 1,
    };
	
	bool compareTrafficClass(TrafficClass* a,  TrafficClass*  b);

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

public:
  using Queue<Item>::Head;
  using Queue<Item>::Tail;
  using Queue<Item>::DoEnqueue;
  using Queue<Item>::DoDequeue;
  using Queue<Item>::DoRemove;
  using Queue<Item>::DoPeek;

  NS_LOG_TEMPLATE_DECLARE;     //!< redefinition of the log component


  // variable
 public:
  QueueMode m_mode;
  std::vector<TrafficClass*> q_class;
  std::vector<double_t> quantums;
  bool isLoad = false;
  

  //function
public:
    void SetMode(QueueMode mode);
    QueueMode GetMode();
    virtual Ptr<Packet> Schedule();
    //Ptr<Packet> ScheduleDrr();
    void Classify(Ptr<Packet> p);
	void LoadConfig(std::string path);
	void orderTrafficClassByPriority(); 
	void printTrafficClass();
    //void nextTurn();

};


} // namespace ns3



#endif /* DROPTAIL_H */
