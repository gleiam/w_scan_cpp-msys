#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/.."
SRC_WIN="$(pwd)"
echo "SRC=$SRC_WIN"

echo "=== 3.2 vdr-Symlink-Check ==="
cd w-scan-cpp-20260515+dfsg
FOUND=0
while IFS= read -r f; do
  # kleine Dateien <=200c, einzeilig, Inhalt sieht wie Pfad aus
  if [ "$(wc -l <"$f")" -le 1 ]; then
    content="$(cat "$f")"
    case "$content" in
      ../*|./*|*/*.c|*/*.h|*/*.cpp)
        echo "VERDACHT: $f -> $content"
        FOUND=1
        ;;
    esac
  fi
done < <(find vdr -type f -size -200c)
if [ "$FOUND" -eq 0 ]; then
  echo "SYMLINK_OK: keine Verdaechtigen"
fi
# echte Symlinks zeigen
ls -la vdr/PLUGINS/src/ | head -10
cd ..

echo "=== 3.3 pugixml vendoren ==="
# Normalfall (Repo/CI): vendor/pugixml ist entpackt committed (pugixml.cpp/hpp, pugiconfig.hpp).
# Legacy-Fallback (lokal): aus orig-Tarball extrahieren, falls vorhanden und vendor leer.
if [ ! -s vendor/pugixml/pugixml.cpp ] && [ -f pugixml_1.16.orig.tar.gz ]; then
  mkdir -p vendor/pugixml
  tar xzf pugixml_1.16.orig.tar.gz --strip-components=2 -C vendor/pugixml \
      --wildcards '*/src/pugixml.cpp' '*/src/pugixml.hpp' '*/src/pugiconfig.hpp'
  echo "extrahiert aus Tarball (legacy)"
fi
ls -l vendor/pugixml
count="$(ls vendor/pugixml | wc -l)"
if [ "$count" -ne 3 ]; then
  echo "FEHLER: vendor/pugixml enthaelt $count Dateien, erwartet 3"
  exit 1
fi
echo "PUGIXML_OK"

echo "=== 3.4 Linux-Header-Shim ==="
mkdir -p vendor/linux-headers/linux/dvb
B=https://raw.githubusercontent.com/torvalds/linux/master/include/uapi/linux
for f in dvb/frontend.h dvb/dmx.h dvb/version.h dvb/ca.h; do
  if [ ! -s "vendor/linux-headers/linux/$f" ]; then
    wget -q -O "vendor/linux-headers/linux/$f" "$B/$f"
    echo "geladen: $f"
  else
    echo "vorhanden: $f"
  fi
done
ls -l vendor/linux-headers/linux/dvb/ vendor/linux-headers/linux/
