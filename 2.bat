@ECHO OFF

if "%1" == "16"	goto start
if "%1" == "32" goto start
if "%1" == "" goto bad_parameter
goto bad_parameter


REM===================================================================
:bad_parameter
echo **********************
echo bad parameter
echo for 16m, usage: all 16
echo for 32m, usage: all 32
echo **********************
goto end
REM===================================================================


:start
font_parse.exe
del mips\crt0.o
del mips\init0.o
del mips\intdrv.o


if "%1" == "16"	goto sdram16
if "%1" == "32" goto sdram32


REM===================================================================
:sdram16
if exist system\makefile call sys.bat %1
if not exist mipsel-elf\libsys_16.a goto failed

call 1.bat %1 %2
rem call 1.bat %1
if not exist mipsel-elf\libir_8202.a goto failed

goto end
REM===================================================================


REM===================================================================
:sdram32
if exist system\makefile call sys.bat %1
if not exist mipsel-elf\libsys_8202.a goto failed

rem call 1.bat %1 %2
call 1.bat %1
if not exist mipsel-elf\libir_8202.a goto failed

goto end
REM===================================================================


REM ===================================================================
:failed
echo compile failed
echo *************************
REM ===================================================================


:end