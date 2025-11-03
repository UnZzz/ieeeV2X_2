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

#include "MyVeinsCarApp.h"
#include "MyVeinsRSUApp.h"

using namespace veins;

Define_Module(veins::MyVeinsCarApp);

const simsignal_t MyVeinsCarApp::generatedPktSignal = registerSignal("MyVeinsCarApp_app_sigPktGenTime");

void MyVeinsCarApp::initialize(int stage)
{
    MyBaseApp::initialize(stage);
    if (stage == 0) {
        // Initializing members and pointers of your application goes here
        sendWSMEvt = new cMessage("WSM evt", SEND_WSM_EVT);
        //hasStopped = false;
       // wsmInterval = SimTime(1000, SIMTIME_US) ;// par("wsmInterval").doubleValue();
        subscribedServiceSenderMAC = LAddress::L2BROADCAST();//9;


        //EV << "MyVeinsCarApp Initializing stage 0" << std::endl;
    }
    else if (stage == 1) {
       if (!dataOnSch)
        {
           wsmInterval =  simtime_t(par("wsmInterval").doubleValue(), SIMTIME_US);
           //EV << "wsmInterval = " << wsmInterval << std::endl;
            scheduleAt(simTime() + (wsmInterval), sendWSMEvt);
        }

        // Initializing members that require initialized other modules goes here
       //traciVehicle->setSpeedMode(0x1f);
       //traciVehicle->setSpeed(30);
    }
}

void MyVeinsCarApp::finish()
{
    MyBaseApp::finish();
    // statistics recording goes here
    //recordScalar("totalGenneratedPacketsByAllCars", gen_pkts_count);
}

void MyVeinsCarApp::onBSM(DemoSafetyMessage* bsm)
{
    MyBaseApp::onBSM(bsm);
    // Your application has received a beacon message from another car or RSU
    // code for handling the message goes here
    /*if (hasStopped == false)
    {
        traciVehicle->setSpeedMode(0x1f);
        traciVehicle->setSpeed(0);
        hasStopped = true;
    }
    else
    {
        traciVehicle->setSpeedMode(0x1f);
        traciVehicle->setSpeed(20);
        hasStopped =false;
    }*/
}

void MyVeinsCarApp::onWSM(BaseFrame1609_4* wsm)
{

   // if(wsm->getRecipientAddress()!=LAddress::L2BROADCAST())
    //{
   //     subscribedServiceSenderMAC = wsm->getSenderAddress();
    //}
    MyBaseApp::onWSM(wsm);
    // Your application has received a data message from another car or RSU
    // code for handling the message goes here, see TraciDemo11p.cc for examples
}

void MyVeinsCarApp::onWSA(DemoServiceAdvertisment* wsa)
{
    // Your application has received a service advertisement from another car or RSU
    // code for handling the message goes here, see TraciDemo11p.cc for examples
    int temp_currentSubscribedServiceId = currentSubscribedServiceId;
    if (currentSubscribedServiceId == -1)
    {
        //if(dataOnSch)
        mac->changeServiceChannel(static_cast<Channel>(wsa->getTargetChannel()));
        currentSubscribedServiceId = wsa->getPsid();
        //EV << "The service ad is received from "<< wsa->getSenderAddress() <<" with service ID= "<<  wsa->getPsid() << ", service channel is "<< wsa->getTargetChannel() << ", service description is "<< wsa->getServiceDescription()<< std::endl;
    }
    else if (currentSubscribedServiceId != wsa->getPsid())
    {
        stopService();
        //if(dataOnSch)
        mac->changeServiceChannel(static_cast<Channel>(wsa->getTargetChannel()));
        currentSubscribedServiceId = wsa->getPsid();
        //EV << "switching to a new service, A new service ad is received from "<< wsa->getSenderAddress() <<" with service ID= "<<  wsa->getPsid() << ", service channel is "<< wsa->getTargetChannel() << ", service description is "<< wsa->getServiceDescription()<< std::endl;

    }
    else
    {
        //EV << "a new service ad for the same service is received"<< std::endl;
    }
    if (temp_currentSubscribedServiceId != currentSubscribedServiceId)
    {
        cancelEvent(sendWSMEvt);
        subscribedServiceSenderMAC = (check_and_cast<BaseFrame1609_4*>(wsa))->getSenderAddress();
        wsmInterval = simtime_t(par("wsmInterval").doubleValue(), SIMTIME_US);
        //EV << "wsmInterval = " << wsmInterval << std::endl;
        scheduleAt(simTime() + wsmInterval, sendWSMEvt);

    }
}


void MyVeinsCarApp::handlePositionUpdate(cObject* obj)
{
    MyBaseApp::handlePositionUpdate(obj);
    // the vehicle has moved. Code that reacts to new positions goes here.
    // member variables such as currentPosition and currentSpeed are updated in the parent class
}

void MyVeinsCarApp::handleSelfMsg(cMessage* msg)
{

    if (msg->getKind() == SEND_WSM_EVT)
        prepareAppMessage();
    else
        MyBaseApp::handleSelfMsg(msg);

    // this method is for self messages (mostly timers)
    // it is important to call the MyBaseApp function for BSM and WSM transmission
}

void MyVeinsCarApp::prepareAppMessage()
{
    BaseFrame1609_4* wsm = new BaseFrame1609_4();
    populateWSM(wsm, dataOnSch? LAddress::L2BROADCAST():subscribedServiceSenderMAC);
    //EV << "emitting the signal " << generatedPktSignal << std::endl;
    emit(generatedPktSignal, (wsm->getCreationTime()).dbl() );
    totalGeneratedWSMs_inAllCars++;
    sendDown(wsm);

    simtime_t nextWSM = simTime();
    //simtime_t wsmInterval = SimTime(50, SIMTIME_MS);

    wsmInterval = simtime_t(par("wsmInterval").doubleValue(), SIMTIME_US);
    //EV << "wsmInterval = " << wsmInterval << std::endl;
    nextWSM = simTime() + wsmInterval;
    scheduleAt(nextWSM, sendWSMEvt);
}

MyVeinsCarApp::~MyVeinsCarApp()
{
    cancelAndDelete(sendWSMEvt);
}
