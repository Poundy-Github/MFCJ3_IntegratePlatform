# \file
#
# \brief AUTOSAR Make
#
# This file contains the implementation of the AUTOSAR
# module Make.
#
# \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
#
# Copyright 2005 - 2019 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.
[!AUTOSPACING!]
#################################################################
# This makefile exports parameters derived from the
# project configuration into variables for make
[!MACRO "GetModuleName","PluginName"!]
  [!IF "contains($PluginName, '_TS_')"!]
[!"substring-before($PluginName, '_TS_')"!][!//
  [!ELSEIF "contains($PluginName, '_')"!]
[!"substring-before($PluginName, '_')"!][!//
  [!ELSE!]
[!"$PluginName"!][!//
  [!ENDIF!]
[!ENDMACRO!]
[!MACRO "GetModuleVariant","PluginName"!]
  [!IF "contains($PluginName, '_TS_')"!]
    [!IF "contains(substring-after($PluginName, '_TS_'), '_')"!]
[!"concat('TS_', substring-before(substring-after($PluginName, '_TS_'), '_'))"!][!//
    [!ELSE!]
[!"concat('TS_', substring-after($PluginName, '_TS_'))"!][!//
    [!ENDIF!]
  [!ELSEIF "contains($PluginName, '_')"!]
    [!IF "contains(substring-after($PluginName, '_'), '_')"!]
[!"substring-before(substring-after($PluginName, '_'), '_')"!][!//
    [!ELSE!]
[!"substring-after($PluginName, '_')"!][!//
    [!ENDIF!]
  [!ELSE!]
[!"''"!][!//
  [!ENDIF!]
[!ENDMACRO!]
[!MACRO "GetModuleVariantSuffix","PluginName"!]
  [!IF "contains($PluginName, '_TS_')"!]
[!"concat('TS_', substring-after($PluginName, '_TS_'))"!][!//
  [!ELSEIF "contains($PluginName, '_')"!]
[!"substring-after($PluginName, '_')"!][!//
  [!ELSE!]
[!"''"!][!//
  [!ENDIF!]
[!ENDMACRO!]

# Only include these variables once
ifndef PROJECT_MODULES

[!IF "$project != ''"!]
# project name in workspace
TRESOS2_PROJECT_NAME :=[!WS!][!"$project"!]
TRESOS2_ECU_ID       :=[!WS!][!"$ecuid"!]

# target and derivate
TARGET   :=[!WS!][!"$target"!]
DERIVATE :=[!WS!][!"$derivate"!]

ifeq (,$(ENABLED_PLUGINS))
# In case enabled modules are NOT specified explicitly
# use all enabled modules (including modules, that are NOT generated)
PROJECT_MODULES :=[!LOOP "text:order(text:split($enabledModules))"!][!WS!][!CALL "GetModuleName","PluginName"="."!][!ENDLOOP!]

else
# otherwise only use generated modules
PROJECT_MODULES :=[!LOOP "text:order(text:split($generateModules))"!][!WS!][!CALL "GetModuleName","PluginName"="."!][!ENDLOOP!]

endif

# add tresos2 make plugin if not yet contained in SOFTWARE_MODULES
SOFTWARE_MODULES := $(strip $(filter-out tresos2,$(SOFTWARE_MODULES)) tresos2)

# There might already modules added to SOFTWARE_MODULES. So add only what's
# not yet contained SOFTWARE_MODULES.
# Duplicated entries are removed by the sort function.
SOFTWARE_MODULES += $(sort $(filter-out $(SOFTWARE_MODULES),$(PROJECT_MODULES)))

# variables defining module versions and locations of the plugins
[!LOOP "text:order(text:split($enabledModules))"!]
  [!VAR "moduleName"!][!CALL "GetModuleName", "PluginName"="."!][!ENDVAR!]
  [!VAR "moduleVariant"!][!CALL "GetModuleVariantSuffix", "PluginName"="."!][!ENDVAR!]
  [!VAR "pluginPath" = "text:replaceAll(asc:getPluginLocationById(.), '\\', '/')"!]
  [!IF "$pluginPath = ''"!]
    [!VAR "pluginName"!][!"$moduleName"!]_[!CALL "GetModuleVariant", "PluginName"="."!][!ENDVAR!]
    [!VAR "pluginPath" = "text:replaceAll(asc:getPluginLocationById($pluginName), '\\', '/')"!]
  [!ENDIF!]
  [!IF "$moduleVariant != ''"!]
[!"$moduleName"!]_VARIANT   :=[!WS!][!"$moduleVariant"!]
  [!ENDIF!]
  [!IF "$pluginPath != ''"!]
[!"$moduleName"!]_CORE_PATH :=[!WS!][!"text:replace($pluginPath, text:replaceAll($tresosBase, '\\', '/'), '\$(TRESOS_BASE)')"!]
  [!ENDIF!]
[!ENDLOOP!]

[!/* list of all generation output paths as Make variable, also contains the default generation output path */!][!//
[!VAR "genPaths" = "' $(GEN_OUTPUT_PATH)'"!]
[!IF "boolean($generationPaths)"!]
# variables defining module generation output paths
  [!FOR "i" = "1" TO "count(text:split($generateConfigs))"!]
    [!VAR "genModule" = "text:split($generateConfigs)[position()=$i]"!]
    [!VAR "genPath" = "text:split($generationPaths)[position()=$i]"!]
    [!IF "$genPath != $generationDir"!]
[!"$genModule"!]_OUTPUT_PATH := [!"text:replace(text:replaceAll($genPath, '\\', '/'), text:replaceAll($projectDir, '\\', '/'), '\$(PROJECT_ROOT)')"!]
[!/* concat all specific generation output paths (with trailing backslash and newline) */!][!//
      [!VAR "genPaths"!][!"$genPaths"!][!"' \'"!][!CR!][!"' $('"!][!"$genModule"!][!"'_OUTPUT_PATH)'"!][!ENDVAR!]
    [!ENDIF!]
  [!ENDFOR!]
[!ENDIF!]

# default output path for generated files
GEN_OUTPUT_PATH  ?= [!"text:replace(text:replaceAll($generationDir, '\\', '/'), text:replaceAll($projectDir, '\\', '/'), '\$(PROJECT_ROOT)')"!]
# list of all output paths of generated files
GEN_OUTPUT_PATHS ?= \
[!"$genPaths"!]
[!ELSE!]
ECU_ID           := ECU
GEN_OUTPUT_PATH  ?= $(PROJECT_ROOT)/output/generated
GEN_OUTPUT_PATHS ?= $(GEN_OUTPUT_PATH)
[!ENDIF!]
override GEN_OUTPUT_PATH  := $(subst \,/,$(GEN_OUTPUT_PATH))
override GEN_OUTPUT_PATHS := $(subst \,/,$(GEN_OUTPUT_PATHS))

# output path for files created by the build environment
PROJECT_OUTPUT_PATH ?= $(abspath $(GEN_OUTPUT_PATH)/..)

# for compatibility reasons we need the AUTOSAR_BASE_OUTPUT_PATH
AUTOSAR_BASE_OUTPUT_PATH ?= $(GEN_OUTPUT_PATH)
override AUTOSAR_BASE_OUTPUT_PATH := $(subst \,/,$(AUTOSAR_BASE_OUTPUT_PATH))

endif

[!/* Get OS Vendor Id: */!][!//
[!/* If there is an Os configuration... */!][!//
[!IF "node:exists(as:modconf('Os'))"!]
[!/* ...and inside there's a vendor Id and the Vendor Id is set to one (EB) */!][!//
  [!IF "node:exists(as:modconf('Os')/CommonPublishedInformation/VendorId) and as:modconf('Os')/CommonPublishedInformation/VendorId = 1"!]
# Set Os Vendor to EB
OS_VENDOR := EB
  [!ELSE!]
# Set Os Vendor to other (not EB)
OS_VENDOR := OTHER
  [!ENDIF!]
[!ELSE!]
# No Os configuration found, declare Os Vendor empty
OS_VENDOR :=
[!ENDIF!]