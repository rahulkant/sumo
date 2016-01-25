/****************************************************************************/
/// @file    MSSOTLPolicyBasedTrafficLightLogic.h
/// @author  Alessio Bonfietti
/// @author  Riccardo Belletti
/// @date    Feb 2014
/// @version $Id: MSSOTLPolicyBasedTrafficLightLogic.cpp 19623 2015-12-16 09:30:37Z behrisch $
///
// The class for SOTL Congestion logics
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

#include "MSSOTLPolicyBasedTrafficLightLogic.h"

MSSOTLPolicyBasedTrafficLightLogic::MSSOTLPolicyBasedTrafficLightLogic(
    MSTLLogicControl& tlcontrol, const std::string& id,
    const std::string& subid, const Phases& phases, unsigned int step,
    SUMOTime delay, const std::map<std::string, std::string>& parameters,
    MSSOTLPolicy* policy) throw() :
    MSSOTLTrafficLightLogic(tlcontrol, id, subid, phases, step, delay,
                            parameters), myPolicy(policy) {

    MsgHandler::getMessageInstance()->inform(
        "*** Intersection " + id + " will run using MSSOTL"
        + policy->getName() + "TrafficLightLogic ***");

}

MSSOTLPolicyBasedTrafficLightLogic::MSSOTLPolicyBasedTrafficLightLogic(
    MSTLLogicControl& tlcontrol, const std::string& id,
    const std::string& subid, const Phases& phases, unsigned int step,
    SUMOTime delay, const std::map<std::string, std::string>& parameters,
    MSSOTLPolicy* policy, MSSOTLSensors* sensors) throw() :
    MSSOTLTrafficLightLogic(tlcontrol, id, subid, phases, step, delay,
                            parameters, sensors), myPolicy(policy) {
}

MSSOTLPolicyBasedTrafficLightLogic::~MSSOTLPolicyBasedTrafficLightLogic(void) {

}

int MSSOTLPolicyBasedTrafficLightLogic::decideNextPhase() {

    DBG(
        std::ostringstream str; str << "\n" << time2string(MSNet::getInstance()->getCurrentTimeStep()) << " " << getID() << "invoked MSSOTLPolicyBasedTrafficLightLogic::decideNextPhase()"; WRITE_MESSAGE(str.str());)

    return myPolicy->decideNextPhase(getCurrentPhaseElapsed(),
                                     &getCurrentPhaseDef(), getCurrentPhaseIndex(),
                                     getPhaseIndexWithMaxCTS(), isThresholdPassed(), isPushButtonPressed(),
                                     countVehicles(getCurrentPhaseDef()));
}

bool MSSOTLPolicyBasedTrafficLightLogic::canRelease() throw() {

    DBG(
        std::ostringstream str; str << "\n" << time2string(MSNet::getInstance()->getCurrentTimeStep()) << " " << getID() << "invoked MSSOTLPolicyBasedTrafficLightLogic::canRelease()"; WRITE_MESSAGE(str.str());)

    return myPolicy->canRelease(getCurrentPhaseElapsed(), isThresholdPassed(), isPushButtonPressed(),
                                &getCurrentPhaseDef(), countVehicles(getCurrentPhaseDef()));
}