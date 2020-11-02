// Per-CPU state
struct cpu
{
    uchar apicid;              // Local APIC ID
    struct context *scheduler; // swtch() here to enter scheduler
    struct taskstate ts;       // Used by x86 to find stack for interrupt
    struct segdesc gdt[NSEGS]; // x86 global descriptor table
    volatile uint started;     // Has the CPU started?
    int ncli;                  // Depth of pushcli nesting.
    int intena;                // Were interrupts enabled before pushcli?
    struct proc *proc;         // The process running on this cpu or null
};

extern struct cpu cpus[NCPU];
extern int ncpu;

//PAGEBREAK: 17
// Saved registers for kernel context switches.
// Don't need to save all the segment registers (%cs, etc),
// because they are constant across kernel contexts.
// Don't need to save %eax, %ecx, %edx, because the
// x86 convention is that the caller has saved them.
// Contexts are stored at the bottom of the stack they
// describe; the stack pointer is the address of the context.
// The layout of the context matches the layout of the stack in swtch.S
// at the "Switch stacks" comment. Switch doesn't save eip explicitly,
// but it is on the stack and allocproc() manipulates it.
struct context
{
    uint edi;
    uint esi;
    uint ebx;
    uint ebp;
    uint eip;
};

enum procstate
{
    UNUSED,
    EMBRYO,
    SLEEPING,
    RUNNABLE,
    RUNNING,
    ZOMBIE
};

// Per-process state
struct proc
{
    uint sz;                    // Size of process memory (bytes)
    pde_t *pgdir;               // Page table
    char *kstack;               // Bottom of kernel stack for this process
    enum procstate state;       // Process state
    int pid;                    // Process ID
    struct proc *parent;        // Parent process
    struct trapframe *tf;       // Trap frame for current syscall
    struct context *context;    // swtch() here to run process
    void *chan;                 // If non-zero, sleeping on chan
    int killed;                 // If non-zero, have been killed
    struct file *ofile[NOFILE]; // Open files
    struct inode *cwd;          // Current directory
    char name[16];              // Process name (debugging)
    int ctime;                  // Creation time
    int etime;                  // end time
    int rtime;                  // total time
    int iotime;                 // ticks for whjch the process was sleeping
    int priority;               // priority of the process
    int timeslices;             // slices of time taken by this process
    int cticks;                 // ticks for the process in this queue
    int queue;                  // queue of the process
    int got_queue;              // has the process got queue
    int talloc;                 // time to store last queue allocation
    int ps_wtime;               // wtime for my_ps
    int n_run;                  // number of this process is picked by the scheduler
    int q_ticks[5];             // ticks taken in queue i
};

// Scheduling algorithms options

#define RR 0
#define FCFS 1
#define PBS 2
#define MLFQ 3

// Process memory is laid out contiguously, low addresses first:
//   text
//   original data and bss
//   fixed-size stack
//   expandable heap

// Struct for MLFQ scheduling nodes
struct proc_node
{
    struct proc *p;         // Pointer to process
    struct proc_node *next; // pointer to next node
    int use;                // Has this node been used 0 for no 1 for yes
};

// number of queues
#define NQUE 5

// Aging thresh
#define AGE_THERSH 25
struct proc_node store[NPROC];
struct proc_node *queues[NQUE];
