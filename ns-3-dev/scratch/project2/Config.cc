//#include "Config.h"



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



//	void readFileJson() {
//		Json::Reader reader;
//		Json::Value root;
//
//		ifstream in("test.json", ios::binary);
//
//		if (!in.is_open()) {
//			cout << "Error opening file\n";
//			return;
//		}
//
//		/*
//        //test.json content：
//        {
//            "priority_level":"1",
//             "filter":[
//             	"filters":
//            	{
//					"type":"DestinationPortNumber",
//                	"protocol":"UDP",
//                	"port":80
//            	},
//            	"filters":
//            	{
//					"type":"DestinationPortNumber",
//                	"protocol":"UDP",
//                	"port":80
//            	}
//            ]
//            "filters":
//            {
//                "type":"DestinationPortNumber",
//                "protocol":"UDP",
//                "port":80
//            },
//			"priority_level_second":"2",
//            "type_element_second":
//            {
//                "type":"DestinationPortNumber",
//                "protocol":"UDP",
//                "port":80
//            }
//        }
//        */
//
//		if (reader.parse(in, root)) {
//
//			//string name = root["name"].asString();
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
//
//		in.close();
//	}

}
