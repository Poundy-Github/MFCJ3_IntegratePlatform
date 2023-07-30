@echo off
:: \file
::
:: \brief AUTOSAR Resource
::
:: This file contains the implementation of the AUTOSAR
:: module Resource.
::
:: \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
::
:: Copyright 2005 - 2019 Elektrobit Automotive GmbH
:: All rights exclusively reserved for Elektrobit Automotive GmbH,
:: unless expressly agreed to otherwise.::
:: script to update MCAL module with EB content
:: or reset it to vendor content

if [%1]==[EB_update] goto usage
if [%1]==[origin] goto usage
echo Usage: %0 [OPTION]
echo(
echo   EB_update
echo		Update files of the plug-in with content of Elektrobit Automotive GmbH.
echo   origin
echo		Reset the files of the plug-in with vendor content.
echo(
goto copy_end

:usage
cd %~d0 >NUL
cd %~p0
:: if exist an *.origin_version delete the current file:
:: if exist an *.EB_update file delete the current file:
if exist .\config\Port.xdm (
echo 	remove %~d0%~p0config\Port.xdm
del .\config\Port.xdm )
if exist .\generate_swcd\swcd\Port_Bswmd.arxml (
echo 	remove %~d0%~p0generate_swcd\swcd\Port_Bswmd.arxml
del .\generate_swcd\swcd\Port_Bswmd.arxml )
if exist .\plugin.xml (
echo 	remove %~d0%~p0plugin.xml
del .\plugin.xml )
if exist .\resources\Port_Dem_Events.xml (
echo 	remove %~d0%~p0resources\Port_Dem_Events.xml
del .\resources\Port_Dem_Events.xml )
if exist .\resources\Port_EcuM_InitFunctions.xml (
echo 	remove %~d0%~p0resources\Port_EcuM_InitFunctions.xml
del .\resources\Port_EcuM_InitFunctions.xml )
if exist .\resources\Port_SchM_MainFunctions.xml (
echo 	remove %~d0%~p0resources\Port_SchM_MainFunctions.xml
del .\resources\Port_SchM_MainFunctions.xml )

:: perform origin
if [%1]==[EB_update] goto copy_EB
:: if exist an *.origin_version file make it to the current file:
if exist .\autosar\Port_Bswmd.arxml.origin_version (
echo 	use %~d0%~p0autosar\Port_Bswmd.arxml.origin_version 
copy .\autosar\Port_Bswmd.arxml.origin_version .\autosar\Port_Bswmd.arxml >NUL )
if exist .\config\Port.xdm.origin_version (
echo 	use %~d0%~p0config\Port.xdm.origin_version 
copy .\config\Port.xdm.origin_version .\config\Port.xdm >NUL )
if exist .\plugin.xml.origin_version (
echo 	use %~d0%~p0plugin.xml.origin_version 
copy .\plugin.xml.origin_version .\plugin.xml >NUL )
goto copy_end

:: perform EB update
:copy_EB
:: if exist an *.EB_update file make it to the current file:
if exist .\config\Port.xdm.EB_update (
echo 	use %~d0%~p0config\Port.xdm.EB_update
copy .\config\Port.xdm.EB_update .\config\Port.xdm >NUL )
if exist .\generate_swcd\swcd\Port_Bswmd.arxml.EB_update (
echo 	use %~d0%~p0generate_swcd\swcd\Port_Bswmd.arxml.EB_update
copy .\generate_swcd\swcd\Port_Bswmd.arxml.EB_update .\generate_swcd\swcd\Port_Bswmd.arxml >NUL )
if exist .\plugin.xml.EB_update (
echo 	use %~d0%~p0plugin.xml.EB_update
copy .\plugin.xml.EB_update .\plugin.xml >NUL )
if exist .\resources\Port_Dem_Events.xml.EB_update (
echo 	use %~d0%~p0resources\Port_Dem_Events.xml.EB_update
copy .\resources\Port_Dem_Events.xml.EB_update .\resources\Port_Dem_Events.xml >NUL )
if exist .\resources\Port_EcuM_InitFunctions.xml.EB_update (
echo 	use %~d0%~p0resources\Port_EcuM_InitFunctions.xml.EB_update
copy .\resources\Port_EcuM_InitFunctions.xml.EB_update .\resources\Port_EcuM_InitFunctions.xml >NUL )
if exist .\resources\Port_SchM_MainFunctions.xml.EB_update (
echo 	use %~d0%~p0resources\Port_SchM_MainFunctions.xml.EB_update
copy .\resources\Port_SchM_MainFunctions.xml.EB_update .\resources\Port_SchM_MainFunctions.xml >NUL )
:copy_end
