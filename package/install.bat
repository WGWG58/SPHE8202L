@ECHO OFF
ECHO Start Copy Files...
copy totalio.sys %windir%\system32
ECHO Registering...
totalio.exe -remove
totalio.exe -install
ECHO Now restart to use the ep4.exe here in WINDOWS 2000/XP!!
