#!/usr/bin/env bash
# Separater femon-Verify (KEIN Bestandteil von tools/build.sh):
# stimmt genau einen Transponder ab und verlangt Lock.
# Lokal:   bash tools/verify-femon.sh   (SATIP_SERVER via Env/local-env)
# Spaeter: eigener GitHub-Job mit SAT>IP-Server im Netz.
#
# Konfiguration nur ueber Env/Flags, keine Pfade einchecken:
#   SATIP_SERVER    Pflicht, z.B. "192.168.1.1|DVBC-4|FRITZBox"
#   VERIFY_CHANNEL  VDR-Kanalzeile (Default: 610 MHz, DVB-C 64-QAM, SR 6900)
#   VERIFY_EXE      Binary (Default: dist/.../w_scan_cpp.exe)
#   VERIFY_TIMEOUT  Sekunden (Default: 40)
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT"
mkdir -p logs

TIMEOUT=40
while [ $# -gt 0 ]; do
  case "$1" in
    --satip-server) SATIP_SERVER="${2:?Wert fehlt}"; shift ;;
    --verify-channel) VERIFY_CHANNEL="${2:?Wert fehlt}"; shift ;;
    --exe) VERIFY_EXE="${2:?Wert fehlt}"; shift ;;
    --timeout) TIMEOUT="${2:?Wert fehlt}"; shift ;;
    -h|--help) sed -n '2,/^set -euo/p' "$0"; exit 0 ;;
    *) echo "FEHLER: unbekannte Option $1" >&2; exit 2 ;;
  esac
  shift
done

: "${SATIP_SERVER:?SATIP_SERVER fehlt (Env oder --satip-server)}"
: "${VERIFY_CHANNEL:=test:610000:I0C0M64:C:6900:0:0:0:0:1:0:0:0}"
: "${VERIFY_EXE:=dist/w_scan_cpp-msys-x86_64/w_scan_cpp.exe}"

[ -x "$VERIFY_EXE" ] || { echo "FEHLER: $VERIFY_EXE fehlt (erst Pipeline bauen)" >&2; exit 1; }

echo "Kanal: $VERIFY_CHANNEL"
set +e
timeout "$TIMEOUT" "$VERIFY_EXE" -f c -c DE -t --satip-server "$SATIP_SERVER" \
  -F "$VERIFY_CHANNEL" > logs/verify-femon.log 2>&1
rc=$?
set -e
# femon laeuft als Endlosschleife -> RC 124 (timeout) ist das erwartete Ende
[ "$rc" -eq 124 ] || { echo "FEHLER: femon endete mit RC=$rc statt 124" >&2; exit 1; }
grep -a "lock" logs/verify-femon.log | tail -3
grep -aq "lock 1" logs/verify-femon.log || { echo "FEHLER: kein Lock" >&2; exit 1; }
echo "VERIFY_OK: Transponder lockt"
