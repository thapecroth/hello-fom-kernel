#### Notion format of this readme: https://varicb.notion.site/EPref-8c99b4d6ce16420c8a6d684a27933de8 

### Motivation

1. Give the ability to analyze and predict the power usage of any program. Specifically in the data center since they have large environmental effects, consuming 1-2 % of energy consumption. Moreover, many programs are repetitive and possibly run the same over a long period. Thus, we want to approximate energy usage in sub-routine level to optimize energy consumption for any given task.

### Previous work/ limitations

1. The conventional solutions measure power usage for the whole machine or CPU socket at best and using the power drain rate to calculate the power consumption. This can be in-accurate. First, there is no guarantee that the program that we are interesting is the only program that is running on that CPU. Second, it doesn’t give a fine granularity over which part of the program cause the high usage.
2. CPU architecture dependent and required specific information from the hardware which might not be available in all platform.

### Solutions

1. create environment to collect program’s performance counter.
    1. make sure that program is run in isolation using taskset to pin the process and clear others.
    2. ensure that the program run longer than 1ms, and collect performance’s counter via Intel PCM or Linux Perf.
    3. use reported values from the package domain.
2. Building linear model using CVXPY to predict the power usage measure from RAPL (ground truth) given the performance’s counter.

### Future Improvements

1. We can try many others machine learning models either classical or more neural networks base in case they give better performance. To still having good interpretability of the feature, we can use GLM or GAM.
2. From reading the introduction, I think the overarching goal of this research is to give a debugger like experience, so that the programmer can identify and justify their program energy usage. However, with the current research we can measure on the energy usage of the overall program and doesn’t provide insight into which function of the code contribute to the energy usage. My hypothesis is that it might also be possible for us to predict the energy consumption using the code chunk sets as an input, so that we can compile function chunk and give programmer the feedback about each function energy consumption and choose the implementation that serve their goals best.
3. 

### Issue while developing the code

1. Using Attu
    1. Due to being an undergraduate, I only have a 10 Gb file limitation, which is exceeded by the img filesize.
2. Installing Qemu
    1. There is no binary release of Qemu in the window. Thus, I was using WSL(Window Subsystem for Linux), which makes running Qemu even slower due to multiple virtualization overhead.
    2. I hesitated in installing Qemu on Windows due to a lack of proper support and though to give docker a try.
    3. I just realized after already spawning docker that they are sharing kernel. Thus, I switched back to Qemu
    4. I found a project called Msys which gives windows linux a building toolchain. I installed it and built Qemu with Pacman.

### Running code

## Pre-req

```bash
sudo apt update
sudo apt install build-essential -y
```

## The code

```c
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("MIT");
MODULE_AUTHOR("Varich Boonsanong");
MODULE_DESCRIPTION("A simple kernel that say hello and goodbye to you");

static int __init init(void) {
  printk(KERN_ALERT"Hello world\n");
  return 0;
}

static void __exit cleanup(void) { printk(KERN_ALERT"Goodbye!\n"); }

module_init(init);
module_exit(cleanup);
```

```makefile
obj-m += hello.o

all:
        make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
        make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```

compile the program using `make -j 10`

add module using `sudo insmod ./hello.ko`, will get `Hello world` in the console.

removing the module using `sudo rmmod hello`, will get Goodbye! in the console.
