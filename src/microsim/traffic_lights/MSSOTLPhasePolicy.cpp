/****************************************************************************/
/// @file    MSSOTLPhasePolicy.cpp
/// @author  Gianfilippo Slager
/// @author  Federico Caselli
/// @date    Feb 2010
/// @version $Id: MSSOTLPhasePolicy.cpp 19610 2015-12-14 21:03:17Z behrisch $
///
// The class for SOTL Phase logics
/****************************************************************************/
// SUMO, Simulation of Urban MObility; see http://sumo.dlr.de/
// Copyright 2001-2009 DLR (http://www.dlr.de/) and contributors
/****************************************************************************/
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or
//   (at your option) any later version.
//
/****************************************************************************/

#include "MSSOTLPhasePolicy.h"
#include <math.h>
#include "utils/common/RandHelper.h"


MSSOTLPhasePolicy::MSSOTLPhasePolicy(const std::map<std::string, std::string>& parameters) :
    MSSOTLPolicy("Phase", parameters) {
    init();
}

MSSOTLPhasePolicy::MSSOTLPhasePolicy(MSSOTLPolicyDesirability* desirabilityAlgorithm) :
    MSSOTLPolicy("Phase", desirabilityAlgorithm) {
    getDesirabilityAlgorithm()->setKeyPrefix("PHASE");
    init();
}

MSSOTLPhasePolicy::MSSOTLPhasePolicy(MSSOTLPolicyDesirability* desirabilityAlgorithm,
                                     const std::map<std::string, std::string>& parameters) :
    MSSOTLPolicy("Phase", desirabilityAlgorithm, parameters) {
    getDesirabilityAlgorithm()->setKeyPrefix("PHASE");
    init();
}

bool MSSOTLPhasePolicy::canRelease(SUMOTime elapsed, bool thresholdPassed, bool pushButtonPressed,
                                   const MSPhaseDefinition* stage, int vehicleCount) {
//  DBG(
    std::ostringstream str;
    str << "MSSOTLPhasePolicy::canRelease threshold " << thresholdPassed << " vehicle " << vehicleCount << " elapsed " << elapsed << " min " << stage->minDuration;
    WRITE_MESSAGE(str.str());
//          );
    if (elapsed >= stage->minDuration) {
        if (pushButtonLogic(elapsed, pushButtonPressed, stage)) {
            return true;
        }
        if (thresholdPassed) {
            return thresholdPassed;
        } else if (m_useVehicleTypesWeights) {
            if (sigmoidLogic(elapsed, stage, vehicleCount)) {
                return true;
            }
        }
    }
    return false;
}

void MSSOTLPhasePolicy::init() {
    PushButtonLogic::init("MSSOTLPhasePolicy", this);
    SigmoidLogic::init("MSSOTLPhasePolicy", this);
    m_useVehicleTypesWeights = getParameter("USE_VEHICLE_TYPES_WEIGHTS", "0") == "1";
}
