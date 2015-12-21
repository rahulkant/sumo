/****************************************************************************/
/// @file    MSSOTLTrafficLightLogic.h
/// @author  Gianfilippo Slager
/// @author	 Anna Chiara Bellini
/// @author  Federico Caselli
/// @date    Apr 2013
/// @version $Id: MSSOTLTrafficLightLogic.h 19623 2015-12-16 09:30:37Z behrisch $
///
// The base abstract class for SOTL logics
/****************************************************************************/
// SUMO, Simulation of Urban MObility; see http://sumo.dlr.de/
// Copyright 2001-2013 DLR (http://www.dlr.de/) and contributors
/****************************************************************************/
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or
//   (at your option) any later version.
//
/****************************************************************************/
#ifndef MSSOTLTrafficLightLogic_h
#define MSSOTLTrafficLightLogic_h

// ===========================================================================
// included modules
// ===========================================================================
#ifdef _MSC_VER
#include <windows_config.h>
#else
#include <config.h>
#endif

#include <utils/common/SwarmDebug.h>

#include <utils/common/SUMOTime.h>
#include "MSSOTLDefinitions.h"
#include "MSPhasedTrafficLightLogic.h"
#include "MSSOTLE2Sensors.h"
#include <utils/common/RandHelper.h>
#include <utils/common/TplConvert.h>


// ===========================================================================
// class declarations
// ===========================================================================
class MSPushButton;


// ===========================================================================
// class definitions
// ===========================================================================

/**
 * @class MSSOTLTrafficLightLogic
 * @brief A self-organizing traffic light logic
 *
 * The base class for SOTL traffic light which switches between
 * its phases and sets the lights to red in between.
 * Some functions are called with an information about the current step. This
 * is needed as a single logic may be used by many junctions and so the current
 * step is stored within them, not within methods.
 * Basically a SOTL logic overrides the natural flow of steps in order and length
 * according to sensors on input (and output) lanes
 */
class MSSOTLTrafficLightLogic: public MSPhasedTrafficLightLogic {
public:
    // typedef unsigned int CTS;

    /**
     * @brief Constructor without sensors passed
     * @param[in] tlcontrol The tls control responsible for this tls
     * @param[in] id This traffic light id
     * @param[in] subid This tls' sub-id (program id)
     * @param[in] phases Definitions of the phases
     * @param[in] step The initial phase index
     * @param[in] delay The time to wait before the first switch
     * @param[in] parameters Parameters defined for the tll
     */
    MSSOTLTrafficLightLogic(MSTLLogicControl& tlcontrol, const std::string& id,
                            const std::string& subid, const Phases& phases, unsigned int step,
                            SUMOTime delay,
                            const std::map<std::string, std::string>& parameters);

    /**
     * @brief Constructor with sensors passed
     * @param[in] tlcontrol The tls control responsible for this tls
     * @param[in] id This tls' id
     * @param[in] subid This tls' sub-id (program id)
     * @param[in] phases Definitions of the phases
     * @param[in] step The initial phase index
     * @param[in] delay The time to wait before the first switch
     * @param[in] parameters Parameters defined for the tll
     * @param[in] sensors The already defined sensor logic
     */
    MSSOTLTrafficLightLogic(MSTLLogicControl& tlcontrol, const std::string& id,
                            const std::string& subid, const Phases& phases, unsigned int step,
                            SUMOTime delay,
                            const std::map<std::string, std::string>& parameters,
                            MSSOTLSensors* sensors);

    /// @brief Destructor
    ~MSSOTLTrafficLightLogic();

    /**
     * @brief Initialises the tls with sensors on incoming and outgoing lanes
     * Sensors are built in the simulation according to the type of sensor specified in the simulation parameter
     * @param[in] nb The detector builder
     * @exception ProcessError If something fails on initialisation
     */
    void init(NLDetectorBuilder& nb) throw(ProcessError);

    /*
     * This member implements the base operations for all SOTL logics.
     * SOTL politics are implementated through decidePhase() member
     * @see MSTrafficLightLogic::trySwitch
     */
    SUMOTime trySwitch();

protected:

    typedef std::map<const std::string, std::vector<MSPushButton*> > PhasePushButtons;
    PhasePushButtons m_pushButtons;

    void logStatus();
    /*
     * This member has to contain the switching logic for SOTL policies
     */

    virtual int decideNextPhase();

    virtual bool canRelease() = 0;

    SUMOTime getCurrentPhaseElapsed();

    /*
     * Count the number of vehicles approaching the target lanes for the given phase.
     * If the phase in not a target phase the function member will return 0.
     * @param[in] The target phase index
     */
    int countVehicles(MSPhaseDefinition phase);

    /*
     * Every target step except the one from the current chain is checked.
     * This is because the current chain is not eligible to be directly
     * targeted again, it would be unfair.
     * @return True if at least a target phase has passed the threshold for input cars-timesteps
     */
    bool isThresholdPassed();

    /**
     * @breef Checks the if the pushbutton was activated for the current stage
     * @return True if at least a push button was pressed
     */
    bool isPushButtonPressed();

    int getThreshold() {
        return TplConvert::_2int(getParameter("THRESHOLD", "10").c_str());
    }

    SUMOReal getSpeedThreshold() {
        return TplConvert::_2SUMOReal(getParameter("THRESHOLDSPEED", "2").c_str());
    }

    SUMOReal getInputSensorsLength() {
        return TplConvert::_2SUMOReal(getParameter("INSENSORSLENGTH", "100").c_str());
    }

    SUMOReal getOutputSensorsLength() {
        return TplConvert::_2SUMOReal(getParameter("OUTSENSORSLENGTH", "80").c_str());
    }

    /*
     * Every target step except the one from the current chain is checked.
     * This is because the current chain is not eligible to be directly
     * targeted again, it would be unfair.
     * @return The index of the phase with the maximum value of cars-timesteps
     */
    int getPhaseIndexWithMaxCTS();

    MSSOTLSensors* getSensors() {
        return mySensors;
    }

    /**
     *\brief Return the sensors that count the passage of vehicles in and out of the tl.
     */
    MSSOTLE2Sensors* getCountSensors() {
        return myCountSensors;
    }
    /*
     * Computes how much time will pass after decideNextPhase will be executed again
     */
    virtual SUMOTime computeReturnTime() {
        if (getCurrentPhaseDef().isTransient()) {
            return getCurrentPhaseDef().duration;

        }
        return DELTA_T;

    }


private:
    /*
     * Pointer to the sensor logic regarding the junction controlled by this SOTLTrafficLightLogic
     */
    MSSOTLSensors* mySensors;

    /*
     * Pointer to the sensor logic regarding the count of the vehicles that pass into a tl.
     */
    MSSOTLE2Sensors* myCountSensors;

    /*
     * When true means the class has responsibilities to intantiate and delete the SOTLSensors instance,
     * otherwise MSSOTLTrafficLightLogic::init and MSSOTLTrafficLightLogic::~MSSOTLTrafficLightLogic have not to affect SOTLSensors instance lifecycle
     */
    bool sensorsSelfBuilt;

    // The map to store the cars*timesteps for each target phase
    std::map<int, SUMOTime> targetPhasesCTS;

    //The map to store the time each target phase have been checked last
    //This helps to compute the timesteps to get the cars*timesteps value
    std::map<int, SUMOTime> lastCheckForTargetPhase;

    //Map to store how many selection rounds have been done from the last selection of the phase
    std::map<int, int> targetPhasesLastSelection;

    int getTargetPhaseMaxLastSelection() {
        //return 2 * targetPhasesCTS.size() - 1;
        return (int)targetPhasesCTS.size() - 1;
    }

    /*
     * This member keeps track which is the current steps chain, i.e.
     * which is the last target phase executed (even if it is currently executed)
     * (a steps chain starts always with a target phase)
     */
    int lastChain;

    SUMOReal decayThreshold;
    /*
     * @brief Check for phases compliancy
     */
    void checkPhases();

    /*
     * Find the first target phase and set the current step on it
     */
    void setToATargetPhase();

    /*
     * This function member helps to set up the map keeping track of target phases and associated timesteps
     */
    void setupCTS();

    /*
     * Updates the cars-timesteps counters for each target phase except the one belonging to the current steps chain
     */
    void updateCTS();

    /*
     * To reset the cars-timesteps counter when a target phase is newly selected
     * If phaseStep is not a target phase nothing happens
     */
    void resetCTS(int phaseStep);
    /*
     * TEST
     */
    void updateDecayThreshold();

    /*
     * Traffic threshold calculation mode:
     * 0-> cars times seconds
     * 1-> estimated cars times seconds
     * 2-> queue length
     */
    unsigned int getMode() {
        return TplConvert::_2int(getParameter("MODE", "0").c_str());
    }
    /*
     * Decay threshold that should be used in case of penetration rate != 100%
     * 0-> not active
     * 1-> active
     */
    bool isDecayThresholdActivated() {
        return TplConvert::_2bool(getParameter("DECAY_THRESHOLD", "0").c_str());
    }

    SUMOReal getDecayConstant() {
        return TplConvert::_2SUMOReal(getParameter("DECAY_CONSTANT", "-0.001").c_str());
    }

};

#endif
/****************************************************************************/
