#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "sysinfo.h"
#include "sleeplock.h"
#include "fs.h"
#include "file.h"


uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if(n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}


int sys_hello(void) {
  printf("Hello, world!\n");
  return 0;
}
extern uint64 free_memory(void);
extern uint64 count_proc(void);
extern uint64 count_openfiles(void);

uint64
sys_sysinfo(void)
{
  struct sysinfo info;
  uint64 addr;
  struct proc *p = myproc();
  
  // Fix the argaddr usage
  argaddr(0, &addr);
  
  info.freemem = free_memory();
  info.nproc = count_proc();
  info.nopenfiles = count_openfiles();
  
  if(copyout(p->pagetable, addr, (char *)&info, sizeof(info)) < 0)
    return -1;
  


int sys_hello(void) { 
  printf("Hello, world!\n"); 
  return 0; 
} 

uint64 sys_trace(void) {
  int mask;
  argint(0, &mask);
  if(mask < 0) 
    return -1;
  struct proc *p = myproc();
  p->trace_mask = mask;  // Lưu mask vào tiến trình hiện tại
  return 0;
}