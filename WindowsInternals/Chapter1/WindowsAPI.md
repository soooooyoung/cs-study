# Windows API

The `Windows Application Programming Interface` (API) is the user-mode system programming interface to the Windows OS family. Prior to the introduction of 64-bit versions of Windows, the programming interface to the 32-bit versions of the Windows OS was called the `Win32 API` to distinguish it from the original 16-bit Windows API.

## Windows API Flavors

The Windows API originally consisted of C-style functions only. C was the natural choice because it was lowest common denominator at the time of the inception of Windows. Today, thousands of functions exist for developers to use, and such many functions resulted in lack of naming consistency and logical groupings. Because of this, some newer APIs use different API mechanism known as the `Component Object Model(COM)`.

### Component Object Model (COM)

COM was originally created to enable Mircosoft Office applications to communicate and exchange data between documents (such as embedding an Excel chart inside a Word document or a PowerPoint presentation.) This ability is called Object Linking and Embedding (OLE). OLE was originally implemented using an old Windows messaging mechaanism called Dynamic Data Exchange (DDE), DDE was inherently limited, which is why new way of communication (COM) was developed.

COM is based on two foundational principles.

- Clients communicate with objects (**\*COM server objects**) through interfaces.

  - COM interfaces: —well-defined contracts with a set of logically related methods grouped under the virtual table dispatch mechanism.
  - This is also a common way for C++ compilers to implement virtual functions dispatch. This results in binary compatibility and removal of compiler name mangling issues. Consequently, it is possible to call these methods from many languages.

- Component implementation is loaded dynamically, rather than being statically linked to the client.

> **\*COM server objects**: a Dynamic Link Library (DLL) or an executable (EXE), where the COM classes are implemented.

> [!NOTE]  
> Examples of APIs accessed through COM include DirectShow, Windows Media Foundation, DirectX, DirectComposition, Windows Imaging Component (WIC), and the Background Intelligent Transfer Service (BITS).

## The Windows Runtime

Windows 8 introduced a new API and supporting runtime called the Windows Runtime.

From an API perspective, WinRT is built on top of COM, adding various extensions to the base COM infrastructure. It’s much more cohesive than classic Windows API functions, with namespace hierarchies,

> [!WARNING]  
> Windows Runtime is sometimes abbreviated WinRT, not to be confused with Windows RT, the discontinued ARM-based Windows OS version

The Windows Runtime consists of platform services aimed particularly at app developers for
the `Windows Apps`. Windows Apps are subject to new rules, unlike the Windows desktop applications.

Desktop apps can use a subset of the WinRT APIs. Conversely, Windows Apps can use a subset of Win32 and COM APIs. Conversely, Windows Apps can use a subset of Win32 and COM APIs. At the basic binary level, the WinRT API is still based on top of the legacy Windows binaries and APIs, even though the availability of certain APIs may not be documented or
supported.

## The .NET Framework

The .NET Framework is a software development platform created by Microsoft, designed to provide a consistent programming environment for applications running on the Windows operating system. It is part of Windows.

Following table shows the .NET Framework version installed by default.

| Windows Version         | .NET Framework Version |
| ----------------------- | ---------------------- |
| Windows 8               | 4.5                    |
| Windows 8.1             | 4.5.1                  |
| Windows 10              | 4.6                    |
| Windows 10 version 1511 | 4.6.1                  |
| Windows 10 version 1607 | 4.6.2                  |
| Windows 11              | 4.8                    |

Later versions can be installed on older OS versions manually.

The .NET Framework consists of two major components

### The Common Language Runtime (CLR)

This is the run-time engine for .NET and includes a **Just In Time** (JIT) compiler that translates **Common Intermediate Language** (CIL) instructions to the underlying hardware CPU machine language, a garbage collector, type verification, code access security, and more. It's implemented as a COM in-process server (DLL) and uses various facilities provided by the Windows API.

- **Just In Time (JIT) Compilation**: Allows applications to be hardware-independent while leveraging the full performance of the hardware at runtime.
- **Garbage Collection (GC)**: Automatically manages memory allocation and deallocation, ensuring efficient memory use and reducing issues like memory leaks.
- **Interoperability with COM**: The CLR works as a COM in-process server (DLL), allowing it to use existing COM components and integrate with native Windows applications.

### The .NET Framwork Class Library (FCL)

This is a large collection of types that implement functionality typically needed by client and server applications, such as user interface services, networking, database access, and more.

- **User Interface Development**: Classes for building Windows Forms, WPF (Windows Presentation Foundation), and web applications.
- **Networking and Communication**: APIs for network programming, web services, and protocols like HTTP, TCP, and FTP.
- **Data Access**: Libraries for database interaction, including ADO.NET for relational databases and LINQ for querying data structures.
