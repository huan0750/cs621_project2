#ifndef CS621_PROJECT2_CONFIG_H
#define CS621_PROJECT2_CONFIG_H



#include "ns3/queue.h"
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

  public :
      bool load(std::string path);
	  int  getTrafficClassSize();
	  std::vector<TrafficClassConfig> getTrafficClass();
  };
}


#endif //CS621_PROJECT2_FILTERELEMENT_H