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

		qConfig.resize(num_queues);
		Json::Value traffic_array = root["traffic"];
		for(unsigned int i = 0; i < traffic_array.size(); i++)
                 {
                     TrafficClass* trafficClass = new TrafficClass(true);
					 if (traffic_array[i].isMember("ifDefault")){
						 bool ifDefault = traffic_array[i]["ifDefault"].asBool();
						 trafficClass = new TrafficClass(ifDefault);
					 }
                     if (traffic_array[i].isMember("priority_level")){
                         int priority_level = traffic_array[i]["priority_level"].asInt();
                         trafficClass->setPriorityLevel(priority_level);
                     }
					 if (traffic_array[i].isMember("quantum")){
						 int quantum = traffic_array[i]["quantum"].asInt();
						 trafficClass->setWeight(quantum);
					 }

                     Json::Value filter_array = root["traffic"][i]["filters"];

                     int filter_size = filter_array.size();
                     Filter* filter = new Filter(filter_size);

                     for(unsigned int j = 0; j < filter_array.size(); ++j){
                         Json::Value filter_elem_array = root["traffic"][i]["filters"][j]["filter_element"];

                         //int filter_elem_size = filter_elem_array.size();

                         for(unsigned int k = 0; k < filter_elem_array.size(); ++k){
							 std::string type = filter_elem_array[j]["type"].asString();
							 std::string protocol = filter_elem_array[j]["protocol"].asString();

							 if((type.compare("DestinationPortNumber")) == 0){
								 int port = filter_elem_array[j]["port"].asInt();
								 DstPortNumber* element = new DstPortNumber(port, protocol);
								 filter->Insert(0, element);
							 }
							 if((type.compare("SourcePortNumber")) == 0){
								 int port = filter_elem_array[j]["port"].asInt();
								 SrcPortNumber* element = new SrcPortNumber(port, protocol);
								 filter->Insert(0, element);
							 }
							 if((type.compare("ProtocolNumber")) == 0){
								 int protocol_num = filter_elem_array[j]["protocol_num"].asInt();
								 ProtocolNum* element = new ProtocolNum(protocol_num, protocol);
								 filter->Insert(0, element);
							 }

							 if((type.compare("SourceMask")) == 0){
//							 	 std::string ipv4_mask = filter_elem_array[j]["ipv4_mask"].asString();
//								 Ipv4Address* address = new Ipv4Address(ipv4_mask);
//								 SrcMask* element = new SrcMask(address, protocol);
//								 filter->Insert(0, element);
							 }
							 if((type.compare("DestinationMask")) == 0){
//								 std::string ipv4_mask = filter_elem_array[j]["ipv4_mask"].asString();
//								 Ipv4Address* address = new Ipv4Address(ipv4_mask);
//								 DstMask* element = new DstMask(address, protocol);
//								 filter->Insert(0, element);
							 }
							 if((type.compare("DestinationIP")) == 0){
//								 std::string ipv4_mask = filter_elem_array[j]["ipv4_mask"].asString();
//								 Ipv4Address* address = new Ipv4Address(ipv4_mask);
//								 DstIP* element = new DstIP(address, protocol);
//								 filter->Insert(0, element);
							 }
							 if((type.compare("SourceIP")) == 0){
//								 std::string ipv4_mask = filter_elem_array[j]["ipv4_mask"].asString();
//								 Ipv4Address* address = new Ipv4Address(ipv4_mask);
//								 SrcIP* element = new SrcIP(address, protocol);
//								 filter->Insert(0, element);
							 }
                         }
                         trafficClass->insertFilter(0, filter);
                     }
                     trafficClass = qConfig[i];
                 }
		return qConfig;
	}

}
