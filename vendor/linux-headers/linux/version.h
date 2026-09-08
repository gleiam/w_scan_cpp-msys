#ifndef _SHIM_LINUX_VERSION_H
#define _SHIM_LINUX_VERSION_H
/* Minimaler Ersatz fuer das generierte UAPI-Header linux/version.h.
   Unter MSYS gibt es weder /dev/lirc noch Kernel-LIRC: LINUX_VERSION_CODE
   bewusst niedrig, damit vdr/lirc.c HAVE_KERNEL_LIRC=0 setzt und nur den
   Userspace-LIRC-Pfad (Socket, auf Cygwin vorhanden) uebersetzt. */
#define KERNEL_VERSION(a,b,c) (((a) << 16) + ((b) << 8) + (c))
#define LINUX_VERSION_CODE 0
#define LINUX_VERSION_MAJOR 0
#define LINUX_VERSION_PATCHLEVEL 0
#define LINUX_VERSION_SUBLEVEL 0
#endif
