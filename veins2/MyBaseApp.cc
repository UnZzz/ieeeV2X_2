/*
 * MyBaseApp.cc
 *
 *  Created on: Jun 15, 2024
 *      Author: hakim
 */

#include "MyBaseApp.h"

#include "MyVeinsCarApp.h"

using namespace veins;

Define_Module(veins::MyBaseApp);
uint32_t MyBaseApp::totalGeneratedWSMs_inAllCars = 0;
void MyBaseApp::initialize(int stage)
{
    DemoBaseApplLayer::initialize(stage);
    if (stage == 0)
    {
        sendWSA = par("sendWSA").boolValue();
    }
}

MyBaseApp::~MyBaseApp()
{

}

void MyBaseApp::finish()
{
    DemoBaseApplLayer::finish();
    // statistics recording goes here
    //recordScalar("totalGeneratedWSMs_fromAllCars", totalGeneratedWSMs_inAllCars);
}

void MyBaseApp::populateWSM(BaseFrame1609_4* wsm, LAddress::L2Type rcvId, int serial)
{
    wsm->setSenderAddress(myId);
    DemoBaseApplLayer::populateWSM(wsm, rcvId,  serial);
}

