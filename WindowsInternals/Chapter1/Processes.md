# Processes

While programs and processes may seem alike at a first glance, they serve fundamentally different purposes.

- A **program** is a static sequence of instructions
- A **process** is a container for a set of resources used when executing the instance of the program. At the highest level of abstraction, a Windows process comprises the following:
  - **A private virtual address space**: Set of virtual memory addresses that the process can use.
  - **An executable program**: Initial code and data. It is mapped into the process's virtual address space
  - **A list of open handles**: Mappings to various system resources such as semaphores, synchronization objects, and files that are accessible to all threads in the process.
  - **A security context**: Access token that indentifies the user, security groups, privilesges, attributes, claims, capabilities, User Account Control (UAC) virtualization state, session, and limited user account state associated with the process, as well as the AppContainer identifier and its related sandboxing information.
  - **A process ID**: Unique identifier internally part of an identifier called a client ID.
  - **At least one thread of execution**: While it is possible to create a process without threads, such processes are typically not useful. (empty process) A process must have at least one active thread to perform tasks.

## Tools for Viewing and Modifying Process Information

### Task Manager

Windows provides various tools to view and manage process information many of which come with overlapping functionalities but use different terminology. Among the most widely used is **Task Manager**, a utility for examining process activity. Despite its name, there is no "task" concept in the Windows kernel.

Upon opening Task Manager, four columns are shown by default:

- **CPU**: Displays the percentage of CPU usage by each process.
- **Memory**: Shows the amount of memory consumed by the process.
- **Disk**: Indicates disk activity associated with the process.
- **Network**: Reflects the process's network activiy.

The Details Tab shows the processes with diverse information columns. Unlike some objects in Windows, processes can't be given global names. To display additional details, you can customize the view by clicking header row and `Select Columns`.

#### Key in the Details Tab

##### Threads

Displays the number of threads associated with each process.

- A process must have at least one thread to perform tasks.
- If a process shows 0 threads, it often indicates an issue that's preventing the process from being deleted.

##### Handles

Indicates the number of kernel object handles opened by the threads within the process.

- Handles are essential for accessing system resources like files, semaphores, and synchronization objects.

##### Status

Displays the current state of the process. Common states include:

- **Running**: For non-UI processes, this typically means threads are active or waiting for an event. For UI-based processes, it means the user interface is responsive.

- **Suspended**: Occurs when all threads in the process are suspended.

  - This can be triggered programmatically (e.g., using tools like Process Explorer)
  - For Windows Runtime apps, this status happens automatically when the app is minimized, helping conserve resources, especially on battery-powered devices.

- **Not Responding**: Indicates that a UI-based process has not checked its message queue for at least 5 seconds, causing the user interface to freeze.
  - This can occur during CPU-intesive tasks or prolonged I/O operations.

##### Parent Process

Each process references a prent or creator process. However, if the parent process no longer exists, the reference is not updated. Tools like **Process Explorer** avoid linking child processes to incorrect parents by considering the parent process's start time.

### Viewing the Process Tree

The process tree shows the hierarchical relationship between processes, including parent-child associations. Most tools do not display this information directly, but it can be retrieved using tools like **Performance Monitor**, **Tlist.exe**, or **Process Explorer**.
