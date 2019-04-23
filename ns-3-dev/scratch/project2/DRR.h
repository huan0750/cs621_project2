#ifndef CS621_PROJECT2_DRR_H
#define CS621_PROJECT2_DRR_H

#include "diffserv.h"

namespace ns3{

    template <typename Item>
    class DRR : public DiffServ<Item>{

        private:
        std::vector<double_t> quantums;
        int turn = 0;

        public:
        Ptr<Packet> Schedule();
        void LoadConfig(std::string path);
        void nextTurn();
    }

}

#endif