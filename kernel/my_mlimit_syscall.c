#include <linux/syscalls.h>
#include <linux/sched.h>

asmlinkage void sys_my_mlimit_syscall(pid_t nc, unsigned long max_mem) 
{
    struct task_struct *tsk = find_task_by_vpid(nc);
    get_task_struct(tsk);

    tsk->max_mem = max_mem;
}
