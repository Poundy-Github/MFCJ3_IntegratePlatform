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
if exist .\config\Can_17_McmCan.xdm (
echo 	remove %~d0%~p0config\Can_17_McmCan.xdm
del .\config\Can_17_McmCan.xdm )
if exist .\generate\include\Can_17_McmCan_Cfg.h (
echo 	remove %~d0%~p0generate\include\Can_17_McmCan_Cfg.h
del .\generate\include\Can_17_McmCan_Cfg.h )
if exist .\generate_swcd\swcd\Can_17_McmCan_Bswmd.arxml (
echo 	remove %~d0%~p0generate_swcd\swcd\Can_17_McmCan_Bswmd.arxml
del .\generate_swcd\swcd\Can_17_McmCan_Bswmd.arxml )
if exist .\include\Can.h (
echo 	remove %~d0%~p0include\Can.h
del .\include\Can.h )
if exist .\include\Can_17_McmCan_Irq.h (
echo 	remove %~d0%~p0include\Can_17_McmCan_Irq.h
del .\include\Can_17_McmCan_Irq.h )
if exist .\plugin.xml (
echo 	remove %~d0%~p0plugin.xml
del .\plugin.xml )
if exist .\resources\Can_17_McmCan_Dem_Events.xml (
echo 	remove %~d0%~p0resources\Can_17_McmCan_Dem_Events.xml
del .\resources\Can_17_McmCan_Dem_Events.xml )
if exist .\resources\Can_17_McmCan_EcuM_InitFunctions.xml (
echo 	remove %~d0%~p0resources\Can_17_McmCan_EcuM_InitFunctions.xml
del .\resources\Can_17_McmCan_EcuM_InitFunctions.xml )
if exist .\resources\Can_17_McmCan_SchM_MainFunctions.xml (
echo 	remove %~d0%~p0resources\Can_17_McmCan_SchM_MainFunctions.xml
del .\resources\Can_17_McmCan_SchM_MainFunctions.xml )
if exist .\src\Can_17_McmCan_Irq.c (
echo 	remove %~d0%~p0src\Can_17_McmCan_Irq.c
del .\src\Can_17_McmCan_Irq.c )

:: perform origin
if [%1]==[EB_update] goto copy_EB
:: if exist an *.origin_version file make it to the current file:
if exist .\autosar\Can_17_McmCan_Bswmd.arxml.origin_version (
echo 	use %~d0%~p0autosar\Can_17_McmCan_Bswmd.arxml.origin_version 
copy .\autosar\Can_17_McmCan_Bswmd.arxml.origin_version .\autosar\Can_17_McmCan_Bswmd.arxml >NUL )
if exist .\config\Can_17_McmCan.xdm.origin_version (
echo 	use %~d0%~p0config\Can_17_McmCan.xdm.origin_version 
copy .\config\Can_17_McmCan.xdm.origin_version .\config\Can_17_McmCan.xdm >NUL )
if exist .\generate\include\Can_17_McmCan_Cfg.h.origin_version (
echo 	use %~d0%~p0generate\include\Can_17_McmCan_Cfg.h.origin_version 
copy .\generate\include\Can_17_McmCan_Cfg.h.origin_version .\generate\include\Can_17_McmCan_Cfg.h >NUL )
if exist .\plugin.xml.origin_version (
echo 	use %~d0%~p0plugin.xml.origin_version 
copy .\plugin.xml.origin_version .\plugin.xml >NUL )
if exist .\src\Can_17_McmCan_Irq.c.origin_version (
echo 	use %~d0%~p0src\Can_17_McmCan_Irq.c.origin_version 
copy .\src\Can_17_McmCan_Irq.c.origin_version .\src\Can_17_McmCan_Irq.c >NUL )
goto copy_end

:: perform EB update
:copy_EB
:: if exist an *.EB_update file make it to the current file:
if exist .\config\Can_17_McmCan.xdm.EB_update (
echo 	use %~d0%~p0config\Can_17_McmCan.xdm.EB_update
copy .\config\Can_17_McmCan.xdm.EB_update .\config\Can_17_McmCan.xdm >NUL )
if exist .\generate\include\Can_17_McmCan_Cfg.h.EB_update (
echo 	use %~d0%~p0generate\include\Can_17_McmCan_Cfg.h.EB_update
copy .\generate\include\Can_17_McmCan_Cfg.h.EB_update .\generate\include\Can_17_McmCan_Cfg.h >NUL )
if exist .\generate_swcd\swcd\Can_17_McmCan_Bswmd.arxml.EB_update (
echo 	use %~d0%~p0generate_swcd\swcd\Can_17_McmCan_Bswmd.arxml.EB_update
copy .\generate_swcd\swcd\Can_17_McmCan_Bswmd.arxml.EB_update .\generate_swcd\swcd\Can_17_McmCan_Bswmd.arxml >NUL )
if exist .\include\Can.h.EB_update (
echo 	use %~d0%~p0include\Can.h.EB_update
copy .\include\Can.h.EB_update .\include\Can.h >NUL )
if exist .\include\Can_17_McmCan_Irq.h.EB_update (
echo 	use %~d0%~p0include\Can_17_McmCan_Irq.h.EB_update
copy .\include\Can_17_McmCan_Irq.h.EB_update .\include\Can_17_McmCan_Irq.h >NUL )
if exist .\plugin.xml.EB_update (
echo 	use %~d0%~p0plugin.xml.EB_update
copy .\plugin.xml.EB_update .\plugin.xml >NUL )
if exist .\resources\Can_17_McmCan_Dem_Events.xml.EB_update (
echo 	use %~d0%~p0resources\Can_17_McmCan_Dem_Events.xml.EB_update
copy .\resources\Can_17_McmCan_Dem_Events.xml.EB_update .\resources\Can_17_McmCan_Dem_Events.xml >NUL )
if exist .\resources\Can_17_McmCan_EcuM_InitFunctions.xml.EB_update (
echo 	use %~d0%~p0resources\Can_17_McmCan_EcuM_InitFunctions.xml.EB_update
copy .\resources\Can_17_McmCan_EcuM_InitFunctions.xml.EB_update .\resources\Can_17_McmCan_EcuM_InitFunctions.xml >NUL )
if exist .\resources\Can_17_McmCan_SchM_MainFunctions.xml.EB_update (
echo 	use %~d0%~p0resources\Can_17_McmCan_SchM_MainFunctions.xml.EB_update
copy .\resources\Can_17_McmCan_SchM_MainFunctions.xml.EB_update .\resources\Can_17_McmCan_SchM_MainFunctions.xml >NUL )
if exist .\src\Can_17_McmCan_Irq.c.EB_update (
echo 	use %~d0%~p0src\Can_17_McmCan_Irq.c.EB_update
copy .\src\Can_17_McmCan_Irq.c.EB_update .\src\Can_17_McmCan_Irq.c >NUL )
:copy_end
