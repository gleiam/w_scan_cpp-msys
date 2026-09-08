@echo off
rem Einstieg in die Build-Pipeline ab Windows.
rem Aufruf: build.cmd [--msys-root PFAD] [--skip-install]
rem
rem MSYS-Pfad, Prioritaet aufsteigend:
rem   1. Standard C:\msys64
rem   2. Session-Env MSYS_ROOT
rem   3. local-env.cmd neben dieser Datei (LOKAL, nicht einchecken!)
rem   4. --msys-root Argument
setlocal EnableDelayedExpansion
set "REPO=%~dp0"
if not defined MSYS_ROOT set "MSYS_ROOT=C:\msys64"
if exist "%REPO%local-env.cmd" call "%REPO%local-env.cmd"
set "FWD="
:parse
if "%~1"=="" goto run
if /i "%~1"=="--msys-root" (
  set "MSYS_ROOT=%~2"
  shift
  shift
  goto parse
)
set "FWD=!FWD! %1"
shift
goto parse
:run
if not exist "%MSYS_ROOT%\usr\bin\bash.exe" (
  echo FEHLER: kein MSYS-Bash unter "%MSYS_ROOT%\usr\bin\bash.exe" 1>&2
  echo Standard ist C:\msys64, anders via MSYS_ROOT, local-env.cmd oder --msys-root 1>&2
  exit /b 1
)
set "MSYSTEM=MSYS"
set "CHERE_INVOKING=1"
set "MSYS2_PATH_TYPE=minimal"
set "LANG=C.UTF-8"
"%MSYS_ROOT%\usr\bin\bash.exe" -lc "cd \"$(cygpath -u '%REPO%')\" && exec bash tools/build.sh!FWD!"
endlocal
