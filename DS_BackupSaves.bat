@ECHO OFF
REM This script is designed to use it on Windows 10.

SET soulLevel=%1
SET taskSelector=0
SET textColor=FC
SET sevenZipExecPath="Y:\Aplikacje\7-Zip\7z.exe"
SET ds2SavesFolder="%AppData%\DarkSoulsII"
SET ds3SavesFolder="%AppData%\DarkSoulsIII"
SET backupFolder="Y:\Projekty\BACKUPS"
SET ds2ArchiveName="Dark_Souls_2_SotFS__AppData_SL*.7z"
SET ds3ArchiveName="Dark_Souls_III__AppData_SL*.7z"
SET ds2BackupName="Dark_Souls_2_SotFS__AppData_SL%soulLevel%.7z"
SET ds3BackupName="Dark_Souls_III__AppData_SL%soulLevel%.7z"

IF NOT EXIST %sevenZipExecPath% ( ECHO "Specified 7z.exe file has not been found. " & GOTO :ProgramClose )
IF NOT EXIST %backupFolder% ( ECHO "Specified backup folder does not exist. " & GOTO :ProgramClose )
IF NOT EXIST %ds2SavesFolder% ( ECHO "Dark Souls II saves has not been found. " & GOTO :ProgramClose )
IF NOT EXIST %ds3SavesFolder% ( ECHO "Dark Souls III saves has not been found. " & GOTO :ProgramClose )

REM "Create a temporary file in attempt to provide different color texts."
SETLOCAL EnableDelayedExpansion
FOR /F "tokens=1,2 delims=#" %%a IN ('"prompt #$H#$E# & echo on & for %%b in (1) do rem"') DO (
  SET "DEL=%%a"
)
<NUL > X SET /p ".=."

IF EXIST %backupFolder%\%ds2ArchiveName% (
    SET taskSelector=1
    CALL :PrintColorfulText %textColor% "Selecting Dark Souls II... "
) ELSE IF EXIST %backupFolder%\%ds3ArchiveName% (
    SET taskSelector=2
    CALL :PrintColorfulText %textColor% "Selecting Dark Souls III... "
) ELSE (
    CALL :PrintColorfulText %textColor% "Game saves archives has not been found in the backup folder. "
)

:TaskSelection
IF %taskSelector%==-1 (
    REM "Terminate script."
    GOTO :ProgramClose
) ELSE IF %taskSelector%==0 (
    REM "Print ending info and switch into script termination."
    GOTO :ProgramClosing
) ELSE IF %taskSelector%==1 (
    REM "Archive Dark Souls II saves."
    SET taskSelector=0
    %sevenZipExecPath% a -t7z -mx=9 -m0=LZMA2:d128m:fb273 -mmt=4 -ms=on -- %backupFolder%\%ds2BackupName% %ds2SavesFolder%
) ELSE IF %taskSelector%==2 (
    REM "Archive Dark Souls III saves."
    SET taskSelector=0
    %sevenZipExecPath% a -t7z -mx=9 -m0=LZMA2:d128m:fb273 -mmt=4 -ms=on -- %backupFolder%\%ds3BackupName% %ds3SavesFolder%
) 

:PrintColorfulText
SET "param=^%~2" !
SET "param=!param:"=\"!"
FINDSTR /p /A:%1 "." "!param!\..\X" NUL
<NUL SET /p ".=%DEL%%DEL%%DEL%%DEL%%DEL%%DEL%%DEL%"
GOTO :TaskSelection

:ProgramClosing
SET taskSelector=-1
CALL :PrintColorfulText %textColor% "Script end. "

:ProgramClose
IF EXIST "X" ( DEL X )
EXIT /B
