obj-m := mydev.o #这里是上面所创建的c文件名.o
PWD := $(shell pwd) 
KERNELDIR := /lib/modules/4.20.10/build/ #你要安装mod的内核版本 
all: 
	make -C $(KERNELDIR) M=$(PWD) modules 
.PHONY: clean 
clean: 
	rm -rf *.o *~ core *.ko *.mod.c modules.order Module.symvers

