#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/sysinfo.h"

int
main(int argc, char *argv[])
{
  struct sysinfo info;
  
  if (sysinfo(&info) < 0) {
    printf("FAIL: sysinfo system call failed\n");
    exit(1);
  }
  
  printf("Free memory: %lu bytes\n", info.freemem);
  
  printf("Number of processes: %lu\n", info.nproc);
  printf("Number of open files: %lu\n", info.nopenfiles);
  
  printf("sysinfotest: OK\n");
  exit(0);
}