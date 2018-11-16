#!/bin/bash
RED_COLOR='\033[0;31m'
GREEN_COLOR='\033[0;32m'
NO_COLOR='\033[0m'
ARCHIVER_EXEC=/usr/bin/7z
GAMESAVE_DIR=$HOME"/.steam/steam/steamapps/compatdata/335300/pfx/drive_c/users/steamuser/Application Data/DarkSoulsII"
ARCHIVE_PATH=$HOME"/Archiwum lokalne/Projekty/BACKUPS/Dark_Souls_2_SotFS__AppData_SL${1}.7z"

if [ ! -f "$ARCHIVER_EXEC" ]; then
  echo -e "${RED_COLOR}Archiver program does not exist within provided path.${NO_COLOR}"
  exit 1
fi

if [ ! -d "$GAMESAVE_DIR" ]; then
  echo -e "${RED_COLOR}Gamesave directory does not exist within provided path.${NO_COLOR}"
  exit 1
fi

echo -e "${GREEN_COLOR}Archiving Dark Souls II gamesaves...${NO_COLOR}"
"$ARCHIVER_EXEC" a -t7z -mx=9 -m0=lzma -md=128m -mfb=273 -mmt=4 -ms=on "$ARCHIVE_PATH" "${GAMESAVE_DIR}"
echo -e "${GREEN_COLOR}Script done.${NO_COLOR}"
