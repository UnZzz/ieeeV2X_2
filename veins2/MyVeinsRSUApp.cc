//
// Copyright (C) 2016 David Eckhoff <david.eckhoff@fau.de>
//
// Documentation for these modules is at http://veins.car2x.org/
//
// SPDX-License-Identifier: GPL-2.0-or-later
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#include "MyVeinsRSUApp.h"
#include "MyMac1609_4.h"
#include <cmath>
//#include "MyVeinsCarApp.h"

using namespace veins;

Define_Module(veins::MyVeinsRSUApp);

void MyVeinsRSUApp::initialize(int stage)
{
    MyBaseApp::initialize(stage);
    if (stage == 0) {
        // Initializing members and pointers of your application goes here
        pktDelaySignal = registerSignal("MyVeinsRSUApp_app_sigPktDelay");
        receivedPktGenTimeSignal = registerSignal("MyVeinsRSUApp_app_sigReceivedPktGenTime");
        receivedPktSendTimeSignal = registerSignal("MyVeinsRSUApp_app_sigReceivedPktSendTime");
        totalReveivedWSMs =0;
        totalPacketsDelay=0.0;
        total_sent_pkts_byAllCars = 0;


        //EV << "Initializing " << par("appName").stringValue() << std::endl;

    }
    else if (stage == 1) {
        // Initializing members that require initialized other modules goes here

        //findHost()->subscribe(MyMac1609_4::sigCarPktSent, this);
        getSimulation()->getSystemModule()->subscribe(MyMac1609_4::sigCarPktSent, this);

        if(sendWSA && dataOnSch)
            startService(Channel::sch1, 1 , "my service");
    }

}

MyVeinsRSUApp::~MyVeinsRSUApp()
{
    findHost()->unsubscribe(MyMac1609_4::sigCarPktSent, this);
}

void MyVeinsRSUApp::finish()
{
    MyBaseApp::finish();
    // statistics recording goes here
    //recordScalar("totalGeneratedWSMs_fromAllCars", totalGeneratedWSMs_inAllCars);
    recordScalar("totalGeneratedWSMs_fromAllCars", totalGeneratedWSMs_inAllCars);
    recordScalar("totalReceivedWSMs_fromAllCars", totalReveivedWSMs);
    recordScalar("average_delay", totalReveivedWSMs == 0? (totalGeneratedWSMs_inAllCars > 0 ? SimTime::getMaxTime() :0 ): (totalPacketsDelay*1.0) / totalReveivedWSMs);
    recordScalar("aPDR", totalGeneratedWSMs_inAllCars == 0? 0 : (totalReveivedWSMs*1.0) / totalGeneratedWSMs_inAllCars);
    recordScalar("totalSentPackets_byAllCars", total_sent_pkts_byAllCars);
    recordScalar("mPDR", total_sent_pkts_byAllCars ==0? 0 : (totalReveivedWSMs*1.0) / total_sent_pkts_byAllCars);
}

void MyVeinsRSUApp::onBSM(DemoSafetyMessage* bsm)
{
    MyBaseApp::onBSM(bsm);
    //this->stopService();
    // Your application has received a beacon message from another car or RSU
    // code for handling the message goes here

}

void MyVeinsRSUApp::onWSM(BaseFrame1609_4* wsm)
{
    //if(!dataOnSch && wsm->getRecipientAddress()==LAddress::L2BROADCAST() )
    //{
    //    BaseFrame1609_4* new_wsm = new BaseFrame1609_4();
   //     populateWSM(new_wsm, wsm->getSenderAddress());
    //    sendDown(new_wsm);
    //}

    simtime_t pktdelay = simTime() - wsm->getCreationTime();
    emit(pktDelaySignal, pktdelay.dbl());
    emit(receivedPktGenTimeSignal, (wsm->getCreationTime()).dbl());
    emit(receivedPktSendTimeSignal, wsm->getSentTime().dbl());
    totalPacketsDelay= totalPacketsDelay + pktdelay;
    totalReveivedWSMs++;
    MyBaseApp::onWSM(wsm);
    // Your application has received a data message from another car or RSU
    // code for handling the message goes here, see TraciDemo11p.cc for examples
}

void MyVeinsRSUApp::onWSA(DemoServiceAdvertisment* wsa)
{
    MyBaseApp::onWSA(wsa);
    // Your application has received a service advertisement from another car or RSU
    // code for handling the message goes here, see TraciDemo11p.cc for examples
}

void MyVeinsRSUApp::receiveSignal(cComponent* source, simsignal_t signalID,  bool obj, cObject* details)
{
    if (signalID == MyMac1609_4::sigCarPktSent)
    {
        total_sent_pkts_byAllCars++;
    }
   // else
        //MyBaseApp::receiveSignal(source,  signalID, obj,  details);
}

