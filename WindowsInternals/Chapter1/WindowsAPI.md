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
