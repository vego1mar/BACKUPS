#!/bin/bash
# This script is designed to use it with Linux shell.

RED_COLOR='\033[0;31m'
GREEN_COLOR='\033[0;32m'
NO_COLOR='\033[0m'
ARCHIVER_EXEC=/usr/bin/7z
GAMESAVE_DIR="/media/moon/26509ADF509AB4D1/Users/Mar/AppData/Roaming/DarkSoulsIII"
ARCHIVE_PATH=$HOME"/Documents/Projekty/BACKUPS/Dark_Souls_III__AppData_SL${1}.7z"

if [ ! -f "$ARCHIVER_EXEC" ]; then
  echo -e "${RED_COLOR}Archiver program does not exist within provided path.${NO_COLOR}"
  exit 1
fi

if [ ! -d "$GAMESAVE_DIR" ]; then
  echo -e "${RED_COLOR}Gamesave directory does not exist within provided path.${NO_COLOR}"
  exit 1
fi

echo -e "${GREEN_COLOR}Archiving Dark Souls III gamesaves...${NO_COLOR}"
"$ARCHIVER_EXEC" a -t7z -mx=9 -m0=lzma -md=128m -mfb=273 -mmt=4 -ms=on "$ARCHIVE_PATH" "${GAMESAVE_DIR}"
echo -e "${GREEN_COLOR}Script done.${NO_COLOR}"
