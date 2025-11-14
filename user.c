#include <stdio.h>
#include <stdlib.h>
#include <bpf/libbpf.h>
#include <bpf/bpf.h>
#include <unistd.h>

int main(int argc, char **argv){
	struct bpf_object *obj;
	int err;

	obj = bpf_object__open_file("open_kern.o", NULL);

	if(libbpf_get_error(obj)){
		fprintf(stderr, "Failed to open BPF object\n");
		return 1;
	}

	err = bpf_object__load(obj);
	if(err){
		fprintf(stderr,  "Failed to load BPF object: %d\n", err);
		return 1;
	}

	struct bpf_program *prog = bpf_object__find_program_by_name(obj, "handle_open");
	if(!prog){
		fprintf(stderr, "Failed to find BPF program\n");
		return 1;
	}

	err = bpf_program__attach_tracepoint(prog, "syscalls", "sys_enter_openat");
	if(err < 0){
		fprintf(stderr, "Failed to attach to tracepoint: %d\n", err);
		return 1;
	}

	printf("BPF program loaded and attached. Tracing open() syscalls.. \n");

	while(1){
		sleep(1);
	}

	return 0;

}
