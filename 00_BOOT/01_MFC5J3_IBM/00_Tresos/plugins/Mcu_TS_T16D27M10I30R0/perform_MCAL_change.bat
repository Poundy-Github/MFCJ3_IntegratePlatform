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
if exist .\config\Mcu.xdm (
echo 	remove %~d0%~p0config\Mcu.xdm
del .\config\Mcu.xdm )
if exist .\config_ext\McuPreConfiguration.xdm (
echo 	remove %~d0%~p0config_ext\McuPreConfiguration.xdm
del .\config_ext\McuPreConfiguration.xdm )
if exist .\config_ext\McuRecConfigurationStandard.xdm (
echo 	remove %~d0%~p0config_ext\McuRecConfigurationStandard.xdm
del .\config_ext\McuRecConfigurationStandard.xdm )
if exist .\generate_swcd\swcd\Mcu_Bswmd.arxml (
echo 	remove %~d0%~p0generate_swcd\swcd\Mcu_Bswmd.arxml
del .\generate_swcd\swcd\Mcu_Bswmd.arxml )
if exist .\include\Gtm_Irq.h (
echo 	remove %~d0%~p0include\Gtm_Irq.h
del .\include\Gtm_Irq.h )
if exist .\plugin.xml (
echo 	remove %~d0%~p0plugin.xml
del .\plugin.xml )
if exist .\resources\Mcu_Dem_Events.xml (
echo 	remove %~d0%~p0resources\Mcu_Dem_Events.xml
del .\resources\Mcu_Dem_Events.xml )
if exist .\resources\Mcu_EcuM_InitFunctions.xml (
echo 	remove %~d0%~p0resources\Mcu_EcuM_InitFunctions.xml
del .\resources\Mcu_EcuM_InitFunctions.xml )
if exist .\resources\Mcu_SchM_MainFunctions.xml (
echo 	remove %~d0%~p0resources\Mcu_SchM_MainFunctions.xml
del .\resources\Mcu_SchM_MainFunctions.xml )
if exist .\src\Gtm_Irq.c (
echo 	remove %~d0%~p0src\Gtm_Irq.c
del .\src\Gtm_Irq.c )

:: perform origin
if [%1]==[EB_update] goto copy_EB
:: if exist an *.origin_version file make it to the current file:
if exist .\autosar\Mcu_Bswmd.arxml.origin_version (
echo 	use %~d0%~p0autosar\Mcu_Bswmd.arxml.origin_version 
copy .\autosar\Mcu_Bswmd.arxml.origin_version .\autosar\Mcu_Bswmd.arxml >NUL )
if exist .\config\Mcu.xdm.origin_version (
echo 	use %~d0%~p0config\Mcu.xdm.origin_version 
copy .\config\Mcu.xdm.origin_version .\config\Mcu.xdm >NUL )
if exist .\config_ext\McuPreConfiguration.xdm.origin_version (
echo 	use %~d0%~p0config_ext\McuPreConfiguration.xdm.origin_version 
copy .\config_ext\McuPreConfiguration.xdm.origin_version .\config_ext\McuPreConfiguration.xdm >NUL )
if exist .\plugin.xml.origin_version (
echo 	use %~d0%~p0plugin.xml.origin_version 
copy .\plugin.xml.origin_version .\plugin.xml >NUL )
if exist .\src\Gtm_Irq.c.origin_version (
echo 	use %~d0%~p0src\Gtm_Irq.c.origin_version 
copy .\src\Gtm_Irq.c.origin_version .\src\Gtm_Irq.c >NUL )
goto copy_end

:: perform EB update
:copy_EB
:: if exist an *.EB_update file make it to the current file:
if exist .\config\Mcu.xdm.EB_update (
echo 	use %~d0%~p0config\Mcu.xdm.EB_update
copy .\config\Mcu.xdm.EB_update .\config\Mcu.xdm >NUL )
if exist .\config_ext\McuPreConfiguration.xdm.EB_update (
echo 	use %~d0%~p0config_ext\McuPreConfiguration.xdm.EB_update
copy .\config_ext\McuPreConfiguration.xdm.EB_update .\config_ext\McuPreConfiguration.xdm >NUL )
if exist .\config_ext\McuRecConfigurationStandard.xdm.EB_update (
echo 	use %~d0%~p0config_ext\McuRecConfigurationStandard.xdm.EB_update
copy .\config_ext\McuRecConfigurationStandard.xdm.EB_update .\config_ext\McuRecConfigurationStandard.xdm >NUL )
if exist .\generate_swcd\swcd\Mcu_Bswmd.arxml.EB_update (
echo 	use %~d0%~p0generate_swcd\swcd\Mcu_Bswmd.arxml.EB_update
copy .\generate_swcd\swcd\Mcu_Bswmd.arxml.EB_update .\generate_swcd\swcd\Mcu_Bswmd.arxml >NUL )
if exist .\include\Gtm_Irq.h.EB_update (
echo 	use %~d0%~p0include\Gtm_Irq.h.EB_update
copy .\include\Gtm_Irq.h.EB_update .\include\Gtm_Irq.h >NUL )
if exist .\plugin.xml.EB_update (
echo 	use %~d0%~p0plugin.xml.EB_update
copy .\plugin.xml.EB_update .\plugin.xml >NUL )
if exist .\resources\Mcu_Dem_Events.xml.EB_update (
echo 	use %~d0%~p0resources\Mcu_Dem_Events.xml.EB_update
copy .\resources\Mcu_Dem_Events.xml.EB_update .\resources\Mcu_Dem_Events.xml >NUL )
if exist .\resources\Mcu_EcuM_InitFunctions.xml.EB_update (
echo 	use %~d0%~p0resources\Mcu_EcuM_InitFunctions.xml.EB_update
copy .\resources\Mcu_EcuM_InitFunctions.xml.EB_update .\resources\Mcu_EcuM_InitFunctions.xml >NUL )
if exist .\resources\Mcu_SchM_MainFunctions.xml.EB_update (
echo 	use %~d0%~p0resources\Mcu_SchM_MainFunctions.xml.EB_update
copy .\resources\Mcu_SchM_MainFunctions.xml.EB_update .\resources\Mcu_SchM_MainFunctions.xml >NUL )
if exist .\src\Gtm_Irq.c.EB_update (
echo 	use %~d0%~p0src\Gtm_Irq.c.EB_update
copy .\src\Gtm_Irq.c.EB_update .\src\Gtm_Irq.c >NUL )
:copy_end
