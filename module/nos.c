#include <linux/module.h>    
#include <linux/kernel.h>    
#include <linux/init.h>      
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/unistd.h>
#include <linux/sched/signal.h>



MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mihajlo");
MODULE_DESCRIPTION("Process list");

static int __init hello_init(void)
{
    printk(KERN_INFO "Loaded NOS Process module!\n");
    printk(KERN_INFO "PID \t PPID \t PNAME \t\t SIZE \t NICE \t PRIORITY \t TIME \t OWNER");
    struct task_struct *task;
    struct mm_struct *mm;
    int nice = 0;
    int mem = 0;
    for_each_process(task)
    {
        mm = get_task_mm(task);
        if(mm != NULL){
            mem = mm->total_vm;
        } else {
            mem = 0;
        }
        nice=task_nice(task);
        
        printk(KERN_INFO "%d \t %d \t %s \t %d \t %d \t %d \t %llu \t %d \n",
                task->pid, task_ppid_nr(task), task->comm, mem, nice,task->prio,task->utime,task->real_cred->uid.val);
    }

    return 0;    
}

static void __exit hello_cleanup(void)
{
    printk(KERN_INFO "Cleaning up NOS Process module.\n");
}

module_init(hello_init);
module_exit(hello_cleanup);