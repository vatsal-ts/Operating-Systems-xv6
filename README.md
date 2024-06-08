# xv6-Implementations

## Assignment 1 Kernel Threads and Synchronization
Implemented kernel threads and then built spin locks and mutexes to synchronize access among them. 
Implemented interface of POSIX threads 
Defined 3 key system calls:
1. `thread_create()`: Creates a kernel thread.
2. `thread_join()`: Waits for the thread to finish.
3. `thread_exit()`: Allows the thread to exit.
Implemented POSIX-like synchronization primitives: spinlocks and mutexes. To test your implementation, a provided simple program was used.

## Assignment 2 Hybrid Scheduler (System Calls and Scheduling)
Enhanced xv6 by adding new system calls and modifying the scheduler.

### Part A: New System Calls
1. **Process Information System Calls**:
   - `getNumProc()`: Returns the total number of active processes.
   - `getMaxPid()`: Returns the maximum PID among all active processes.
   - `getProcInfo(pid, &processInfo)`: Takes a PID and a pointer to a `processInfo` structure, returning information like parent PID, context switch count, and process size.

2. **Process Burst Time System Calls**:
   - `set_burst_time(n)`: Sets the process's burst time.
   - `get_burst_time()`: Retrieves the process's burst time.

### Part B: Scheduler Modification
Modified the xv6 scheduler to implement a shortest job first (SJF) scheduling algorithm based on user-defined process burst times.

### Implementation Notes
- **Locking Discipline**: Ensured proper locking when accessing the process table to avoid subtle bugs.
- **Scheduler Design**: Described design and implementation details, including run-time complexity.
- **Test Cases**: Created test programs to compare the new scheduler against the default round robin scheduler, demonstrating different execution behaviors for CPU-bound and I/O-bound processes.

### Testing
Developed a user-space test program, `test_scheduler`, which forks multiple processes, sets different burst times, and showcases the impact on execution behavior compared to the default scheduler.


## Assignment 3 Memory Management (Lazy Memory Allocation and Paging Mechanism)

### Part A: Lazy Memory Allocation
Modern operating systems often use lazy allocation for heap memory, unlike the default behavior in xv6. The goal of this part was to implement lazy allocation in xv6.

#### Steps:
1. **Eliminate Allocation in `sbrk()`**:
   - Modified `sbrk(n)` in `sysproc.c` to only increase the process size by `n` without allocating physical memory.
   - The process is tricked into believing it has the requested memory by updating `proc->sz`.

2. **Implement Lazy Allocation**:
   - Modified `trap.c` to handle page faults by mapping newly-allocated physical memory at the faulting address and then returning to user space.
   - Allocated a new memory page, added suitable page table entries, and returned from the trap to allow the process to continue executing.

This change was validated by running simple commands like `echo hi` in the shell and ensuring they executed without page faults.

### Part B: Paging Mechanism
Implemented a paging mechanism to allow xv6 to swap out pages to a backing store when physical memory is exhausted.

#### Tasks:
1. **Kernel Processes**:
   - Created kernel processes to handle swapping tasks using the function `void create_kernel_process(const char* name, void (*entrypoint)())`.

2. **Swapping Out Mechanism**:
   - When memory allocation failed, the process was suspended, and a request was submitted to the kernel swapping out process.
   - The swapping out process saved the content of the least recently used page to disk, marked it as free, and then resumed the suspended process.

3. **Swapping In Mechanism**:
   - On detecting a page fault due to a swapped out page, the process was suspended, and a request was sent to the kernel swapping in process.
   - The swapping in process allocated a new physical page, filled it with the swapped-out content, mapped it to the virtual address, and resumed the process.

4. **Sanity Test**:
   - Developed a user-space program `memtest` to fork 20 child processes, each allocating memory, filling it with values, and validating the content. This tested the paging mechanism effectively.

This implementation ensured proper memory management even under constrained physical memory, enabling xv6 to handle more processes efficiently through swapping.

## Assignment 4 Quantitative Comparison of Filesystems

### Summary

This assignment focused on understanding and evaluating the benefits of modern filesystem features through quantitative comparison.

### Steps:

1. **Chosen Filesystems and Feature**:
   - Selected two filesystems differing in a specific feature: ZFS with data deduplication and ext4, which lacks this feature.
   - Researched the chosen filesystems and the data deduplication feature to understand their implementation. Documented the feature, the selected filesystems, and a brief description of the feature implementation based on filesystem code and documentation.
   - Installed the selected filesystems on test machines to run experiments.

2. **Quantified Benefits**:
   - Set up a workload using the provided tool, `vdbench`, to showcase the selected feature.
   - Ran experiments on both filesystems using the same workload.
   - Measured and compared metrics between the two sets of experiments.
   - Detailed the experiments, metrics, and observations in the report.

   **Sample Ideas for Quantifying Benefits**:
   - **Data Deduplication**: Wrote similar files to disk and measured disk space usage with and without deduplication.
   - **Large File Optimization**: Observed throughput for creating and managing large files.
   - **Compression**: Measured disk space usage with filesystems that support compression.
   - **Copy-on-Write**: Measured the time taken for copying files or making snapshots.
   - **Metadata Management**: Measured read/write speeds for filesystems with optimized metadata structures.

3. **Disadvantages Observed**:
   - Identified and documented any observed disadvantages of the feature.
   - Noted that while data deduplication led to lower disk usage, it resulted in higher CPU consumption.

### Workload Creation Tool
Used the provided tool, `vdbench`, for creating workloads to test the filesystems. The tool supported both raw I/O and file-system testing. Utilized the file-system testing mode. The `vdbench` directory contained a manual for understanding and using the tool. Ensured `jre` was installed on systems to use this tool.

### Implementation and Testing
- Installed and configured the chosen filesystems.
- Designed and executed experiments using `vdbench`.
- Collected and analyzed data to compare performance metrics.
- Documented the entire process, from filesystem selection to experimental results and analysis, including any encountered disadvantages.

This assignment provided a comprehensive understanding of modern filesystem features and their practical implications through hands-on experimentation and quantitative analysis.