@ECHO OFF

if "%1" == "16"	goto start
if "%1" == "32" goto start
if "%1" == "" goto bad_parameter
goto bad_parameter


REM===================================================================
:bad_parameter
echo **********************
echo bad parameter
echo for 16m, usage: ir 16
echo for 32m, usage: ir 32
echo **********************
cd ir_vfd
goto end
REM===================================================================


REM============== start =====================
:start
del mipsel-elf\libir_8202.a
del ir_vfd\libir.a

cd ir_vfd
make

if %ERRORLEVEL%==0 goto MakeOK


REM============== MakeNG =====================
:MakeNG
echo *************************
echo Failed on generating libir.a
echo *************************

PAUSE
goto end


REM============== MakeOK =====================
:MakeOK
copy libir.a ..\mipsel-elf\libir_8202.a
goto end


REM============== end =====================
:end
cd..
