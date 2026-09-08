@echo off
rem Startet ein Kommando in der MSYS-Umgebung (nicht MINGW64/UCRT64!)
rem Aufruf: msys.cmd bash tools/build.sh
rem MSYS-Pfad: Standard C:\msys64, uebersteuerbar wie in build.cmd beschrieben.
setlocal
if not defined MSYS_ROOT set "MSYS_ROOT=C:\msys64"
if exist "%~dp0local-env.cmd" call "%~dp0local-env.cmd"
set "MSYSTEM=MSYS"
set "CHERE_INVOKING=1"
set "MSYS2_PATH_TYPE=minimal"
set "LANG=C.UTF-8"
if not exist "%MSYS_ROOT%\usr\bin\bash.exe" (
  echo FEHLER: kein MSYS-Bash unter "%MSYS_ROOT%\usr\bin\bash.exe" 1>&2
  exit /b 1
)
"%MSYS_ROOT%\usr\bin\bash.exe" -lc "%*"
endlocal
