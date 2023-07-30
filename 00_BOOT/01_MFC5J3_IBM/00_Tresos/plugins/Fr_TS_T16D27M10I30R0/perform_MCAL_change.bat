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
if exist .\config\Fr_17_Eray.xdm (
echo 	remove %~d0%~p0config\Fr_17_Eray.xdm
del .\config\Fr_17_Eray.xdm )
if exist .\generate\include\Fr_17_Eray_Cfg.h (
echo 	remove %~d0%~p0generate\include\Fr_17_Eray_Cfg.h
del .\generate\include\Fr_17_Eray_Cfg.h )
if exist .\generate\src\Fr_17_Eray_PBcfg.c (
echo 	remove %~d0%~p0generate\src\Fr_17_Eray_PBcfg.c
del .\generate\src\Fr_17_Eray_PBcfg.c )
if exist .\generate_swcd\swcd\Fr_17_Eray_Bswmd.arxml (
echo 	remove %~d0%~p0generate_swcd\swcd\Fr_17_Eray_Bswmd.arxml
del .\generate_swcd\swcd\Fr_17_Eray_Bswmd.arxml )
if exist .\include\Fr.h (
echo 	remove %~d0%~p0include\Fr.h
del .\include\Fr.h )
if exist .\plugin.xml (
echo 	remove %~d0%~p0plugin.xml
del .\plugin.xml )
if exist .\resources\Fr_17_Eray_Dem_Events.xml (
echo 	remove %~d0%~p0resources\Fr_17_Eray_Dem_Events.xml
del .\resources\Fr_17_Eray_Dem_Events.xml )
if exist .\resources\Fr_17_Eray_EcuM_InitFunctions.xml (
echo 	remove %~d0%~p0resources\Fr_17_Eray_EcuM_InitFunctions.xml
del .\resources\Fr_17_Eray_EcuM_InitFunctions.xml )
if exist .\resources\Fr_17_Eray_SchM_MainFunctions.xml (
echo 	remove %~d0%~p0resources\Fr_17_Eray_SchM_MainFunctions.xml
del .\resources\Fr_17_Eray_SchM_MainFunctions.xml )

:: perform origin
if [%1]==[EB_update] goto copy_EB
:: if exist an *.origin_version file make it to the current file:
if exist .\autosar\Fr_17_Eray_Bswmd.arxml.origin_version (
echo 	use %~d0%~p0autosar\Fr_17_Eray_Bswmd.arxml.origin_version 
copy .\autosar\Fr_17_Eray_Bswmd.arxml.origin_version .\autosar\Fr_17_Eray_Bswmd.arxml >NUL )
if exist .\config\Fr_17_Eray.xdm.origin_version (
echo 	use %~d0%~p0config\Fr_17_Eray.xdm.origin_version 
copy .\config\Fr_17_Eray.xdm.origin_version .\config\Fr_17_Eray.xdm >NUL )
if exist .\generate\include\Fr_17_Eray_Cfg.h.origin_version (
echo 	use %~d0%~p0generate\include\Fr_17_Eray_Cfg.h.origin_version 
copy .\generate\include\Fr_17_Eray_Cfg.h.origin_version .\generate\include\Fr_17_Eray_Cfg.h >NUL )
if exist .\generate\src\Fr_17_Eray_PBcfg.c.origin_version (
echo 	use %~d0%~p0generate\src\Fr_17_Eray_PBcfg.c.origin_version 
copy .\generate\src\Fr_17_Eray_PBcfg.c.origin_version .\generate\src\Fr_17_Eray_PBcfg.c >NUL )
if exist .\plugin.xml.origin_version (
echo 	use %~d0%~p0plugin.xml.origin_version 
copy .\plugin.xml.origin_version .\plugin.xml >NUL )
goto copy_end

:: perform EB update
:copy_EB
:: if exist an *.EB_update file make it to the current file:
if exist .\config\Fr_17_Eray.xdm.EB_update (
echo 	use %~d0%~p0config\Fr_17_Eray.xdm.EB_update
copy .\config\Fr_17_Eray.xdm.EB_update .\config\Fr_17_Eray.xdm >NUL )
if exist .\generate\include\Fr_17_Eray_Cfg.h.EB_update (
echo 	use %~d0%~p0generate\include\Fr_17_Eray_Cfg.h.EB_update
copy .\generate\include\Fr_17_Eray_Cfg.h.EB_update .\generate\include\Fr_17_Eray_Cfg.h >NUL )
if exist .\generate\src\Fr_17_Eray_PBcfg.c.EB_update (
echo 	use %~d0%~p0generate\src\Fr_17_Eray_PBcfg.c.EB_update
copy .\generate\src\Fr_17_Eray_PBcfg.c.EB_update .\generate\src\Fr_17_Eray_PBcfg.c >NUL )
if exist .\generate_swcd\swcd\Fr_17_Eray_Bswmd.arxml.EB_update (
echo 	use %~d0%~p0generate_swcd\swcd\Fr_17_Eray_Bswmd.arxml.EB_update
copy .\generate_swcd\swcd\Fr_17_Eray_Bswmd.arxml.EB_update .\generate_swcd\swcd\Fr_17_Eray_Bswmd.arxml >NUL )
if exist .\include\Fr.h.EB_update (
echo 	use %~d0%~p0include\Fr.h.EB_update
copy .\include\Fr.h.EB_update .\include\Fr.h >NUL )
if exist .\plugin.xml.EB_update (
echo 	use %~d0%~p0plugin.xml.EB_update
copy .\plugin.xml.EB_update .\plugin.xml >NUL )
if exist .\resources\Fr_17_Eray_Dem_Events.xml.EB_update (
echo 	use %~d0%~p0resources\Fr_17_Eray_Dem_Events.xml.EB_update
copy .\resources\Fr_17_Eray_Dem_Events.xml.EB_update .\resources\Fr_17_Eray_Dem_Events.xml >NUL )
if exist .\resources\Fr_17_Eray_EcuM_InitFunctions.xml.EB_update (
echo 	use %~d0%~p0resources\Fr_17_Eray_EcuM_InitFunctions.xml.EB_update
copy .\resources\Fr_17_Eray_EcuM_InitFunctions.xml.EB_update .\resources\Fr_17_Eray_EcuM_InitFunctions.xml >NUL )
if exist .\resources\Fr_17_Eray_SchM_MainFunctions.xml.EB_update (
echo 	use %~d0%~p0resources\Fr_17_Eray_SchM_MainFunctions.xml.EB_update
copy .\resources\Fr_17_Eray_SchM_MainFunctions.xml.EB_update .\resources\Fr_17_Eray_SchM_MainFunctions.xml >NUL )
:copy_end
