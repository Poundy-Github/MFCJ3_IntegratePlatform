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
if exist .\config\Resource.xdm (
echo 	remove %~d0%~p0config\Resource.xdm
del .\config\Resource.xdm )
if exist .\generate_swcd\swcd\Resource.arxml (
echo 	remove %~d0%~p0generate_swcd\swcd\Resource.arxml
del .\generate_swcd\swcd\Resource.arxml )
if exist .\include\Compiler_CfgExtMcal.h (
echo 	remove %~d0%~p0include\Compiler_CfgExtMcal.h
del .\include\Compiler_CfgExtMcal.h )
if exist .\include\IFX_Os.h (
echo 	remove %~d0%~p0include\IFX_Os.h
del .\include\IFX_Os.h )
if exist .\include\Irq.h (
echo 	remove %~d0%~p0include\Irq.h
del .\include\Irq.h )
if exist .\include\Mcal_SafetyError.h (
echo 	remove %~d0%~p0include\Mcal_SafetyError.h
del .\include\Mcal_SafetyError.h )
if exist .\plugin.xml (
echo 	remove %~d0%~p0plugin.xml
del .\plugin.xml )
if exist .\resource\cangeneraltypesmapping.properties (
echo 	remove %~d0%~p0resource\cangeneraltypesmapping.properties
del .\resource\cangeneraltypesmapping.properties )
if exist .\resource\canwizard.properties (
echo 	remove %~d0%~p0resource\canwizard.properties
del .\resource\canwizard.properties )
if exist .\src\Mcal_SafetyError.c (
echo 	remove %~d0%~p0src\Mcal_SafetyError.c
del .\src\Mcal_SafetyError.c )

:: perform origin
if [%1]==[EB_update] goto copy_EB
:: if exist an *.origin_version file make it to the current file:
if exist .\include\IFX_Os.h.origin_version (
echo 	use %~d0%~p0include\IFX_Os.h.origin_version 
copy .\include\IFX_Os.h.origin_version .\include\IFX_Os.h >NUL )
if exist .\include\Irq.h.origin_version (
echo 	use %~d0%~p0include\Irq.h.origin_version 
copy .\include\Irq.h.origin_version .\include\Irq.h >NUL )
if exist .\include\Mcal_SafetyError.h.origin_version (
echo 	use %~d0%~p0include\Mcal_SafetyError.h.origin_version 
copy .\include\Mcal_SafetyError.h.origin_version .\include\Mcal_SafetyError.h >NUL )
if exist .\plugin.xml.origin_version (
echo 	use %~d0%~p0plugin.xml.origin_version 
copy .\plugin.xml.origin_version .\plugin.xml >NUL )
if exist .\src\Mcal_SafetyError.c.origin_version (
echo 	use %~d0%~p0src\Mcal_SafetyError.c.origin_version 
copy .\src\Mcal_SafetyError.c.origin_version .\src\Mcal_SafetyError.c >NUL )
goto copy_end

:: perform EB update
:copy_EB
:: if exist an *.EB_update file make it to the current file:
if exist .\config\Resource.xdm.EB_update (
echo 	use %~d0%~p0config\Resource.xdm.EB_update
copy .\config\Resource.xdm.EB_update .\config\Resource.xdm >NUL )
if exist .\generate_swcd\swcd\Resource.arxml.EB_update (
echo 	use %~d0%~p0generate_swcd\swcd\Resource.arxml.EB_update
copy .\generate_swcd\swcd\Resource.arxml.EB_update .\generate_swcd\swcd\Resource.arxml >NUL )
if exist .\include\Compiler_CfgExtMcal.h.EB_update (
echo 	use %~d0%~p0include\Compiler_CfgExtMcal.h.EB_update
copy .\include\Compiler_CfgExtMcal.h.EB_update .\include\Compiler_CfgExtMcal.h >NUL )
if exist .\include\IFX_Os.h.EB_update (
echo 	use %~d0%~p0include\IFX_Os.h.EB_update
copy .\include\IFX_Os.h.EB_update .\include\IFX_Os.h >NUL )
if exist .\include\Irq.h.EB_update (
echo 	use %~d0%~p0include\Irq.h.EB_update
copy .\include\Irq.h.EB_update .\include\Irq.h >NUL )
if exist .\include\Mcal_SafetyError.h.EB_update (
echo 	use %~d0%~p0include\Mcal_SafetyError.h.EB_update
copy .\include\Mcal_SafetyError.h.EB_update .\include\Mcal_SafetyError.h >NUL )
if exist .\plugin.xml.EB_update (
echo 	use %~d0%~p0plugin.xml.EB_update
copy .\plugin.xml.EB_update .\plugin.xml >NUL )
if exist .\resource\cangeneraltypesmapping.properties.EB_update (
echo 	use %~d0%~p0resource\cangeneraltypesmapping.properties.EB_update
copy .\resource\cangeneraltypesmapping.properties.EB_update .\resource\cangeneraltypesmapping.properties >NUL )
if exist .\resource\canwizard.properties.EB_update (
echo 	use %~d0%~p0resource\canwizard.properties.EB_update
copy .\resource\canwizard.properties.EB_update .\resource\canwizard.properties >NUL )
if exist .\src\Mcal_SafetyError.c.EB_update (
echo 	use %~d0%~p0src\Mcal_SafetyError.c.EB_update
copy .\src\Mcal_SafetyError.c.EB_update .\src\Mcal_SafetyError.c >NUL )
:copy_end
