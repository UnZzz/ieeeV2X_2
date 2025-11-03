/*
 * MyVehicleInserter.cc
 *
 *  Created on: Jun 5, 2024
 *      Author: hakim
 */

#include "../veins2/MyVehicleInserter.h"

#include "veins/modules/mobility/traci/TraCIMobility.h"
#include "veins/modules/mobility/traci/TraCICommandInterface.h"
#include "veins/modules/mobility/traci/TraCIConnection.h"

Define_Module(MyVehicleInserter);

void MyVehicleInserter::initialize(int stage) {
     veins::TraCIVehicleInserter::initialize(stage);

    if (stage == 0) {
        numVehicles = par("numVehicles").intValue();

    } else if (stage == 1)
    {

      /*  // Get the TraCI Command Interface
        veins::TraCIMobility* mobility = veins::TraCIMobilityAccess().get(getParentModule());
        if (!mobility) {
            throw cRuntimeError("Unable to access TraCIMobility");
        }
        veins::TraCICommandInterface* traci = mobility->getCommandInterface();
        if (!traci) {
            throw cRuntimeError("Unable to access TraCICommandInterface");
        }

        for (int i = 0; i < numVehicles; ++i) {
            std::stringstream vehicleId;
            vehicleId << "vehicle_" << i;
            traci->addVehicle(vehicleId.str(), "route_0", 0, 0, 0);
        }*/
    }
}
/*void MyVehicleInserter::initialize(int stage) {
    veins::TraCIVehicleInserter::initialize(stage);
    if (stage == 0) {
        numVehicles = par("numVehicles").intValue();
    }
    else if (stage == 1) {
        for (int i = 0; i < numVehicles; ++i) {
            std::stringstream vehicleId;
            vehicleId << "vehicle_" << i;
            traciVehicleManager->commandAddVehicle(vehicleId.str(), "route_0", 0, 0, 0, "", 0);


        }
    }
}*/



