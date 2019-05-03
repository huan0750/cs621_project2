#ifndef CS621_PROJECT2_FILTER_H
#define CS621_PROJECT2_FILTER_H

#endif //CS621_PROJECT2_FILTER_H


#include <vector>
#include <stdint.h>
#include <queue>
#include "DestinationPortNumber.h"
#include "DestinationIP.h"
#include "DestinationMask.h"
#include "ProtocolNumber.h"
#include "SourceIP.h"
#include "SourceMask.h"
#include "SourcePortNumber.h"

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