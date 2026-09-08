#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/../vendor/librepfunc-1.11.2"

echo "=== Verdaechtige Linux-Only-Stellen ==="
grep -nE 'execinfo|backtrace|sys/prctl|prctl\(|dlopen|__linux__|libunwind|unwind\.h' *.cpp *.h *.c 2>/dev/null || echo "(keine)"

# Objekte direkt bauen, Makefile-Regeln fuer .so umgehen
# Flags aus vendor-Makefile uebernommen, angepasst fuer MSYS/Cygwin:
# bares -D_POSIX_C_SOURCE versteckt popen/pclose, daher 200809L + _GNU_SOURCE
rm -f *.o librepfunc.a
CXXFLAGS="-O2 -g -fPIC -std=gnu++17 -Wall -DVERSION=\"1.11.2\" -D_GNU_SOURCE -D_POSIX_C_SOURCE=200809L -I."
for f in *.cpp; do g++ $CXXFLAGS -c "$f" -o "${f%.cpp}.o"; done
ar rcs librepfunc.a *.o
ranlib librepfunc.a
nm -C librepfunc.a | grep -c ' T ' && echo "LIBREPFUNC_OK"
ls -l librepfunc.a
