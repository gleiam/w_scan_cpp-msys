#!/usr/bin/env bash
# Reproduzierbare Build-Pipeline fuer w_scan_cpp (SAT>IP-only) unter MSYS2.
#
# Laeuft IN einer MSYS-Bash (nicht MINGW64/UCRT64). Einstieg ab Windows:
#   build.cmd [--msys-root C:\msys64] [Pipeline-Optionen]
# Direkt aus MSYS:  bash tools/build.sh [Optionen]
#
# Stufen: 1) MSYS-Pakete  2) Patches 101-112  3) Vendor/Hygiene
#         4) librepfunc   5) Build (+Gate)     6) Paket  7) femon-Verify
#
# Konfiguration nur ueber Env/Flags, keine Pfade einchecken:
#   SATIP_SERVER    z.B. "192.168.1.1|DVBC-4|FRITZBox" (leer = Verify wird uebersprungen)
#   VERIFY_CHANNEL  VDR-Kanalzeile fuer den femon-Einzeltransponder-Test
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT"
mkdir -p logs

SKIP_INSTALL=0
SKIP_VERIFY=0
: "${SATIP_SERVER:=}"
: "${VERIFY_CHANNEL:=test:610000:I0C0M64:C:6900:0:0:0:0:1:0:0:0}"

usage() {
  sed -n '2,/^set -euo/p' "$0"
  echo "Optionen: --skip-install  --skip-verify"
  echo "          --satip-server \"IP|MODEL|DESC\"  --verify-channel \"VDR-Zeile\""
}

while [ $# -gt 0 ]; do
  case "$1" in
    --skip-install) SKIP_INSTALL=1 ;;
    --skip-verify) SKIP_VERIFY=1 ;;
    --satip-server) SATIP_SERVER="${2:?Wert fehlt}"; shift ;;
    --verify-channel) VERIFY_CHANNEL="${2:?Wert fehlt}"; shift ;;
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

if [ "$SKIP_VERIFY" -eq 1 ] || [ -z "$SATIP_SERVER" ]; then
  echo "===== [7/7] femon-Verify uebersprungen (kein SATIP_SERVER / --skip-verify) ====="
  echo "PIPELINE_OK (ohne Verify)"
  exit 0
fi

echo "===== [7/7] femon-Verify: einzelner Transponder ====="
echo "Kanal: $VERIFY_CHANNEL"
set +e
timeout 40 "$EXE" -f c -c DE -t --satip-server "$SATIP_SERVER" \
  -F "$VERIFY_CHANNEL" > logs/build-07-verify.log 2>&1
rc=$?
set -e
# femon laeuft als Endlosschleife -> RC 124 (timeout) ist das erwartete Ende
if [ "$rc" -ne 124 ]; then
  echo "FEHLER: femon endete mit RC=$rc statt 124 (siehe logs/build-07-verify.log)" >&2; exit 1
fi
grep -a "lock" logs/build-07-verify.log | tail -3
if grep -aq "lock 1" logs/build-07-verify.log; then
  echo "VERIFY_OK: Transponder lockt"
else
  echo "FEHLER: kein Lock (siehe logs/build-07-verify.log)" >&2; exit 1
fi
echo "PIPELINE_OK"
