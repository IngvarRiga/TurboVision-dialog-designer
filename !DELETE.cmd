ECHO OFF
ECHO ================================================================================
ECHO -- CLEARING PROJECT -- 
ECHO ================================================================================
ECHO -- Deleting trash ...
del /S *.bak
rem del /S *.pdb
del /S *.tmp
del /S *.obj
del /S *.ilk

rd /S /Q .vs\tvdd
rd /S /Q tvdd\x64
ECHO ================================================================================
ECHO -- Finish garbage. Press Any key :) ...
ECHO ================================================================================

pause
