#include "Config.h"
namespace ns3 {

    //todo 
     int  Config::getTrafficClassSize(){
		 return list.size();
	 }
	 
	 
	 bool Config::load(std::string path){
		 		
		FilterElementConfig element;
		 element["type"] = "DestinationPortNumber";
		 element["protocal"] = "UDP";
		 element["port"] = "80";
		 
		 
		 FilterConfig filter(1);
		 
		 filter[0] = element;
		 
		 TrafficClassConfig trafficClass(1);
		 trafficClass[0] = filter;
		 
		 list.resize(1);
		 list[0] = trafficClass;
		 return true;
		 
	 }
	 
     std::vector<TrafficClassConfig> Config::getTrafficClass(){

		 return list;
		 
		 
		 
	 }

}
