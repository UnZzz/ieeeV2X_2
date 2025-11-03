/*
 * MyBaseApp.h
 *
 *  Created on: Jun 15, 2024
 *      Author: hakim
 */

#pragma once
#include <omnetpp.h>
#include "veins/veins.h"

#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"

using namespace omnetpp;

namespace veins {

class VEINS_API MyBaseApp : public DemoBaseApplLayer {
public:
    ~MyBaseApp() override;
    void initialize(int stage) override;
    void finish() override;
    //void receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj, cObject* details) override;

    enum DemoApplMessageKinds {
        SEND_BEACON_EVT,
        SEND_WSA_EVT,
        SEND_WSM_EVT
    };

protected:
    /** @brief sets all the necessary fields in the WSM, BSM, or WSA. */
    void populateWSM(BaseFrame1609_4* wsm, LAddress::L2Type rcvId = LAddress::L2BROADCAST(), int serial = 0) override;
    bool sendWSA;
    static uint32_t totalGeneratedWSMs_inAllCars;
};

}
