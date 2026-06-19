# Windows CE Build Tools

A drop-in cross-development bundle for Windows CE 3.0 through Windows CE 7.0.
Builds CE PE binaries for ARM, MIPS, and SH targets on a modern Windows host
without installing eMbedded Visual C++, Platform Builder, or Visual Studio.

## Layout

```
.
├── bin/I386/                    host x86 build tools
│   ├── ARM/                     cl.exe armasm.exe c1.dll c1xx.dll c2.dll
│   ├── MIPS/  SH/               cl.exe for the other ISAs
│   ├── link.exe lib.exe         universal linker / librarian
│   └── rc.exe nmake.exe dumpbin.exe editbin.exe ...
│
├── ce3-ppc2k/                   Pocket PC 2000 SDK             (CE 3.0)
├── ce3-hpc2k/                   H/PC 2000 SDK                  (CE 3.0)
├── ce42-standard/               Standard CE .NET 4.2 SDK       (CE 4.2)
├── ce42-smartphone/             Smartphone 2003 SDK            (CE 4.2)
├── ce5-standard/                Standard SDK for Windows CE 5  (CE 5.0)
│
├── ce3-oak/  ce3-ddk/           Driver-mode headers (CE 3.0)
├── ce5-oak/  ce5-ddk/           Driver-mode headers (CE 5.0)
├── ce6-oak/  ce6-ddk/           Driver-mode headers (CE 6.0)
└── ce7-oak/  ce7-ddk/           Driver-mode headers (CE 7.0)
```

## Quick start — build an ARM CE 5 app

```powershell
//Set SDK path

set SDK=C:\PATH\TO\\WindowsCE-Build-Tools


set PATH=%SDK%\bin\I386\ARM;%SDK%\bin\I386;%PATH%

//compile main.cpp, rename or add extra file at the end if more files


"%SDK%\bin\I386\ARM\cl.exe" /nologo /c /W3 /O2 /DUNICODE /D_UNICODE /DUNDER_CE /DARM /D_ARM_ /I "%SDK%\ce5-standard\Include\Armv4i" main.cpp

//link main.cpp, like with compiling rename or add another obj file like start.obj

"%SDK%\bin\I386\link.exe" /nologo /subsystem:windowsce,5.00 /entry:WinMain /machine:THUMB /nodefaultlib /libpath:"%SDK%\ce5-standard\Lib\ARMV4I" /out:result.exe main.obj coredll.lib commctrl.lib commdlg.lib

```

The resulting `result.exe` is a Windows CE PE that runs on any ARM-based CE 5.0 /
Windows Mobile 5 device — Pocket PC, Smartphone, Handheld PC, or industrial
hardware. The same binary also runs on CE 6.0 and CE 7.0 because CE coredll
only ever added exports, never removed them.

## Building for other CE versions

The same `cl.exe` cross-compiles for every CE version — only the include / lib
paths and the PE subsystem stamp change:

| Target CE          | Include path                       | Lib path                              | Subsystem        |
|--------------------|------------------------------------|---------------------------------------|------------------|
| CE 3.0 (PPC2K)     | `ce3-ppc2k\include`                | `ce3-ppc2k\lib\arm\<soc>\CE\RETAIL`   | `windowsce,3.00` |
| CE 3.0 (H/PC)      | `ce3-hpc2k\include`                | `ce3-hpc2k\lib\arm\<soc>\CE\RETAIL`   | `windowsce,3.00` |
| CE 4.2 (Standard)  | `ce42-standard\Include\Armv4i`     | `ce42-standard\Lib\Armv4i`            | `windowsce,4.20` |
| CE 4.2 (Smartphone)| `ce42-smartphone\Include\Armv4i`   | `ce42-smartphone\Lib\Armv4`           | `windowsce,4.20` |
| CE 5.0 / 5.2       | `ce5-standard\Include\Armv4i`      | `ce5-standard\Lib\ARMV4I`             | `windowsce,5.00` |
| CE 6.0 / 7.0       | `ce5-standard\Include\Armv4i`      | `ce5-standard\Lib\ARMV4I`             | `windowsce,5.00` |

For CE 6 / CE 7 targets the CE 5 SDK include / lib paths work — coredll's
export set is forward-compatible. Stamp a higher `/subsystem:windowsce,6.00`
or `,7.00` if you want loader rejection on older devices.

## Driver development

For driver builds add the matching CE-version OAK and DDK include paths
alongside the SDK include path:

```powershell
& cl.exe /c /W3 /O2 /DUNICODE /D_UNICODE /DUNDER_CE /DARM /D_ARM_ `
    /I "$SDK\ce5-standard\Include\Armv4i" `
    /I "$SDK\ce5-oak\INC" `
    /I "$SDK\ce5-ddk\INC" `
    driver.c
```

## Other architectures

For MIPS / SH targets the matching `bin\I386\<arch>\cl.exe` and the per-SDK
`Include\<arch>\` / `Lib\<arch>\` subdirs follow the same pattern. The shared
`link.exe` accepts all CE machine types — run `link.exe /?` for the full
`/machine:` token list.

## Sources

Contents are a verbatim merge of Microsoft installs:

- `bin/` — `SDK\BIN\` from Windows CE 5.0 Platform Builder
- `ce3-ppc2k/` — Microsoft Pocket PC 2000 SDK
- `ce3-hpc2k/` — Microsoft Handheld PC 2000 SDK
- `ce42-standard/` — Standard SDK for Windows CE .NET 4.2
- `ce42-smartphone/` — Smartphone 2003 SDK
- `ce5-standard/` — Standard SDK for Windows CE 5.0
- `ce3-oak/`, `ce3-ddk/` — header subtrees from Windows CE 3.0 Platform Builder
- `ce5-oak/`, `ce5-ddk/` — header subtrees from Windows CE 5.0 Platform Builder
- `ce6-oak/`, `ce6-ddk/` — header subtrees from Windows CE 6.0 Platform Builder
- `ce7-oak/`, `ce7-ddk/` — header subtrees from Windows CE 7.0 Platform Builder

## License

All binaries, headers, and libraries in this repository are Microsoft's
intellectual property, redistributed verbatim. The Microsoft EULAs preserved
inside each `ce*-*` subdirectory govern use and redistribution. No additional
license is granted by this repository beyond what Microsoft's EULAs permit.



