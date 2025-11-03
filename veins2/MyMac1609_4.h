/*
 * MyMac1609_4.h
 *
 *  Created on: Jun 11, 2024
 *      Author: hakim
 */

#pragma once
#include <omnetpp.h>
#include "veins/veins.h"

#include "veins/modules/mac/ieee80211p/Mac1609_4.h"

using namespace omnetpp;

namespace veins {

class VEINS_API MyMac1609_4 : public Mac1609_4  {
public:
    void initialize(int stage) override;

    static const simsignal_t sigCarPktSent;
protected:

    int cwMIN_value;
    void setCW_Limits(ChannelType chType, int cwMIN_value = CWMIN_11P);
};

}



