#include "TrafficClass.h"
namespace ns3 {

    //constructor

    TrafficClass::TrafficClass(bool isDefault) {
        this->isDefault = isDefault;
    }


    bool TrafficClass::Enqueue(Ptr <Packet> p) {
        m_queue.push(p);
        return true;
    }

    Ptr <Packet> TrafficClass::Dequeue() {
        if (m_queue.empty()) {
            return NULL;
        } else {
            Ptr <Packet> p = m_queue.front();
            m_queue.pop();

            return p;
        }


    }


    void TrafficClass::setBytes(uint32_t num) {
        this->bytes = num;

    }

    void TrafficClass::setPackets(uint32_t num) {
        this->packets = num;

    }

    void TrafficClass::setMaxPackets(uint32_t num) {
        this->max_packets = num;

    }

    void TrafficClass::setMaxBytes(uint32_t num) {
        this->max_bytes = num;

    }

    void TrafficClass::setPriorityLevel(uint32_t num) {
        this->priority_level = num;
    }
	
	uint32_t  TrafficClass::getPriorityLevel(){
		return priority_level;
	}

    void TrafficClass::setWeight(double_t num) {
        this->weight = num;
    }


    bool TrafficClass::match(Ptr <Packet> p) {
		std::cout<<"is default "<<isDefault << " priority "<<priority_level <<std::endl; 
		if(isDefault) return true; 
		
        for (unsigned int i = 0; i < filters.size(); i++) {
                if (filters[i]->match(p) == true) {
                    return true;
                }
        }

        return false;

    }
	
	void TrafficClass::resizeFilters(int size){
		filters.resize(size);	
	}
	
	void TrafficClass::insertFilter(int pos, ns3::Filter* filter){
		filters[pos] = filter;
		
	}
	
	void TrafficClass::print(){
		std::cout<<"traffic class queue size " <<m_queue.size() <<"  isDefault "<< isDefault 
		<< " priority_level "<< priority_level <<std::endl;
	}

}
