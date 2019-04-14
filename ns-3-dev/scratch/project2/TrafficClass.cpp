

#include "TrafficClass.h"




//constructor

TrafficClass::TrafficClass(bool isDefault){
     this->isDefault = isDefault;

}


bool TrafficClass::Enqueue(Ptr<Packet> p){
    m_queue.push(p);
}

Ptr<Packet> TrafficClass::Dequeue(){
    if (m_queue.empty()){
        return NULL;
    }else{
        return m_queue.pop();
    }

}

//– bytes - the count of bytes in the queue.
//– packets - the count of packets in the queue.
//– maxPackets - the maximum number of packets allowed in the queue.
//– maxBytes - the maximum number of bytes allowed in the queue.

void TrafficClass::setBytes(uint32_t num){
    this->bytes = num;

}

void TrafficClass::setPackets(uint32_t num){
    this->packets = num;

}

void TrafficClass::setMaxPackets(uint32_t num){
    this->max_packets = num;

}

void TrafficClass::setMaxBytes(uint32_t num){
    this->max_bytes = num;

}

void TrafficClass::setPriorityLevel(uint32_t num){
    this->priority_level = num;
}

void TrafficClass::setWeight(double_t num){
	this->weight = num;
}


bool TrafficClass::match(Ptr<Packet> p){
    bool check = true;
    for(unsigned int i=0; i<filters.size(); i++){
        for(unsigned int j=0; j<filters[i]->element.size(); j++){
            if(filters[i]->element[j]->match(p) == false){
                check = false;
                break;
            }
        }
        if(check)
            return true;
    }

    return false;

}