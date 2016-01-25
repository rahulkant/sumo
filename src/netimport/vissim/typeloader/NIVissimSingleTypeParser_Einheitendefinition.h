/****************************************************************************/
/// @file    NIVissimSingleTypeParser_Einheitendefinition.h
/// @author  Daniel Krajzewicz
/// @date    Wed, 30 Apr 2003
/// @version $Id: NIVissimSingleTypeParser_Einheitendefinition.h 18095 2015-03-17 09:39:00Z behrisch $
///
//
/****************************************************************************/
// SUMO, Simulation of Urban MObility; see http://sumo.dlr.de/
// Copyright (C) 2001-2015 DLR (http://www.dlr.de/) and contributors
/****************************************************************************/
//
//   This file is part of SUMO.
//   SUMO is free software: you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation, either version 3 of the License, or
//   (at your option) any later version.
//
/****************************************************************************/
#ifndef NIVissimSingleTypeParser_Einheitendefinition_h
#define NIVissimSingleTypeParser_Einheitendefinition_h


// ===========================================================================
// included modules
// ===========================================================================
#ifdef _MSC_VER
#include <windows_config.h>
#else
#include <config.h>
#endif

#include <iostream>
#include "../NIImporter_Vissim.h"


// ===========================================================================
// class definitions
// ===========================================================================
/**
 * @class NIVissimSingleTypeParser_Einheitendefinition
 *
 */
class NIVissimSingleTypeParser_Einheitendefinition :
    public NIImporter_Vissim::VissimSingleTypeParser {
public:
    /// Constructor
    NIVissimSingleTypeParser_Einheitendefinition(NIImporter_Vissim& parent);

    /// Destructor
    ~NIVissimSingleTypeParser_Einheitendefinition();

    /// Parses the data type from the given stream
    bool parse(std::istream& from);

};


#endif

/****************************************************************************/
