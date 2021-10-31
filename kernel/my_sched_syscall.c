#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/module.h>

int faster_PID = -1;
int slower_PID = -1;

EXPORT_SYMBOL(faster_PID);
EXPORT_SYMBOL(slower_PID);

asmlinkage long sys_higher_priority(int pid) {
    faster_PID = pid;
    printk(KERN_CRIT "faster_PID: %d", pid);

    return faster_PID;
}
asmlinkage long sys_lower_priority(int pid) {
    slower_PID = pid;
    printk(KERN_CRIT "slower_PID: %d", pid);

    return slower_PID;
}
