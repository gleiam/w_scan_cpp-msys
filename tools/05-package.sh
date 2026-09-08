#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/.."
OUT=dist/w_scan_cpp-msys-x86_64
rm -rf "$OUT"; mkdir -p "$OUT"
cp w-scan-cpp-20260515+dfsg/w_scan_cpp.exe "$OUT/"
# alle DLLs aus /usr/bin, die ldd meldet (Windows-System-DLLs werden nicht kopiert)
ldd w-scan-cpp-20260515+dfsg/w_scan_cpp.exe | awk '/=> \/usr\/bin\//{print $3}' | sort -u | while read -r d; do cp -v "$d" "$OUT/"; done
# Lizenzhinweise fuer msys-2.0.dll (LGPLv3) und curl/openssl beilegen
mkdir -p "$OUT/licenses"
cp /usr/share/licenses/msys2-runtime/* "$OUT/licenses/" 2>/dev/null || true
cp /usr/share/licenses/curl/* "$OUT/licenses/" 2>/dev/null || true
ls -l "$OUT"
