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

#include <map>

typedef std::map<std::string, std::string>  FilterElementConfig;
typedef std::vector<FilterElementConfig>  FilterConfig;
typedef std::vector<FilterConfig> TrafficClassConfig;

namespace ns3 {

  class Config{
  public:
     Config();
     
	 
   private:
	 std::vector<TrafficClassConfig> list;
	 std::vector<ns3::TrafficClass*> q_class;

  public :
      bool load(std::string path);
	  int  getTrafficClassSize();
	  std::vector<TrafficClassConfig> getTrafficClass();
	  void readFileJson();
  };
}


#endif //CS621_PROJECT2_FILTERELEMENT_H