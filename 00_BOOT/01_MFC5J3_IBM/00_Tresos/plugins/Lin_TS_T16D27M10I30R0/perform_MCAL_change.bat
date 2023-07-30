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
if exist .\config\Lin_17_AscLin.xdm (
echo 	remove %~d0%~p0config\Lin_17_AscLin.xdm
del .\config\Lin_17_AscLin.xdm )
if exist .\generate_swcd\swcd\Lin_17_AscLin_Bswmd.arxml (
echo 	remove %~d0%~p0generate_swcd\swcd\Lin_17_AscLin_Bswmd.arxml
del .\generate_swcd\swcd\Lin_17_AscLin_Bswmd.arxml )
if exist .\include\Lin.h (
echo 	remove %~d0%~p0include\Lin.h
del .\include\Lin.h )
if exist .\include\Lin_17_AscLin_Irq.h (
echo 	remove %~d0%~p0include\Lin_17_AscLin_Irq.h
del .\include\Lin_17_AscLin_Irq.h )
if exist .\plugin.xml (
echo 	remove %~d0%~p0plugin.xml
del .\plugin.xml )
if exist .\resources\Lin_17_AscLin_Dem_Events.xml (
echo 	remove %~d0%~p0resources\Lin_17_AscLin_Dem_Events.xml
del .\resources\Lin_17_AscLin_Dem_Events.xml )
if exist .\resources\Lin_17_AscLin_EcuM_InitFunctions.xml (
echo 	remove %~d0%~p0resources\Lin_17_AscLin_EcuM_InitFunctions.xml
del .\resources\Lin_17_AscLin_EcuM_InitFunctions.xml )
if exist .\resources\Lin_17_AscLin_SchM_MainFunctions.xml (
echo 	remove %~d0%~p0resources\Lin_17_AscLin_SchM_MainFunctions.xml
del .\resources\Lin_17_AscLin_SchM_MainFunctions.xml )
if exist .\src\Lin_17_AscLin.c (
echo 	remove %~d0%~p0src\Lin_17_AscLin.c
del .\src\Lin_17_AscLin.c )
if exist .\src\Lin_17_AscLin_Irq.c (
echo 	remove %~d0%~p0src\Lin_17_AscLin_Irq.c
del .\src\Lin_17_AscLin_Irq.c )

:: perform origin
if [%1]==[EB_update] goto copy_EB
:: if exist an *.origin_version file make it to the current file:
if exist .\autosar\Lin_17_AscLin_Bswmd.arxml.origin_version (
echo 	use %~d0%~p0autosar\Lin_17_AscLin_Bswmd.arxml.origin_version 
copy .\autosar\Lin_17_AscLin_Bswmd.arxml.origin_version .\autosar\Lin_17_AscLin_Bswmd.arxml >NUL )
if exist .\config\Lin_17_AscLin.xdm.origin_version (
echo 	use %~d0%~p0config\Lin_17_AscLin.xdm.origin_version 
copy .\config\Lin_17_AscLin.xdm.origin_version .\config\Lin_17_AscLin.xdm >NUL )
if exist .\plugin.xml.origin_version (
echo 	use %~d0%~p0plugin.xml.origin_version 
copy .\plugin.xml.origin_version .\plugin.xml >NUL )
if exist .\src\Lin_17_AscLin.c.origin_version (
echo 	use %~d0%~p0src\Lin_17_AscLin.c.origin_version 
copy .\src\Lin_17_AscLin.c.origin_version .\src\Lin_17_AscLin.c >NUL )
if exist .\src\Lin_17_AscLin_Irq.c.origin_version (
echo 	use %~d0%~p0src\Lin_17_AscLin_Irq.c.origin_version 
copy .\src\Lin_17_AscLin_Irq.c.origin_version .\src\Lin_17_AscLin_Irq.c >NUL )
goto copy_end

:: perform EB update
:copy_EB
:: if exist an *.EB_update file make it to the current file:
if exist .\config\Lin_17_AscLin.xdm.EB_update (
echo 	use %~d0%~p0config\Lin_17_AscLin.xdm.EB_update
copy .\config\Lin_17_AscLin.xdm.EB_update .\config\Lin_17_AscLin.xdm >NUL )
if exist .\generate_swcd\swcd\Lin_17_AscLin_Bswmd.arxml.EB_update (
echo 	use %~d0%~p0generate_swcd\swcd\Lin_17_AscLin_Bswmd.arxml.EB_update
copy .\generate_swcd\swcd\Lin_17_AscLin_Bswmd.arxml.EB_update .\generate_swcd\swcd\Lin_17_AscLin_Bswmd.arxml >NUL )
if exist .\include\Lin.h.EB_update (
echo 	use %~d0%~p0include\Lin.h.EB_update
copy .\include\Lin.h.EB_update .\include\Lin.h >NUL )
if exist .\include\Lin_17_AscLin_Irq.h.EB_update (
echo 	use %~d0%~p0include\Lin_17_AscLin_Irq.h.EB_update
copy .\include\Lin_17_AscLin_Irq.h.EB_update .\include\Lin_17_AscLin_Irq.h >NUL )
if exist .\plugin.xml.EB_update (
echo 	use %~d0%~p0plugin.xml.EB_update
copy .\plugin.xml.EB_update .\plugin.xml >NUL )
if exist .\resources\Lin_17_AscLin_Dem_Events.xml.EB_update (
echo 	use %~d0%~p0resources\Lin_17_AscLin_Dem_Events.xml.EB_update
copy .\resources\Lin_17_AscLin_Dem_Events.xml.EB_update .\resources\Lin_17_AscLin_Dem_Events.xml >NUL )
if exist .\resources\Lin_17_AscLin_EcuM_InitFunctions.xml.EB_update (
echo 	use %~d0%~p0resources\Lin_17_AscLin_EcuM_InitFunctions.xml.EB_update
copy .\resources\Lin_17_AscLin_EcuM_InitFunctions.xml.EB_update .\resources\Lin_17_AscLin_EcuM_InitFunctions.xml >NUL )
if exist .\resources\Lin_17_AscLin_SchM_MainFunctions.xml.EB_update (
echo 	use %~d0%~p0resources\Lin_17_AscLin_SchM_MainFunctions.xml.EB_update
copy .\resources\Lin_17_AscLin_SchM_MainFunctions.xml.EB_update .\resources\Lin_17_AscLin_SchM_MainFunctions.xml >NUL )
if exist .\src\Lin_17_AscLin.c.EB_update (
echo 	use %~d0%~p0src\Lin_17_AscLin.c.EB_update
copy .\src\Lin_17_AscLin.c.EB_update .\src\Lin_17_AscLin.c >NUL )
if exist .\src\Lin_17_AscLin_Irq.c.EB_update (
echo 	use %~d0%~p0src\Lin_17_AscLin_Irq.c.EB_update
copy .\src\Lin_17_AscLin_Irq.c.EB_update .\src\Lin_17_AscLin_Irq.c >NUL )
:copy_end
