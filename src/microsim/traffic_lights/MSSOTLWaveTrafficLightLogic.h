/****************************************************************************/
/// @file    MSSOTLWaveTrafficLightLogic.h
/// @author  Riccardo Belletti
/// @author  Anna Chiara Bellini
/// @date    Sep 2013
/// @version $Id: MSSOTLWaveTrafficLightLogic.h 19623 2015-12-16 09:30:37Z behrisch $
///
// The class for SOTL Platoon logics
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
#ifndef MSSOTLWaveTrafficLightLogic_h
#define MSSOTLWaveTrafficLightLogic_h

// ===========================================================================
// included modules
// ===========================================================================
#ifdef _MSC_VER
#include <windows_config.h>
#else
#include <config.h>
#endif

#include "MSSOTLTrafficLightLogic.h"
class MSSOTLWaveTrafficLightLogic: public MSSOTLTrafficLightLogic {
public:
    /**
     * @brief Constructor without sensors passed
     * @param[in] tlcontrol The tls control responsible for this tls
     * @param[in] id This tls' id
     * @param[in] subid This tls' sub-id (program id)
     * @param[in] phases Definitions of the phases
     * @param[in] step The initial phase index
     * @param[in] delay The time to wait before the first switch
     */
    MSSOTLWaveTrafficLightLogic(MSTLLogicControl& tlcontrol,
                                const std::string& id, const std::string& subid,
                                const Phases& phases, unsigned int step, SUMOTime delay,
                                const std::map<std::string, std::string>& parameters) throw();

    /**
     * @brief Constructor with sensors passed
     * @param[in] tlcontrol The tls control responsible for this tls
     * @param[in] id This tls' id
     * @param[in] subid This tls' sub-id (program id)
     * @param[in] phases Definitions of the phases
     * @param[in] step The initial phase index
     * @param[in] delay The time to wait before the first switch
     */
    MSSOTLWaveTrafficLightLogic(MSTLLogicControl& tlcontrol,
                                const std::string& id, const std::string& subid,
                                const Phases& phases, unsigned int step, SUMOTime delay,
                                const std::map<std::string, std::string>& parameters,
                                MSSOTLSensors* sensors) throw();

    /** @brief Returns the type of the logic as a string
     * @return The type of the logic
     */
    const std::string getLogicType() const {
        return "waveTrafficLightLogic";
    }
    /// @}

protected:

    /*
     * @brief Contains the logic to decide whether to release the green light
     */
    bool canRelease() throw();

private:

    /*
     * @brief Counts the vehicles on the green lanes of this phase
     */
    int countVehicles();

};

#endif
/****************************************************************************/
