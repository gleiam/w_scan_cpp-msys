#ifndef _SHIM_LINUX_IOCTL_H
#define _SHIM_LINUX_IOCTL_H
#include <sys/ioctl.h>
/* Cygwin/MSYS liefert _IO/_IOR/_IOW/_IOWR ueber <asm/socket.h>. Falls nicht: Dummywerte,
   es wird unter MSYS nie ein DVB-ioctl abgesetzt. */
#ifndef _IO
#define _IO(t,n)      (0)
#define _IOR(t,n,s)   (0)
#define _IOW(t,n,s)   (0)
#define _IOWR(t,n,s)  (0)
#endif
#endif
