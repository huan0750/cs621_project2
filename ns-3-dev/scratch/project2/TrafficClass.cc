

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
bool TrafficClass::match(Ptr<Packet> p){

}