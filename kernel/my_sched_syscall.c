#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/module.h>

int faster_PID = -1;
int slower_PID = -1;

EXPORT_SYSBOL(faster_PID);
EXPORT_SYSBOL(slower_PID);

asmlinkage long sys_higher_priority(int pid) {
    faster_PID = pid;
    return faster_PID;
}
asmlinkage long sys_lower_priority(int pid) {
    slower_PID = pid;
    return slower_PID;
}