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



	void readFileJson() {
		//Json::Reader reader;
		Json::CharReaderBuilder rbuilder;
		Json::Value root;
		std::string errs;
		std::ifstream config_doc("scratch/project2/spq.json", std::ifstream::binary);
		config_doc >> root;
		Json::parseFromStream (rbuilder, config_doc, &root, &errs);



//        q_class.resize(2);
//
//        TrafficClass* trafficClass = new TrafficClass(true);
//        trafficClass->setPriorityLevel(0);
//        //trafficClass->print();
//        q_class[1] = trafficClass;
//
//
//        DestinationPortNumber* element = new DestinationPortNumber(53, "UDP");  // 53 DNS heigh priority
//        TrafficClass* trafficClass2 = new TrafficClass();
//        Filter* filter = new Filter(1);
//        filter->Insert(0, element);
//        trafficClass2->resizeFilters(1);
//        trafficClass2->insertFilter(0, filter);
//        trafficClass2->setPriorityLevel(1);

        //trafficClass2->print();

        //q_class[0] = trafficClass2;

		//if (reader.parse(in, root)) {
            int num_queues = root["num_queues"].asInt();

            qConfig.resize(num_queues);

            Json::Value traffic_array = root["traffic"];
            cout << "array size = " << traffic_array.size() << endl;
            for(unsigned int i = 0; i < traffic_array.size(); i++)
                 {
                     TrafficClass* trafficClass = new TrafficClass(true);
                     if (traffic_array[i].isMember("priority_level")){
                         int priority_level = traffic_array[i]["priority_level"].asInt();
                         trafficClass->setPriorityLevel(priority_level);
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
                             int port = filter_elem_array[j]["port"].asInt();
                             DstPortNumber* element = new DstPortNumber(port, protocol);
                             filter->Insert(0, element);
                         }
                         trafficClass->insertFilter(0, filter);
                     }
                     qConfig[i] = trafficClass;

                 }

//
//
//			int priority_level_first = root["priority_level_first"].asInt();
//
//			cout << "priority level is" << priority_level_first << endl;
//
//			string type_first = root["type_element_first"]["type"].asString();
//			string protocol_first = root["type_element_first"]["protocol"].asString();
//			int port_first = root["type_element_first"]["port"].asInt();
//
//			cout << "type is " << type_first << endl;
//			cout << "protocol is " << protocol_first << endl;
//			cout << "port is " << port_first << endl;
//
//
//			cout << "Reading 1 is Complete!" << endl;
//
//			int priority_level_second = root["priority_level_second"].asInt();
//
//			cout << "priority level is" << priority_level_second << endl;
//
//			string type_second = root["type_element_second"]["type"].asString();
//			string protocol_second = root["type_element_second"]["protocol"].asString();
//			int port_second = root["type_element_second"]["port_second"].asInt();
//
//			cout << "second type is " << type_second << endl;
//			cout << "second protocol is " << protocol_second << endl;
//			cout << "second port is " << port_second << endl;
//
//
//			cout << "All Reading Complete!" << endl;
//		} else {
//			cout << "parse error\n" << endl;
//		}

		//in.close();
	}

}
