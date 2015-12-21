#!/usr/bin/env python
"""
@file    pythonPropsMSVC.py
@author  Michael Behrisch
@author  Daniel Krajzewicz
@author  Jakob Erdmann
@date    2011
@version $Id: pythonPropsMSVC.py 19649 2015-12-17 21:05:20Z behrisch $

This script rebuilds "../../build/msvc/python.props", the file which
gives information about the python includes and library.

SUMO, Simulation of Urban MObility; see http://sumo.dlr.de/
Copyright (C) 2011-2015 DLR (http://www.dlr.de/) and contributors

This file is part of SUMO.
SUMO is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.
"""
from __future__ import absolute_import
from __future__ import print_function

import sys
import distutils.sysconfig
from os.path import dirname, join

propsFile = join(
    dirname(__file__), '..', '..', 'build', 'msvc10', 'python.props')
print('generating %s ' % propsFile)
props = open(propsFile, 'w')
libPrefix = "%s\libs\python%s%s" % (sys.prefix, sys.version[0], sys.version[2])
print("""<?xml version="1.0" encoding="utf-8"?>
<Project DefaultTargets="Build" ToolsVersion="4.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
  <PropertyGroup Label="UserMacros">
    <PYTHON_LIB>%s.lib</PYTHON_LIB>
    <PYTHON_DEBUG_LIB>%s_d.lib</PYTHON_DEBUG_LIB>
  </PropertyGroup>
  <ItemDefinitionGroup>
    <ClCompile>
      <AdditionalIncludeDirectories>%s;%%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>
      <PreprocessorDefinitions>HAVE_PYTHON;%%(PreprocessorDefinitions)</PreprocessorDefinitions>
    </ClCompile>
  </ItemDefinitionGroup>
</Project>""" % (libPrefix, libPrefix, distutils.sysconfig.get_config_var('INCLUDEPY')), file=props)
props.close()
