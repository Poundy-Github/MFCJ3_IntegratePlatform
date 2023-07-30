@ECHO OFF

:: SWC Maker
@REM goto Pre_Build_Process
@REM :Pre_Build_End


:: set PROJECT_ROOT to the current project directory (relative to location of this batch file, converted to absolute path)
for /f %%i in ("%~dp0..") do set PROJECT_ROOT=%%~fi

:: Call the optional launch_cfg.bat
:: This file contains TARGET, DERIVATE, TRESOS_BASE, and TOOLPATH_COMPILER.
:: These variables can also be provided as environment variables.
IF "%TARGET%"=="" SET TARGET=TRICORE
IF "%DERIVATE%"=="" SET DERIVATE=TC38XQ
IF "%TOOLCHAIN%"=="" SET TOOLCHAIN=tasking

call launch_cfg.bat

:: add %TRESOS_BASE%\bin to path
set PATH=%PATH%;%TRESOS_BASE%\bin;

:: set path of make executable
SET MAKE_EXE=%PLUGINS_BASE%\Make_TS_TxDxM4I0R0\tools\GNU_Make\make.exe

SET MAKE_OPTIONS=
:: a user makefile is specified
IF "%1"=="-f" GOTO call_make
:: no user makefile is specified, use default file
SET MAKE_OPTIONS=-f Makefile.mak
GOTO call_make


:call_make

:: make clean
%MAKE_EXE% SHELL=cmd.exe %MAKE_OPTIONS% "clean"

:: make -j16
%MAKE_EXE% SHELL=cmd.exe %MAKE_OPTIONS% "-j10"