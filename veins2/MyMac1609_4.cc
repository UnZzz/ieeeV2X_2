/*
 * MyMac1609_4.cc
 *
 *  Created on: Jun 11, 2024
 *      Author: hakim
 */

#include "MyMac1609_4.h"

using namespace veins;

Define_Module(veins::MyMac1609_4);
const simsignal_t MyMac1609_4::sigCarPktSent = registerSignal("Mycar2x_veins_modules_MyMac_sigPktSent");


void MyMac1609_4::initialize(int stage)
{
    //EV << "Initializing MyMac1609_4" << std::endl;
    Mac1609_4::initialize(stage);
    if (stage == 0)
    {
        cwMIN_value = par("cwMIN_value");
        setCW_Limits(ChannelType::control , cwMIN_value);
        setCW_Limits(ChannelType::service , cwMIN_value);
    }
}



void MyMac1609_4::setCW_Limits(ChannelType chType, int cwMIN_value)
{
    for (auto&& p : myEDCA[chType]->myQueues)
    {
        auto& accessCategory = p.first;
        auto& edcaQueue = p.second;
        switch(accessCategory)
        {
        case AC_BK:
            edcaQueue.cwMin=std::round(cwMIN_value);
            edcaQueue.cwMax=CWMAX_11P;
             break;
        case AC_BE:
            edcaQueue.cwMin=std::round(cwMIN_value);
            edcaQueue.cwMax=CWMAX_11P;
            break;
        case AC_VI:
            edcaQueue.cwMin=std::round(((cwMIN_value + 1) / 2.0) - 1);
            edcaQueue.cwMax=std::round(cwMIN_value);
            break;
        case AC_VO:
            edcaQueue.cwMin=std::round(((cwMIN_value + 1) / 4.0) - 1);
            edcaQueue.cwMax=std::round(((cwMIN_value + 1) / 2.0) - 1);
            break;
        }
        //EV << "Channel Type is " << (chType==ChannelType::control? "control":"service" )<< ", access category is " << accessCategory<< ", cwMin = "<<edcaQueue.cwMin<< ", cwMax = "<< edcaQueue.cwMax<< std::endl;
    }
}
