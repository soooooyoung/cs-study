# Kernel Mode vs. User Mode in Windows

To ensure the OS remains stable and secure, Windows divides processor access into two primary modes: **user mode** and **kernel mode**. This separation prevents user applications from directly accessing or modifying critical OS data, providing a robust foundation for system security.

User application runs in user mode, whereas OS code (such as system services and devices drivers) runs in kernel mode.

## User Mode

Applications operating in user mode have restricted access to memory and syhstem resources. If a user application misbehaves, it cannot interfere with other applications or the OS itself.

## Kernel Mode

Kernel mode refers to a mode of execution in a processor that grants access to all system memory and all CPU instructions.

## Privilege Levels

Some processors differentiate between such modes by using the term `code privilege level` or `ring level`, while others use terms such as `supervisor mode` and `application mode`. Regardless of what it's called, by providing the operating system kernel with a higher privilege level than user mode applications have, the processor provides a necessary foundation for OS designers to ensure that a misbehaving application can't disrupt the stability of the system as a whole.

## Memory Access

Every Windows process has its own private memory space. Kernnel-mode code and device drivers share a signle virtual address space for all processes.

- Pages in `system space` (used by the kernel) are accessible only in kernel mode.
- Pages in `user space` are accesible in both user mode and kernel mode.

### Read-Only Pages

Read-only pages are protected from being overwritten in both modes. On processors that support no-execute memory protection, Windows mark pages containing data as non-executable, and **Data Execution Prevention (DEP)** prevents code execution.

### R/W Access In Kernel Mode

Windows doesn't provide any protection for private read/write system memory being used by components running in kernel mode. In other words, once in kernel mode, OS and device-driver code has complete access to system-space memory and can bypass Windows security to access objects. Because the bulk of the Windows OS Code runs in kernel mode, it is vital that components that run in kernel mode be carefully designed and tested to ensure they don't violate system security or cuase system instability.

This lack of protection also emphasizes the need to remain vigilant when loading a third-party device driver, especially if it's unsigned, because once in kernel mode, the driver has complete access to all OS data.

> [!NOTE]  
> This risk was one of the reasons behind the driver-signing mechanism introduced in Windows 2000, which warns (and, if configured as such, blocks) the user if an attempt is made to add an unsigned plug-and-play driver, but does not affect other types of drivers. Also, a mechanism called `Driver Verifer` helps device-driver writers find bugs, such as buffer overruns or memory leaks, that can cause security or reliability issues.

#### Driver Signing Policies

Windows uses **driver signing** to ensure device drivers are tested and verified.

On 64-bit Windows and ARM systems, unsigned drivers cannot be installed unless in **Test Mode**, which disables certain DRM features and displays a watermark.

**Windows 10**

- Drivers must be signed with a **SHA-2 Extended Validation (EV) Hardware Ceritificate**. These drivers are submitted to Microsoft for `attestation signing`, ensuring they meet security standards.

**Windows Server 2016**

- Drivers require **Windows Hardware Qulaity Labs (WHQL)** ceritifcation. WHQL ensures compatibility, security, and performance, further reducing the risks of unstable drivers.

## Transition Between Modes

### System Calls

When user applciations call OS services (e.g., `ReadFile`), the processor switches from **user mode** to **kernel mode**.

This transition is triggered by a special processor instruction, enabling the OS to perform privileged operations securely.

### Process

1. The processor enters **system service dispatching code** in the kernel.

2. It calls the appropriate internal function in kernel components like `Ntoskrnl.exe` or `Win32k.sys`
3. After completing the task, the processor switches back to **user mode** and returns control to the user application.

> [!NOTE]
> Mode transition do not directly affect thread scheduling- it only changes the privilege lelvel of the executing code.Thus it is **not a context switch**.
