/*
 * MyMac1609_4_forCar.cc
 *
 *  Created on: Jun 11, 2024
 *      Author: hakim
 */

#include "MyMac1609_4_forCar.h"

using namespace veins;

Define_Module(veins::MyMac1609_4_forCar);

void MyMac1609_4_forCar::sendFrame(Mac80211Pkt* frame, omnetpp::simtime_t delay, Channel channelNr, MCS mcs, double txPower_mW)
{
    simtime_t temp_delay = std::max(delay, RADIODELAY_11P);
    (check_and_cast<BaseFrame1609_4*>(frame->getEncapsulatedPacket()))->setSentTime(simTime()+temp_delay);
    //EV << "Sending a frame from a car" << std::endl;
    MyMac1609_4::sendFrame( frame,  delay,  channelNr,  mcs,  txPower_mW);
    if (dynamic_cast<Mac80211Ack*>(frame))
    {
        // an ack is sent
    }
    else // a data frame is sent
    {
        emit(MyMac1609_4::sigCarPktSent, true);
    }
}


