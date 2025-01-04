# Services, functions and routines

The word `service` can refer to a callable routine in the OS, a device driver, or a server process. In this book following list describes the certain terms mean.

## Windows API Funtions

Window API functions are doumented, callable subroutines in the Windows API. They provide developers with a standardized way to interact with the Windows operating system. WIndows API functions form the primary interface for applications to perform system-level tasks, such as file handling, process creation, thread management, and GUI interactions.

Examples include:

- **CreateProcess**: Creates a new process and its primary thread.
- **CreateFile**: Opens or creates a file or I/O device. (e.g., pipes, mailslots, or physical disks)
- **GetMessage**: Retrieves messages from the application's message queue.

## Native System Services (System Calls)

Native system services are undocumented, underlying OS services in the OS callable from the user mode. These services serve the core of Windows operating system and are invoked by high-level Windows API functions. Unlike Windows API functions, they operate closer to the kernal, providing low-level functionality.

Examples include:

- **NtCreateUserProcess**: Used internally by `CreateProcess` to create a new process.
- **NtQuerySystemInformation**: Provides detailed system information (e.g., CPU usage, processes) not exposed directly by Windows API.

System calls are not officially doucmented or supported by Microsoft, making them more prone to changes across Windows versions.

## Kernal Support Functions (Kernal Routines)

Kernel support functions are callable only from the kernal mode and are used by kernel components, including device drivers. These routines provide kernel-level functionality, such as memory management, synchronization, and hardware communication.

Example of a kernal support function is `ExAllocatePoolWIthTag`, which allocates memory from kernal pools (Windows system heaps), a fundamental operation for kernel-mode drivers and subsystems.

## Windows Services

Windows services are long-running processes managed by the **Windows Service Control Manager (SCM)**. These services operate in the background, often without direct user interaction, to perform tasks such as scheduling, monitoring, or maintaining system functionality.

Examples include:

- **Task Scheduler Service**: Manages scheduled tasks and supports the `schtasks` command (similar to `cron` in UNIX).
- **Windows Update Service**: Ensures the operating system stays updated with the lastest patches and features.

ALthough device drivers are also registered as "services" in the Windows registry, they are distinct from these user-mode services and are not referred to as such in this context.

## Dynamic Link Libraries (DLLs)

DLLs are compiled binary files containing resuable subroutines that applications can dynamically load at runtime. DLLs are widely used in Windows to provide modularity, code sharing, and memory efficiency. They allow multiple applciates to share the same library code, reducing duplication and memory usage.

Examples include:

- **Msvcrt.dll**: The Microsoft C Runtime Library, which provides functions like string manipulation and memory allocation.
- **Kernel32.dll**: A core library of the Windows API that supports process and thread creation, memory management, and I/O operations.

The advantage DLLs provide over static libraries is that applications can share DLLs, and Windows ensures taht there is only one in-memory copy of DLL's code among the applications that are referencing it.

### .NET Assemblies as DLLs

In .NET, assemblies are compiled as DLLs, but instead of exporting unmanaged functions, they contain metadata and managed code. The Common Language Runtime (CLR) uses this metadata to access types and members in .NET DLLs.

### Memory Sharing in DLLs

#### Code Sharing

The code segment (the compiled executable instructions of a DLL) is shared among all process that load the same DLL. Windows loads a DLL into memory only once. When multiple process use the same DLL, they share the same in-memory code, reducing overall memory usage. This is possible because the code in DLL is typically read-only and reentrant, meaning it can safely be used by multiple processes simultaneously.

#### Private Data

Each process that loads the DLL gets its own private copy of the DLL's data segment (global and static variables). Modifications to global or static variables in one process do not affect other processes using the same DLL.

#### Shared Data

DLLs can be designed to explicitly share memory between processes. This can be achieved using:

- **Shared Memory Sections**: The `#pragma data_seg` directive in C/C++ allows developers to declare variables in a shared memory section. This enables multiple processes to access the same variables in the DLL.

```cpp
#pragma data_seg("SHARED")
int sharedVar = 0;
#pragma data_seg()
```

A shared memory section must be marked with proper attributes in the DLL's linker options.

- **Memory-Mapped Files**: DLLs can also use memory-mapped files to share memory between processes

#### Heap and Stack Memory

Each process has its own heap and stack. A DLL loaded by a process uses the process's heap and stack for dynamic allocations or local variables.

Memory allocated by a DLL within one process is not accessible to other processes unless explicitly shared using the inter-process communication (IPC) mechanisms like shared memory, pipes, or sockets.
