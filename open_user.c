#include <bpf/libbpf.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
	struct bpf_object *obj;
	int err;

	obj = bpf_object__open_file("open_kern.o", NULL);
	if(!obj){
		printf("Failed to open BPF object\n");
		return 1;
	}

	err = bpf_object__load(obj);
	if(err){
		printf("Failed to load BPF program\n");
		return 1;
	}

	printf("Tracing file opens... Press Ctrl-C to stop.\n");

	int trace_fd = open("/sys/kernel/debug/tracing/trace_pipe", O_RDONLY);
	if(trace_fd < 0){
		perror("open trace_pipe");
		return 1;
	}

	while(1){
		char buf[40936];
		int n = read(trace_fd, buf, sizeof(buf) - 1);
		if(n>0){
			buf[n] = '\0';
			printf("%s", buf);
		}
	}

	return 0;
}
