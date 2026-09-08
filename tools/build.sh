#!/usr/bin/env bash
# Reproduzierbare Build-Pipeline fuer w_scan_cpp (SAT>IP-only) unter MSYS2.
#
# Laeuft IN einer MSYS-Bash (nicht MINGW64/UCRT64). Einstieg ab Windows:
#   build.cmd [--msys-root C:\msys64] [Pipeline-Optionen]
# Direkt aus MSYS:  bash tools/build.sh [Optionen]
#
# Stufen: 1) MSYS-Pakete  2) Patches 101-112  3) Vendor/Hygiene
#         4) librepfunc   5) Build (+Gate)     6) Paket  7) Smoke-Test
#
# KEIN Verify in der Pipeline: das laeuft separat (spaeter auf GitHub),
# lokal bei Bedarf via:  bash tools/verify-femon.sh
#
# Konfiguration nur ueber Env/Flags, keine Pfade einchecken.
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT"
mkdir -p logs

SKIP_INSTALL=0

usage() {
  sed -n '2,/^set -euo/p' "$0"
  echo "Optionen: --skip-install"
}

while [ $# -gt 0 ]; do
  case "$1" in
    --skip-install) SKIP_INSTALL=1 ;;
    -h|--help) usage; exit 0 ;;
    *) echo "FEHLER: unbekannte Option $1" >&2; usage >&2; exit 2 ;;
  esac
  shift
done

EXE="w-scan-cpp-20260515+dfsg/w_scan_cpp.exe"

if [ "$SKIP_INSTALL" -eq 0 ]; then
  echo "===== [1/7] MSYS-Pakete (tools/01-install.sh) ====="
  bash tools/01-install.sh 2>&1 | tee logs/build-01-install.log
else
  echo "===== [1/7] MSYS-Pakete uebersprungen (--skip-install) ====="
fi

echo "===== [2/7] Patches 101-112 (tools/00-apply-patches.sh) ====="
bash tools/00-apply-patches.sh 2>&1 | tee logs/build-02-patches.log

echo "===== [3/7] Vendor/Hygiene (tools/02-prepare.sh) ====="
bash tools/02-prepare.sh 2>&1 | tee logs/build-03-prepare.log

echo "===== [4/7] librepfunc (tools/03-librepfunc.sh) ====="
bash tools/03-librepfunc.sh 2>&1 | tee logs/build-04-librepfunc.log

echo "===== [5/7] Build (tools/04-build.sh) ====="
bash tools/04-build.sh 2>&1 | tail -20
if [ ! -x "$EXE" ]; then
  echo "FEHLER: $EXE fehlt nach Build" >&2; exit 1
fi
if grep -E 'error:|undefined reference|fatal error' logs/04-build.log | grep -qv 'strerror'; then
  echo "FEHLER: Fehlerzeilen in logs/04-build.log" >&2; exit 1
fi
echo "BUILD_OK: $EXE"
"$EXE" --help > logs/build-05-help.txt 2>&1
grep -q "w_scan_cpp Version" logs/build-05-help.txt
echo "GATE_OK: --help laeuft"

echo "===== [6/7] Paket (tools/05-package.sh) ====="
bash tools/05-package.sh > logs/build-06-package.log 2>&1
tail -3 logs/build-06-package.log

echo "===== [7/7] Smoke-Test (dist-Binary, ohne Netz) ====="
DIST_EXE="dist/w_scan_cpp-msys-x86_64/w_scan_cpp.exe"
[ -x "$DIST_EXE" ] || { echo "FEHLER: $DIST_EXE fehlt" >&2; exit 1; }
"$DIST_EXE" --help > logs/build-07-smoke.log 2>&1
grep -q "w_scan_cpp Version" logs/build-07-smoke.log
echo "SMOKE_OK: dist --help laeuft"
# msys-DLLs muessen im Paket liegen (selbständig), Rest nur aus System32
ldd_ok=1
while read -r dll target _; do
  case "$dll" in
    msys-*)
      [ -f "dist/w_scan_cpp-msys-x86_64/$dll" ] || { echo "FEHLT im Paket: $dll"; ldd_ok=0; } ;;
    *)
      case "$target" in
        /[Cc]/[Ww][Ii][Nn][Dd][Oo][Ww][Ss]/[Ss][Yy][Ss][Tt][Ee][Mm]32/*) ;;
        *) echo "FREMD: $dll => $target"; ldd_ok=0 ;;
      esac ;;
  esac
done < <(ldd "$DIST_EXE" | awk '/=>/{print $1, $3}')
[ "$ldd_ok" -eq 1 ] || { echo "FEHLER: unerwartete DLL-Abhaengigkeit" >&2; exit 1; }
echo "SMOKE_OK: Paket selbstaendig (msys-DLLs gebuendelt, Rest System32)"
echo "PIPELINE_OK"
