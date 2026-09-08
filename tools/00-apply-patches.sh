#!/usr/bin/env bash
# Wendet alle vendored Patches (101-112) strikt auf einen PRISTINE Tree an.
# Nur auf frischem Checkout / entpackten Orig-Quellen laufen lassen (kein --forward:
# bereits angewendete Patches schlagen bewusst FEHL, statt still uebersprungen zu werden).
set -euo pipefail
cd "$(dirname "$0")/.."

PATCHES=(
  patches/101-vdr-tools-no-jpeg.patch
  patches/102-vdr-thread-msys.patch
  patches/103-satip-poller-poll.patch
  patches/104-satip-common-strerror.patch
  patches/105-vdr-tools-h-msys.patch
  patches/106-vdr-i18n-format-arg.patch
  patches/107-vdr-svdrp-socklen.patch
  patches/108-vdr-eit-no-clockset.patch
  patches/109-satip-sectionfilter-dgram.patch
  patches/110-satip-socket-multijoin.patch
  patches/111-satip-msearch-multihomed.patch
  patches/112-vdr-thread-sleepms-msys.patch
)

for p in "${PATCHES[@]}"; do
  [ -s "$p" ] || { echo "FEHLT: $p"; exit 1; }
  patch -p1 < "$p"
  echo "APPLIED: $p"
done

echo "=== LF-Check (kein CR in gepatchten Quellen erwartet) ==="
if grep -rlU --include='*.c' --include='*.h' --include='*.cpp' --include='*.hpp' \
    $'\r' w-scan-cpp-20260515+dfsg/vdr/tools.c \
    w-scan-cpp-20260515+dfsg/vdr/thread.c \
    w-scan-cpp-20260515+dfsg/vdr/PLUGINS/src/satip/poller.c \
    w-scan-cpp-20260515+dfsg/vdr/PLUGINS/src/vdr-plugin-satip/ 2>/dev/null; then
  echo "FEHLER: CR gefunden"
  exit 1
fi
echo "PATCHES_OK: ${#PATCHES[@]} Patches angewendet, LF sauber"
