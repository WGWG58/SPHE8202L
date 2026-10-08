echo off

if "%1" == "16" goto sdram16
if "%1" == "32" goto sdram32
if "%1" == "" goto bad_parameter
goto bad_parameter


REM===================================================================
:bad_parameter
echo **********************
echo bad parameter
echo for 16m, usage: sys 16
echo for 32m, usage: sys 32
echo **********************
cd system
goto end
REM===================================================================


REM =====================================
:sdram16
del system\*.a
del mipsel-elf\libsys_16.a
cd system
make
copy libsys.a ..\mipsel-elf\libsys_16.a
if not exist libsys.a goto failed
goto end
REM =====================================


REM =====================================
:sdram32
del system\*.a
del mipsel-elf\libsys_8202.a
cd system
make
copy libsys.a ..\mipsel-elf\libsys_8202.a
if not exist libsys.a goto failed
goto end
REM =====================================


REM ======================================
:failed
echo *************************
echo failed on generating libsys.a
REM ======================================


:end
cd..
