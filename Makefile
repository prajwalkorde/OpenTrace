KERN_SRC = src/open_kern.c
USER_SRC = src/open_user.c
KERNEL_HEADERS = /usr/src/linux-headers-$(shell uname -r)

all: open_kern.o open_user

open_kern.o: $(KERN_SRC) vmlinux.h
	clang -O2 -g -target bpf \
	-I. \
	-I$(KERNEL_HEADERS)/include \
	-I$(KERNEL_HEADERS)/include/uapi \
	-I$(KERNEL_HEADERS)/include/generated/uapi \
	-c $(KERN_SRC) -o open_kern.o

open_user: $(USER_SRC)
	gcc -Wall $(USER_SRC) -o open_user -lbpf -lelf -lz

clean:
	rm -f open_kern.o open_user

