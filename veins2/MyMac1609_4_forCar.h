/*
 * MyMac1609_4_forCar.h
 *
 *  Created on: Jun 11, 2024
 *      Author: hakim
 */

#pragma once
#include <omnetpp.h>
#include "veins/veins.h"

#include "MyMac1609_4.h"

using namespace omnetpp;

namespace veins {

class VEINS_API MyMac1609_4_forCar : public MyMac1609_4  {
public:

protected:
    void sendFrame(Mac80211Pkt* frame, omnetpp::simtime_t delay, Channel channelNr, MCS mcs, double txPower_mW) override;

};

}



