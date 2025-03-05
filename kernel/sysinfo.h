#ifndef _SYSINFO_H_
#define _SYSINFO_H_

struct sysinfo {
  uint64 freemem;    // amount of free memory (in bytes)
  uint64 nproc;      // number of processes whose state is not UNUSED
  uint64 nopenfiles; // number of open files across the system
};

#endif