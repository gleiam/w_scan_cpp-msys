#!/usr/bin/env bash
set -euo pipefail
# Systemupdate: kann beim ersten Mal "restart required" melden -> Skript einfach erneut ausfuehren
pacman -Syu --noconfirm || true
pacman -Syu --noconfirm

pacman -S --needed --noconfirm \
  base-devel msys2-devel \
  pkgconf \
  libcurl-devel openssl-devel zlib-devel \
  gettext-devel \
  libzstd-devel libidn2-devel libpsl-devel brotli-devel libnghttp2-devel \
  dos2unix wget unzip

echo "=== Verifikation ==="
gcc -dumpmachine
g++ --version | head -1
make --version | head -1
pkg-config --modversion libcurl
echo "=== Diese Pakete duerfen NICHT im msys-Repo sein (Ausgabe leer erwartet) ==="
pacman -Ss '^pugixml$|^fontconfig$|^freetype$|^libjpeg|^libcap$' | grep '^msys/' || echo "(leer, ok)"
echo "=== Keine mingw-Pakete installiert (Ausgabe leer erwartet) ==="
pacman -Qq | grep '^mingw-w64' || echo "(leer, ok)"
