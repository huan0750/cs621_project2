#ifndef CS621_PROJECT2_FILTER_H
#define CS621_PROJECT2_FILTER_H

#endif //CS621_PROJECT2_FILTER_H


#include <vector>
#include <stdint.h>
#include <queue>
#include "DstPortNumber.h"
#include "DstIP.h"
#include "DstMask.h"
#include "ProtocolNum.h"
#include "SrcIP.h"
#include "SrcMask.h"
#include "SrcPortNumber.h"

#include "FilterElement.h"





namespace ns3 {
  class Filter{
  private:
      std::vector<FilterElement*> list;


  public:
      Filter(int elementSize);
	  void Resize(int elementSize);
      void Insert(int pos, FilterElement* element);
      bool match(Ptr<Packet> p);
  
  
  };
}
