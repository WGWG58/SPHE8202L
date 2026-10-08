@echo off
cpp -P -traditional -D__EMU__ -DFINALSYS -I. -Ih/ -x c++ 1.bak > 1_run.bat
call 1_run.bat %1
