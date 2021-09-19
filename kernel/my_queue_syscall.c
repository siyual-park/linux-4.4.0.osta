#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/vmalloc.h>

#define MY_QUEUE_SYSCALL_DEFAULT_QUEUE 512

int max_size = 0;
int *queue = 0;
int size = 0;


void print_queue(void)
{
    int i = 0;
    while (i < size) {
        printk(KERN_CRIT "Queue: %d\n", queue[i]);
        i++;
    }
}

asmlinkage void sys_my_enqueue(int n) 
{
    if (max_size == 0) {
        max_size = MY_QUEUE_SYSCALL_DEFAULT_QUEUE;
        queue = vmalloc(sizeof(int) * max_size);
    }

    if (size + 1 > max_size) {
        max_size = (int) (max_size * 1.5);
        int *new_queue = vmalloc(sizeof(int) * max_size);
        int i = 0;
        while (i < size) {
            new_queue[i] = queue[i];
            i++;
        }
        vfree(queue);
        queue = new_queue;
    }

    queue[size++] = n;
    printk(KERN_CRIT "Enqueue: %d\n", n);
    print_queue();
}

asmlinkage int sys_my_dequeue(void)
{
    if (size <= 0) {
        return 0;
    }

    int first = queue[0];
    int i = 0;
    while (i < size - 1) {
        queue[i] = queue[i + 1];
        i++;
    }
    size--;

    printk(KERN_CRIT "Dnqueue: %d\n", first);
    print_queue();
    
    return first;
}