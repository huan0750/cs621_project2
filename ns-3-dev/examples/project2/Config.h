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
#include "DestinationPortNumber.h"
#include "DestinationIP.h"
#include "DestinationMask.h"
#include "ProtocolNumber.h"
#include "SourceIP.h"
#include "SourceMask.h"
#include "SourcePortNumber.h"
#include "ns3/ipv4-address.h"


#include <map>

typedef std::map<std::string, std::string>  FilterElementConfig;
typedef std::vector<FilterElementConfig>  FilterConfig;
typedef std::vector<FilterConfig> TrafficClassConfig;

namespace ns3 {

  class Config{

   private:
     std::vector<ns3::TrafficClass*> qConfig;
	 std::vector<TrafficClassConfig> list;



  public :
	  /*
	   * return the the number of traffic classes
	   */
	  int  getTrafficClassSize();

	  /*
	   *  read config of traffic class from json file, and return the vector of traffic class
	   */
	  std::vector<ns3::TrafficClass*> readFileJson(std::string path);
  };
}


#endif //CS621_PROJECT2_FILTERELEMENT_H