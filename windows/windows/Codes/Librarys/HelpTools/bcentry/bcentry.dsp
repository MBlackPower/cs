# Microsoft Developer Studio Project File - Name="bcentry" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=bcentry - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "bcentry.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "bcentry.mak" CFG="bcentry - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "bcentry - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "bcentry - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "bcentry - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "BCENTRY_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "BCENTRY_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"Release/HelpTools.dll"

!ELSEIF  "$(CFG)" == "bcentry - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "BCENTRY_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "BCENTRY_EXPORTS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"Debug/HelpTools.dll" /pdbtype:sept
# SUBTRACT LINK32 /nodefaultlib /force

!ENDIF 

# Begin Target

# Name "bcentry - Win32 Release"
# Name "bcentry - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\dllentry.cpp
# End Source File
# End Group
# Begin Group "ClassLib"

# PROP Default_Filter ""
# Begin Group "threadmanage"

# PROP Default_Filter ""
# Begin Group "pool"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\threadmanage\pool\bqueue.h
# End Source File
# Begin Source File

SOURCE=..\threadmanage\pool\task.cpp
# End Source File
# Begin Source File

SOURCE=..\threadmanage\pool\task.h
# End Source File
# Begin Source File

SOURCE=..\threadmanage\pool\threadmanager.cpp
# End Source File
# Begin Source File

SOURCE=..\threadmanage\pool\threadmanager.h
# End Source File
# Begin Source File

SOURCE=..\threadmanage\pool\worker.cpp
# End Source File
# Begin Source File

SOURCE=..\threadmanage\pool\worker.h
# End Source File
# End Group
# Begin Group "thread"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\threadmanage\thread\synch.cpp
# End Source File
# Begin Source File

SOURCE=..\threadmanage\thread\synch.h
# End Source File
# Begin Source File

SOURCE=..\threadmanage\thread\thread.cpp
# End Source File
# Begin Source File

SOURCE=..\threadmanage\thread\thread.h
# End Source File
# End Group
# End Group
# Begin Group "file"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\file\bdirectory.cpp
# End Source File
# Begin Source File

SOURCE=..\file\bdirectory.h
# End Source File
# Begin Source File

SOURCE=..\file\bfile.cpp
# End Source File
# Begin Source File

SOURCE=..\file\bfile.h
# End Source File
# End Group
# Begin Group "share"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\share\share.h
# End Source File
# End Group
# Begin Group "debuglog"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\debuglog\debuglog.cpp
# End Source File
# Begin Source File

SOURCE=..\debuglog\debuglog.h
# End Source File
# End Group
# End Group
# End Target
# End Project
