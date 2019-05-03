#include "Config.h"



namespace ns3 {

    //todo




     int  Config::getTrafficClassSize(){
		 return list.size();
	 }
	 
	 
	 bool Config::load(std::string path){
		 		
		FilterElementConfig element;
		 element["type"] = "DestinationPortNumber";
		 element["protocol"] = "UDP";
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

	std::vector<ns3::TrafficClass*> Config::getTraffics(){
		return qConfig;

	}


	std::vector<ns3::TrafficClass*> Config::readFileJson(std::string path) {
		Json::CharReaderBuilder rbuilder;
		Json::Value root;
		std::string errs;
		std::ifstream config_doc(path, std::ifstream::binary);
		config_doc >> root;
		Json::parseFromStream (rbuilder, config_doc, &root, &errs);
		int num_queues = root["num_queues"].asInt();

		qConfig.resize(num_queues + 1);
		 
		 TrafficClass* trafficClass = new TrafficClass(true);
		 trafficClass->setPriorityLevel(0);
		 trafficClass->setWeight(400);
		 qConfig[num_queues] = trafficClass;    // size = 2, there are 3 queue, [2] == defualt 
		
		Json::Value traffic_array = root["traffic"];
		for(unsigned int i = 0; i < traffic_array.size(); i++)
                 {
                     TrafficClass* trafficClass = new TrafficClass(false);
					
					 
                     if (traffic_array[i].isMember("priority_level")){
                         int priority_level = traffic_array[i]["priority_level"].asInt();
                         trafficClass->setPriorityLevel(priority_level);
                     }
					 if (traffic_array[i].isMember("quantum")){
						 int quantum = traffic_array[i]["quantum"].asInt();
						 trafficClass->setWeight(quantum);
					 }

                     Json::Value filter_array = root["traffic"][i]["filters"];
					 
					 // todo       filters ==> filter 
					 // filters -->filter  -->filterelement

                     int filter_size = filter_array.size();
					 trafficClass->resizeFilters(filter_size);
                     

                     for(unsigned int j = 0; j < filter_array.size(); ++j){
                         Json::Value filter_elem_array = root["traffic"][i]["filters"][j]["filter"];

                         int filter_elem_size = filter_elem_array.size();
						 Filter* filter = new Filter(filter_elem_size);

                         for(unsigned int k = 0; k < filter_elem_array.size(); ++k){
							 std::string type = filter_elem_array[j]["type"].asString();
							 std::string protocol = filter_elem_array[j]["protocol"].asString();

                             
							 if((type.compare("DestinationPortNumber")) == 0){
								 int port = filter_elem_array[j]["port"].asInt();
								 DestinationPortNumber* element = new DestinationPortNumber(port, protocol);
								 filter->Insert(k, element);
							 }
							 if((type.compare("SourcePortNumber")) == 0){
								 int port = filter_elem_array[j]["port"].asInt();
								 SourcePortNumber* element = new SourcePortNumber(port, protocol);
								 filter->Insert(k, element);
							 }
							 if((type.compare("ProtocolNumber")) == 0){
								 int protocol_num = filter_elem_array[j]["protocol_num"].asInt();
								 ProtocolNumber* element = new ProtocolNumber(protocol_num, protocol);
								 filter->Insert(k, element);
							 }

							 if((type.compare("SourceMask")) == 0){
							 	 std::string ipv4_mask = filter_elem_array[j]["ipv4_mask"].asString();
								 std::string ipv4_address = filter_elem_array[j]["ipv4_address"].asString();
								 auto mask = ipv4_mask.c_str();
								 auto address = ipv4_address.c_str();

								 Ipv4Address* Ipaddress = new Ipv4Address(address);
								 Ipv4Mask* Ipmask = new Ipv4Mask(mask);
								 SourceMask* element = new SourceMask(*Ipaddress,*Ipmask,protocol);
								 filter->Insert(k, element);
							 }
							 if((type.compare("DestinationMask")) == 0){
								 std::string ipv4_mask = filter_elem_array[j]["ipv4_mask"].asString();
								 std::string ipv4_address = filter_elem_array[j]["ipv4_address"].asString();
								 auto mask = ipv4_mask.c_str();
								 auto address = ipv4_address.c_str();

								 Ipv4Address* Ipaddress = new Ipv4Address(address);
								 Ipv4Mask* Ipmask = new Ipv4Mask(mask);
								 DestinationMask* element = new DestinationMask(*Ipaddress,*Ipmask,protocol);
								 filter->Insert(k, element);
							 }
							 if((type.compare("DestinationIP")) == 0){
								 std::string ipv4_address = filter_elem_array[j]["ipv4_address"].asString();
								 auto address = ipv4_address.c_str();
								 Ipv4Address* Ipaddress = new Ipv4Address(address);
								 DestinationIP* element = new DestinationIP(*Ipaddress, protocol);
								 filter->Insert(k, element);
							 }
							 if((type.compare("SourceIP")) == 0){
								 std::string ipv4_address = filter_elem_array[j]["ipv4_address"].asString();
								 auto address = ipv4_address.c_str();
								 Ipv4Address* Ipaddress = new Ipv4Address(address);
								 SourceIP* element = new SourceIP(*Ipaddress, protocol);
								 filter->Insert(k, element);
							 }
                         }
                         trafficClass->insertFilter(j, filter);
                     }
                     qConfig[i] = trafficClass;
                 }
		return qConfig;
	}

}
