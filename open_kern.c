#include <linux/types.h>
#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>

char LICENSE[] SEC("license") = "GPL";

SEC("tracepoint/syscalls/sys_enter_openat")

int handle_open(struct trace_event_raw_sys_enter *ctx){
	__u32 pid = bpf_get_current_pid_tgid() >> 32;

	char comm[16];
	bpf_get_current_comm(comm, sizeof(comm));

	const char *filename = (const char *)ctx->args[1];
	char fname_buf[256];
	bpf_probe_read_user_str(fname_buf, sizeof(fname_buf), filename);

	bpf_printk("PID=%d COMM=%s FILE=%s\n", pid, comm, fname_buf);

	return 0;
}

