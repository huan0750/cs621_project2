#include "TrafficClass.h"
namespace ns3{

  //constructor

  TrafficClass::TrafficClass(bool isDefault){
       this->isDefault = isDefault;

  }




  bool TrafficClass::Enqueue(Ptr<Packet> p){
      m_queue.push(p);
      return true;
  }

  Ptr<Packet> TrafficClass::Dequeue(){
      if (m_queue.empty()){
          return NULL;
      }else{
            Ptr<Packet> p = m_queue.front();
            m_queue.pop();

            return p;
      }

  }
  bool TrafficClass::match(Ptr<Packet> p){
        return true;
  }


}
