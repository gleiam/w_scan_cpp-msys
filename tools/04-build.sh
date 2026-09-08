#!/usr/bin/env bash
set -uo pipefail
cd "$(dirname "$0")/../w-scan-cpp-20260515+dfsg"
make -f Makefile.msys clean >/dev/null 2>&1 || true
make -f Makefile.msys -j"$(nproc)" -k 2>&1 | tee ../logs/04-build.log
echo "=== Fehlerzusammenfassung ==="
grep -E 'error:|undefined reference|fatal error' ../logs/04-build.log | sort | uniq -c | sort -rn | head -60 || true
