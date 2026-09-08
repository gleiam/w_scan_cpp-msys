#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/.."
W=w-scan-cpp-20260515+dfsg
mkpatch() {
  local src="$1" dst="$2" out="$3"
  if diff -u --label "a/${dst}" --label "b/${dst}" "$src" "$dst" > "$out"; then
    echo "UNVERAENDERT: $dst (kein Patch)"
    rm -f "$out"
  else
    code=$?
    if [ $code -eq 1 ]; then
      echo "PATCH: $out"
    else
      echo "FEHLER bei diff $src $dst"
      exit 1
    fi
  fi
}
mkpatch /tmp/pristine/tools.c            $W/vdr/tools.c   patches/101-vdr-tools-no-jpeg.patch
# 102 eingefroren (historisch, pre-112): NICHT regenerieren, sonst wuerde 112 in 102 aufgehen.
# mkpatch /tmp/pristine/thread.c           $W/vdr/thread.c  patches/102-vdr-thread-msys.patch
# 112 inkrementell auf 102: Basis = pristine + 102, Diff Basis -> aktuell
cp /tmp/pristine/thread.c /tmp/thread-112-base.c
patch -s /tmp/thread-112-base.c < patches/102-vdr-thread-msys.patch
diff -u --label a/$W/vdr/thread.c --label b/$W/vdr/thread.c \
  /tmp/thread-112-base.c $W/vdr/thread.c > patches/112-vdr-thread-sleepms-msys.patch || [ $? -eq 1 ]
echo "PATCH: patches/112-vdr-thread-sleepms-msys.patch (inkrementell auf 102)"
mkpatch /tmp/pristine/satip/poller.c     $W/vdr/PLUGINS/src/satip/poller.c patches/103-satip-poller-poll.patch
mkpatch /tmp/pristine/satip/poller.h     $W/vdr/PLUGINS/src/satip/poller.h patches/103-satip-poller-poll.patch.h
mkpatch /tmp/pristine/satip/common.h     $W/vdr/PLUGINS/src/satip/common.h patches/104-satip-common-strerror.patch
mkpatch /tmp/pristine/vdr/tools.h        $W/vdr/tools.h   patches/105-vdr-tools-h-msys.patch
mkpatch /tmp/pristine/vdr/i18n.h         $W/vdr/i18n.h    patches/106-vdr-i18n-format-arg.patch
mkpatch /tmp/pristine/vdr/svdrp.c        $W/vdr/svdrp.c   patches/107-vdr-svdrp-socklen.patch
mkpatch /tmp/pristine/vdr/eit.c          $W/vdr/eit.c     patches/108-vdr-eit-no-clockset.patch
# SAT>IP-Laufzeitfixes (pristine aus orig.tar.xz + orig-vdr.tar.xz)
P2=/tmp/pristine2/vdr/PLUGINS/src/vdr-plugin-satip
mkpatch $P2/sectionfilter.c $W/vdr/PLUGINS/src/vdr-plugin-satip/sectionfilter.c patches/109-satip-sectionfilter-dgram.patch
diff -u --label a/$W/vdr/PLUGINS/src/vdr-plugin-satip/socket.c --label b/$W/vdr/PLUGINS/src/vdr-plugin-satip/socket.c \
  $P2/socket.c $W/vdr/PLUGINS/src/vdr-plugin-satip/socket.c > patches/110-satip-socket-multijoin.patch || [ $? -eq 1 ]
diff -u --label a/$W/vdr/PLUGINS/src/vdr-plugin-satip/socket.h --label b/$W/vdr/PLUGINS/src/vdr-plugin-satip/socket.h \
  $P2/socket.h $W/vdr/PLUGINS/src/vdr-plugin-satip/socket.h >> patches/110-satip-socket-multijoin.patch || [ $? -eq 1 ]
diff -u --label a/$W/vdr/PLUGINS/src/vdr-plugin-satip/msearch.c --label b/$W/vdr/PLUGINS/src/vdr-plugin-satip/msearch.c \
  $P2/msearch.c $W/vdr/PLUGINS/src/vdr-plugin-satip/msearch.c > patches/111-satip-msearch-multihomed.patch || [ $? -eq 1 ]
diff -u --label a/$W/vdr/PLUGINS/src/vdr-plugin-satip/msearch.h --label b/$W/vdr/PLUGINS/src/vdr-plugin-satip/msearch.h \
  $P2/msearch.h $W/vdr/PLUGINS/src/vdr-plugin-satip/msearch.h >> patches/111-satip-msearch-multihomed.patch || [ $? -eq 1 ]
echo "PATCH: patches/109, 110 (c+h), 111 (c+h)"
# poller .c/.h zu einem Patch zusammenfassen
if [ -f patches/103-satip-poller-poll.patch.h ]; then
  cat patches/103-satip-poller-poll.patch.h >> patches/103-satip-poller-poll.patch
  rm patches/103-satip-poller-poll.patch.h
  echo "PATCH: patches/103-satip-poller-poll.patch (c+h kombiniert)"
fi
find patches -type f -exec dos2unix -q {} +
ls -l patches/
