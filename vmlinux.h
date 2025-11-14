#ifndef VMLINUX_H
#define VMLINUX_H

#include <linux/types.h>  // for __u32, __u64

struct trace_event_raw_sys_enter {
    __u64 __unused;      // padding if needed
    __u64 args[6];       // syscall arguments
};

#endif // VMLINUX_H

