#ifndef CS621_PROJECT2_SPQ_H
#define CS621_PROJECT2_SPQ_H

#include "diffserv.h"


namespace ns3 {


    template<typename Item>
    class SPQ : public DiffServ<Item> {


    private:
        using DiffServ<Item>::q_class;

    public:
        // contructor
        SPQ();

        static TypeId GetTypeId(void);
        /*
         * SPQ implement Schedule with SPQ logic
         */
        virtual Ptr <Packet> Schedule();
    };


    template<typename Item>
    TypeId
    SPQ<Item>::GetTypeId(void) {
        static TypeId tid = TypeId(("ns3::SPQ<" + GetTypeParamName<SPQ<Item> >() + ">").c_str())
                                    .SetParent < Queue < Item > > ()
                                    .SetGroupName("Network")
                                    .template AddConstructor<SPQ<Item> >()
                                    .AddAttribute("ConfigPath",
                                                  "The path of config file.",
                                                  StringValue("config.txt"),
                                                  MakeStringAccessor(&DiffServ<Item>::LoadConfig),
                                                  MakeStringChecker());
        return tid;
    }


}

#endif //CS621_PROJECT2_FILTER_H