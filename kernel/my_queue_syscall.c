#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/vmalloc.h>

#define MY_QUEUE_SYSCALL_DEFAULT_QUEUE 512

int max_size = MY_QUEUE_SYSCALL_DEFAULT_QUEUE;
int *queue = vmalloc(sizeof(int) * max_size);
int size = 0;

asmlinkage void sys_my_enqueue(int n) 
{
    if (size + 1 > max_size) {
        max_size = max_size * 1.5;
        int *new_queue = vmalloc(sizeof(int) * max_size);
        for (int i = 0; i < size; i++) {
            new_queue[i] = queue[i];
        }
        vfree(queue);
        queue = new_queue;
    }

    queue[size++] = n;
    printk(KERN_CRIT, "Enqueue: %d\n", n);
    print_queue();
}

asmlinkage int sys_my_dequeue(void)
{
    if (size <= 0) {
        return 0;
    }

    int first = queue[0];
    for (int i = 0; i < size - 1; i++) {
        queue[i] = queue[i + 1];
    }
    size--;

    printk(KERN_CRIT, "Dnqueue: %d\n", first);
    print_queue();
    
    return first;
}

void print_queue()
{
    for (int i = 0; i < size; i++)
        printk(KERN_CRIT, "Queue: %d\n", queue[i]);
}