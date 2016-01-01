******************************************
*                                        *
*                                        *
*             Free ActiveX               *
*                                        *
*                                        *
******************************************

Help about Free ActiveX.

Created 14.01.2009


1. INTRIDUCTION

Free ActiveX is example of ActiveX element without using MFC and ATL based on Video LAN VLC ActiveX(http://www.videolan.org/) on Ñ++. License of Free ActiveX is GNU General Public License 2 version. See text of License in files:
/doc/gnu general public license v2.0 - gnu project - free software foundation (fsf).mht
/doc/gpl-2.0.txt
Or in internet:
http://www.gnu.org/licenses/old-licenses/gpl-2.0.html

Fragment of License:
			    NO WARRANTY

  11. BECAUSE THE PROGRAM IS LICENSED FREE OF CHARGE, THERE IS NO WARRANTY
FOR THE PROGRAM, TO THE EXTENT PERMITTED BY APPLICABLE LAW.  EXCEPT WHEN
OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR OTHER PARTIES
PROVIDE THE PROGRAM "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED
OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE ENTIRE RISK AS
TO THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU.  SHOULD THE
PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY SERVICING,
REPAIR OR CORRECTION.

  12. IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING
WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MAY MODIFY AND/OR
REDISTRIBUTE THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES,
INCLUDING ANY GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING
OUT OF THE USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED
TO LOSS OF DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY
YOU OR THIRD PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER
PROGRAMS), EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE
POSSIBILITY OF SUCH DAMAGES.
                                                                                                   
MFC/ATL need only for compile project in Debug/Release configuration. MFC/ATL is used only in resource file for easy creating window and demonstration interaction ActiveX and application. But you may use CreateWindow for create window. Configuration Debug without mfc/Release without mfc not need MFC/ATL, but demonstration interaction does not work.

2. RUN AND TEST

Compilation:

1. Run file Visual Studio 2005 /FreeActiveX/freeactivex.sln. It is C++ project.
2. In Release files will be created:
/bin/freeactivex.dll - ActiveX component.
/test/freeactivex.cab /bin/freeactivex.cab - ActiveX in cab file.
3. In Debug mode files will be created:
/FreeActiveX/debug/freeactivex.dll - ActiveX component, it will be register.
4. In Debug without mfc mode files will be created:
/FreeActiveX/debug without mfc/freeactivex.dll - ActiveX component, it will be register.
5. In Release without mfc mode will be created:
/bin/freeactivex.dll - ActiveX component.
/test/freeactivex.cab /bin/freeactivex.cab - ActiveX cab file.

Registration:
1. In Debug file be registration immediately.
2. In Release need type command:
regsvr32 FreeActiveX.dll

Test:
1. Using ActiveX Control Test Container. 

   à) Press button New Control.

   á) Select form list ActiveX Example with out ATL and MFC v2.

2. Run files /test/htmltest.html in Internet Explorer.

   à) In setting Internet Explorer need allow run ActiveX, run no certified ActiveX, allow JavaScript and setup no certified ActiveX. 
* We recommend recover back your setting.

   á) If ActiveX component was not installed. You can install it through Internet Explorer.
      i) Copy dir test in www dir of web-server.
      ii) Run file htmltest.html through web-server (for Example http://localhost/htmltest.html)
      iii) If ActiveX was not installed,Internet Explorer can offer install it. Internet Explorer install ActiveX from freeactivex.cab.

3. ABOUT CODE:


!---- Attention ----!
MFC/ATL need only for compile project in Debug/Release configuration. MFC/ATL is used only in resource file for easy creating window and demonstration interaction ActiveX and application. But you may use CreateWindow for create window. Configuration Debug without mfc/Release without mfc not need MFC/ATL, but demonstration interaction does not work.

Directory:
/bin - include binary files.
/doc - include documentation. 
/FreeActiveX - include ActiveX project.
/FreeActiveX/FreeActiveX/src/ - include soures of ActiveX.
/FreeActiveX/FreeActiveX/src/helpers - supportive class implement COM interfaces.
/FreeActiveX/FreeActiveX/src/misc - include files of settings and utils.
/FreeActiveX/FreeActiveX/src/plug-in - include common files of plug-in and control.
/FreeActiveX/FreeActiveX/src/resource - resource files.
/test/ - files for test.


Files:
Here list of common files:
/bin/
FreeActiveX.cab - pack ActiveX component for incstall through Internet Explorer.
FreeActiveX.dll - librarie with ActiveX component.
FreeActiveX.inf - file of information for FreeActiveX.cab.
makecab.bat     - file for creating FreeActiveX.cab.
/FreeActiveX/FreeActiveX/src/
activex.def   - list if export fucntions.
main.cpp      - entry point and export fucntions for registration.
/FreeActiveX/FreeActiveX/src/plug-in/
plugin.cpp      - class plug-in implement. It is loaded by application for using.
plugin.h        - class plug-in header.
vlccontrol2.cpp - class control implement. It is used parent application for control ActiveX component.
vlccontrol2.h   - class control header.
/FreeActiveX/FreeActiveX/src/resource/
axexample.idl    - file which include interface of ActiveX component: interfaces of plugin.h, vlccontrol2.h. Parent applaction use it files know functions of ActiveX.
axexample.tlb    - file is generate from axexample.idl.
axexample_h.h    - file is generate from axexample.idl.
axexample_i.c    - file is generate from axexample.idl.
axexample_rc.rc  - file is generate from axexample.idl.

!---- Attention ----!
It is not full example of ActiveX. You can study ActiveX of VLC. 

                  
4. Links:
http://www.codeproject.com/KB/cpp/ActiveXControlWithoutMFC.aspx - How use ActiveX.
http://en.wikipedia.org/wiki/ActiveX - What is ActiveX.
http://msdn.microsoft.com/en-us/library/aa751972(VS.85).aspx - intriduction about ActiveX from Microsoft site.
http://www.videolan.org/ - site of VLC player.
http://www.videolan.org/vlc/download-sources.html - here is source of VLC player.
