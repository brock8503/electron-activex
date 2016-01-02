Test tool
Download tstcon32 to test ActiveX http://www.microsoft.com/en-us/download/confirmation.aspx?id=16351
To build it you'll need http://www.microsoft.com/en-us/download/confirmation.aspx?id=40770 installed in vs2013
Update WINVER to #define WINVER 0x0501		// Change this to 0x0500 to target Windows 98 and Windows 2000.
Then project properties -> configurations properties -> C/C++ -> treats warning as error -> No (/WX-)

http://blogs.msdn.com/b/rextang/archive/2008/08/04/8830769.aspx
Configuration Properties -> Expand the Linker node -> Manifest File property page -> Enable User Account Control (UAC), UAC Execution Level, and UAC Bypass UI Protection properties.
Set MANIFEST /NO
set /MD flag

OLEView
https://msdn.microsoft.com/en-us/library/d0kh9f4c.aspx
 "C:\Program Files (x86)\Windows Kits\8.0\bin\x86\oleview.exe"

#Register the control with the OS
Use Regsvr32 https://technet.microsoft.com/en-us/library/bb490985.aspx
* Register dll
$ regsvr32.exe ActiveX.dl
* UnRegister dll
$ regsvr32.exe /u ActiveX.dll

#Tests control
Verify registration with OLEView
orTest view with tstcon32

#Build
Only *debug* is building currently

#Debug
Using win32 `DebugBreak();` during post build you can break into the `DllRegisterServer`  