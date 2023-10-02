#include <linux/kernel.h>
#include <linux/resource.h>
#include <linux/time.h>
#include <linux/sched.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE2(nos, int, pid, int, nice)
{
	int old_nice = 0;
        int new_nice = 0;

	struct task_struct *p;
	printk(KERN_INFO "Called NOS system call\n");
	
	for_each_process(p) {
		if(p->pid==pid){
                        break;
                }
	}

	old_nice = p->static_prio - MAX_RT_PRIO - 20; //nice value of the process = static_prio  - MAX_RT_PRIO - 20
	printk(KERN_INFO "Old nice was:%d \n", old_nice);
	new_nice = old_nice + nice;
        if(new_nice >= -20 && new_nice <= 19){
                p->static_prio = new_nice + MAX_RT_PRIO + 20;
                set_tsk_need_resched(p);
	        return 0;
        } else {
                printk(KERN_INFO "New nice is not in limits \n");
                return 1;
        }

}