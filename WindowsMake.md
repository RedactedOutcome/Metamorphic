#Host System Windows
MakeFolders=mkdir -p 
CC=cl
LK=link
CFlags=
LFlags=
#engine
ECFlags=
ELFlags=

#app
ACFlags=
ALFlags=

#Flags
#CompileFlag
CF=/c
#Include flag
IF=/I
#Define Flag
DF=/D
#Lib dir flag
LDF=/LIBPATH:
#OutputObjs
OBJOutput=/Fo
#CreatePCH
CPCH=/Yc
OPCH=/Fp
#Using a pch with a name
UPCH=/Yu

#Linker output flag
LinkerOut=/out:

IncludeDirs=$(IF)Morphic/include/
LibPaths=
Libs=
Files=

ECFlags=$(DF)MORPHIC_EXPORTS
ELFlags=/DLL
Libs += GDI32.lib Shell32.lib kernel32.lib User32.lib
EngineFiles+= $(EngineSrc)Test.cpp
AppFiles+=$(EngineSrc)Test.cpp