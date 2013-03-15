# Microsoft Developer Studio Project File - Name="UltraWhorld" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=UltraWhorld - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "UltraWhorld.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "UltraWhorld.mak" CFG="UltraWhorld - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "UltraWhorld - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "UltraWhorld - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "UltraWhorld - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 shlwapi.lib /nologo /subsystem:windows /dll /machine:I386
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy Release\UltraWhorld.dll C:\temp\OpenTZTHiResBeta0_11Full\OpenTZT\Effector\Bank0\F6
# End Special Build Tool

!ELSEIF  "$(CFG)" == "UltraWhorld - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 shlwapi.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "UltraWhorld - Win32 Release"
# Name "UltraWhorld - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BackBufGDI.cpp
# End Source File
# Begin Source File

SOURCE=.\BackBufGDI.h
# End Source File
# Begin Source File

SOURCE=.\Benchmark.cpp
# End Source File
# Begin Source File

SOURCE=.\Benchmark.h
# End Source File
# Begin Source File

SOURCE=.\DPoint.cpp
# End Source File
# Begin Source File

SOURCE=.\DPoint.h
# End Source File
# Begin Source File

SOURCE=.\FFParmDef.h
# End Source File
# Begin Source File

SOURCE=.\FormatIO.cpp
# End Source File
# Begin Source File

SOURCE=.\FormatIO.h
# End Source File
# Begin Source File

SOURCE=.\FreeFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\FreeFrame.h
# End Source File
# Begin Source File

SOURCE=.\hls.cpp
# End Source File
# Begin Source File

SOURCE=.\hls.h
# End Source File
# Begin Source File

SOURCE=.\MainDef.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MasterDef.h
# End Source File
# Begin Source File

SOURCE=.\NormVal.cpp
# End Source File
# Begin Source File

SOURCE=.\NormVal.h
# End Source File
# Begin Source File

SOURCE=.\Oscillator.cpp
# End Source File
# Begin Source File

SOURCE=.\Oscillator.h
# End Source File
# Begin Source File

SOURCE=.\ParmDef.h
# End Source File
# Begin Source File

SOURCE=.\ParmInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\ParmInfo.h
# End Source File
# Begin Source File

SOURCE=.\Patch.cpp
# End Source File
# Begin Source File

SOURCE=.\Patch.h
# End Source File
# Begin Source File

SOURCE=.\PatchLink.cpp
# End Source File
# Begin Source File

SOURCE=.\PatchLink.h
# End Source File
# Begin Source File

SOURCE=.\PathStr.cpp
# End Source File
# Begin Source File

SOURCE=.\PathStr.h
# End Source File
# Begin Source File

SOURCE=.\Playlist.cpp
# End Source File
# Begin Source File

SOURCE=.\Playlist.h
# End Source File
# Begin Source File

SOURCE=.\RealTimer.cpp
# End Source File
# Begin Source File

SOURCE=.\RealTimer.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SortStringArray.cpp
# End Source File
# Begin Source File

SOURCE=.\SortStringArray.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\UltraWhorld.cpp
# End Source File
# Begin Source File

SOURCE=.\UltraWhorld.def
# End Source File
# Begin Source File

SOURCE=.\UltraWhorld.h
# End Source File
# Begin Source File

SOURCE=.\UltraWhorld.rc
# End Source File
# Begin Source File

SOURCE=.\Version.h
# End Source File
# Begin Source File

SOURCE=.\VideoList.h
# End Source File
# Begin Source File

SOURCE=.\WCritSec.cpp
# End Source File
# Begin Source File

SOURCE=.\WCritSec.h
# End Source File
# Begin Source File

SOURCE=.\WEvent.cpp
# End Source File
# Begin Source File

SOURCE=.\WEvent.h
# End Source File
# Begin Source File

SOURCE=.\WhorldPlug.cpp
# End Source File
# Begin Source File

SOURCE=.\WhorldPlug.h
# End Source File
# Begin Source File

SOURCE=.\WhorldView.cpp
# End Source File
# Begin Source File

SOURCE=.\WhorldView.h
# End Source File
# Begin Source File

SOURCE=.\WObject.h
# End Source File
# Begin Source File

SOURCE=.\WThread.cpp
# End Source File
# Begin Source File

SOURCE=.\WThread.h
# End Source File
# Begin Source File

SOURCE=.\WTimer.cpp
# End Source File
# Begin Source File

SOURCE=.\WTimer.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\UltraWhorld.rc2
# End Source File
# End Group
# End Target
# End Project
