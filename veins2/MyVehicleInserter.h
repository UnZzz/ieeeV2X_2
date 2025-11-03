/*
 * MyVehicleInserter.h
 *
 *  Created on: Jun 5, 2024
 *      Author: hakim
 */

#ifndef MYVEHICLEINSERTER_H_
#define MYVEHICLEINSERTER_H_

#include "veins/modules/mobility/traci/TraCIVehicleInserter.h"

class MyVehicleInserter : public veins::TraCIVehicleInserter {
    protected:
        virtual void initialize(int stage) override;
};



#endif /* MYVEHICLEINSERTER_H_ */
