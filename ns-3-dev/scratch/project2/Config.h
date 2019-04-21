#ifndef CS621_PROJECT2_CONFIG_H
#define CS621_PROJECT2_CONFIG_H


#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <stdint.h>

#include "ns3/queue.h"
#include "src/json/json.h"
#include "TrafficClass.h"
#include "DstPortNumber.h"
#include "DstIP.h"
#include "DstMask.h"
#include "ProtocolNum.h"
//#include "SrcIP.h"
#include "SrcMask.h"
#include "SrcPortNumber.h"
#include "ns3/ipv4-address.h"


#include <map>

typedef std::map<std::string, std::string>  FilterElementConfig;
typedef std::vector<FilterElementConfig>  FilterConfig;
typedef std::vector<FilterConfig> TrafficClassConfig;

namespace ns3 {

  class Config{
//  public:
//     Config();
     
	 
   private:
     std::vector<ns3::TrafficClass*> qConfig;
	 std::vector<TrafficClassConfig> list;



  public :
      bool load(std::string path);
	  int  getTrafficClassSize();
	  std::vector<TrafficClassConfig> getTrafficClass();
	  std::vector<ns3::TrafficClass*> readFileJson(std::string path);
	  std::vector<ns3::TrafficClass*> getTraffics();
  };
}


#endif //CS621_PROJECT2_FILTERELEMENT_H