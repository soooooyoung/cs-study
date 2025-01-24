# Threads

A thread is an entity within a process that Windows schedules for execution.

## Key Components of a Thread

A thread includes following essential components:

- The contents of a set of CPU register registers representing the state of the processor
- Two stacks - one for the thread to use while executing in kernel mode and one for executing in user

### CPU registers

A set of volatile registers that hold the thread's state while executing. These registers store:

- The program counter (instruction pointer)
- General-purpose registers
- Flags and other execution-related informatoin

### Stacks

#### Kernel-mode stacks

Used when the thread executes privileged system code.

#### User-mode stacks

Used when the thread executes application code in user space.

### Thread-Local Storage (TLS)

A private storage area for each thread to store data accessible only within the thread's execution context. It is commonly used by runtime libraries, subsystems, and dynamically linked libraries (DLLs).

### Thread ID

A unique identifier for the thread within the system. Threads and processes share a common namespace, ensuring IDs never overlap. It is part of the **client ID**, which includes both the process ID and the thread ID.

### Security Context

Optional, but threads in multi-threaded server applications can have their own security tokens. It is used for impersonating clients, enabling the thread to act on behalf of a client.

## Thread Context

The volatile registers, stacks and private storage area are called thread's context. Because this information is different for each machine architecture that Windows runs on, this structure, by necessity, is architecture-specific. The Windows `GetThreadContext` function provides access to this architecture-specific information (called the `CONTEXT` block).

> [!NOTE]  
> Threads of a 32-bit application running on a 64-bit version of Windows will contain both 32-bit and 64-bit contexts, which Wow64(Windows on Windows) will use to switch the application from running in 32-bit to 64-bit mode when required. These threads will have two user stacks and two `CONTEXT` blocks, and the usual WIndows API functions will return the 64-bit context instead. The `Wow64GetThreadContext` function, however, will return the 32-bit context.

## Performance Scheduling

Thread scheduling involves the Windows kernel's scheduler, which prioritizes execution based on a priority model. However, `context switching` between threads incurs overhead due to:

- Saving and restoring thread contexts.
- Invoking the kernel scheduler.

To mitigate this cost, Windows supports **Fibers** and **User-Mode Scheduling (UMS)**.

### Fibers

Fibers allow an application to schedule its own threads of execution rather than rely on the priority-based scheduling mechanism built into Windows. Fibers are often called `lightweight threads`. In terms of scheduling, they're invisible to the kernel because they're implemented in user mode in `Kernel32.dll`. To use fibers, you first make a call to the Windows `ConvertThreadToFiber` function. This function converts the thread to a running fiber. Afterward, the newly converted fiber can create additional fibers via the `CreateFiber` function. (Each fiber can have its own set of fibers) Unlike a thread, however, a fiber doesn't begin execution until it's manually selected through a call to the `SwitchToFiber` function. The new fiber runs until it exits or until it calles `SwitchToFiber`, again selecting another fiber to run.

> [!NOTE]
> Using fibers is usually not a good idea. This is because they are invisible to the kernel. They also have issues such as sharing thread local storage (TLS) because several fibers can be running on the same thread. Although fiber local sotrage (FLS) exists, this does not solve all sharing issues, and I/O bound fibers will perform poorly regardless. Additionally, fibers cannot run concurrently on more than one processor, and are limited to cooperative multi-tasking only. In most scenarios it's best to let the Windows kernel handle scheduling by using the appropriate threads for the task at hand.

#### Summary

- Invisible to kernel, implemented entirely in `Kernel32.dll`
- Require explicit conversion of threads to fibers using `ConvertThreadToFiber` function
- Switching between fibers is manual through `SwitchToFiber` function

**Pros**:

- Greater control over scheduling
- Can be useful in meeting specific task sequencing requirements

**Cons**:

- Poor I/O performance
- Shared TLS
- Cooperative multitasking (cannot run concurrently on mulitple processors)

### User-Mode Scheduling (UMS)

User-Mode Scheduling (UMS) is a mechanism introduced to allow more efficient management of a thread scheduling. It is only available on 64-bit versions of Windows, and provide same basic advantages of fibers and less disadvantages. UMS threads have their own kernel thread state, and are therefore visible to the kernel, which allows multiple UMS threads to issue blocking system calls and share and contend on resources. When two or more UMS threads need to perform work in user mode, they can periodically switch execution contexts in user mode (by yielding from one thread to another) rather than involving the scheduler. From kernel's perspective, the same kernel thread is still running and nothing has changed. When a UMS thread performs an operation that requires entering the kernel (such as system call), it switches to its dedicated kernel-mode thread (called directed context switch). While **concurrent UMS threads still cannot run on multiple processors**, they do follow a pre-emptible model that's not solely cooperative.

Although threads have their own execution context, every thread within a proces sshares the process's virtual address space (in addtion to the rest of the resources belonging to the process), meaning that all the threads in a process have full read-write access to the process virtual address space. Threads cannot accidentally refernce the address space of another process, however, unless the other process makes available part of its private address space as a shared memory section (called a `file mapping object` in the Windows API) or unless one process has the right to open another process to use cross-process memory functions, such as `ReadProcessMemory` and `WriteProcessMemory` (which a process that's running with the same user account, and not inside of an AppContainer or other type of sandbox, can get by default unless the target process has certain protections).

> [!WARNING]  
> As of Windows 11, user-mode scheduling is not supported. All calls fail with the error `ERROR_NOT_SUPPORTED`. Applications requiring UMS must use earlier versions of Windows.
