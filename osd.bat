
echo off

if "%1" == "16" goto sdram16
if "%1" == "32" goto sdram32
if "%1" == "" goto bad_parameter
goto bad_parameter


REM===================================================================
:bad_parameter
echo **********************
echo bad parameter
echo for 16m, usage: osd 16
echo for 32m, usage: osd 32
echo **********************
cd osd
goto end
REM===================================================================


REM ======================================
:sdram16
del mipsel-elf\libosd_16.a
cd osd
make
copy libosd.a ..\mipsel-elf\libosd_16.a
if not exist libosd.a goto failed
goto end
REM ======================================


REM ======================================
:sdram32
del mipsel-elf\libosd_8202.a
cd osd
make
copy libosd.a ..\mipsel-elf\libosd_8202.a
if not exist libosd.a goto failed
goto end
REM =======================================


REM ======================================
:failed
echo *************************
echo failed on generating libosd.a
REM ======================================


:end
cd..
