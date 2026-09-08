#ifndef _SHIM_LINUX_TYPES_H
#define _SHIM_LINUX_TYPES_H
#include <stdint.h>
#include <sys/types.h>
typedef uint8_t  __u8;   typedef int8_t  __s8;
typedef uint16_t __u16;  typedef int16_t __s16;
typedef uint32_t __u32;  typedef int32_t __s32;
typedef uint64_t __u64;  typedef int64_t __s64;
typedef uint16_t __le16, __be16; typedef uint32_t __le32, __be32; typedef uint64_t __le64, __be64;
#define __aligned_u64 __u64 __attribute__((aligned(8)))
#include <linux/ioctl.h>
#endif
