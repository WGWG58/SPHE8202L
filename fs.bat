echo off

if "%1" == "16" goto start
if "%1" == "32" goto start
if "%1" == "" goto bad_parameter
goto bad_parameter
REM===================================================================
:bad_parameter
echo **********************
echo bad parameter
echo for 16m, usage: fs 16
echo for 32m, usage: fs 32
echo **********************
goto end
REM===================================================================

:start
if exist fs_mp4\makefile call fs_mp4.bat %1
if not exist fs_mp4\libfs_mp4.a goto fs

if exist fs_mp4\parser\makefile call parser.bat %1
if not exist fs_mp4\parser\libparser.a goto fs

if exist fs_krnl\makefile call fs_krnl.bat %1
if not exist fs_krnl\libfs_krnl.a goto fs

if exist fs_midi\makefile call fs_midi.bat %1
REM if not exist fs_midi\libfs_midi.a goto fs

if exist fs_pmp\makefile call fs_pmp.bat %1
if not exist fs_pmp\libfs_pmp.a goto fs

:fs
if "%1" == "16" goto sdram16
if "%1" == "32" goto sdram32

REM =========================================
:sdram16
del fs\*.a
del mipsel-elf\libfs_16.a
cd fs
make
copy libfs.a ..\mipsel-elf\libfs_16.a
cd ..
if not exist fs\libfs.a goto failed
goto end
REM =========================================


REM =========================================
:sdram32
del fs\*.a
del mipsel-elf\libfs_8202.a
cd fs
make
copy libfs.a ..\mipsel-elf\libfs_8202.a
cd ..
if not exist fs\libfs.a goto failed
goto end
REM =========================================


REM ======================================
:failed
echo *************************
echo failed on generating libfs.a
REM ======================================


:end
