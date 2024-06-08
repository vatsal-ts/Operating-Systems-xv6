#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
// #include "proc.c"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

//
int
sys_thread_create(void) {
  int fcn;
  char* arg;
  char* stack;
  if (argint(0, &fcn) < 0)
    return -1;
  if (argstr(1, &arg) < 0)
    return -1;
  if (argstr(2, &stack) < 0)
    return -1;
  // fcn make integer to void(*)(void*)
  return thread_create((void(*)(void*))fcn, arg, stack);
}
int
sys_thread_exit(void)
{
  thread_exit();
  return 0;
}
int
sys_thread_join(void)
{
  return thread_join();
}

int
sys_draw(void)
{
  void* buf;
  uint size;
  argptr(0, (void*)&buf, sizeof(buf));
  argptr(1, (void*)&size, sizeof(size));

  char text[] = R"(
    Everyone Loves Mickey Mouse!
                   >?>?>
)";
  if(sizeof(text)>size)
    return -1;

  strncpy((char *)buf, text, size);
  return sizeof(text);
}

// int
// sys_thread_create(void) {
//   int fcn;
//   char* arg;
//   char* stack;
//   if (argint(0, &fcn) < 0)
//     return -1;
//   if (argstr(1, &arg) < 0)
//     return -1;
//   if (argstr(2, &stack) < 0)
//     return -1;
//   // fcn make integer to void(*)(void*)
//   return thread_create((void(*)(void*))fcn, arg, stack);
// }
// int
// sys_thread_exit(void)
// {
//   thread_exit();
//   return 0;
// }
// int
// sys_thread_join(void)
// {
//   return thread_join();
// }
