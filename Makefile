#SrcPlatforms [Windows]
SrcPlatform = Windows
#DstPlatforms [Windows]
DstPlatform = Windows
Configuration=Release
#Arch [x64]
Architecture=x64

PLAT=$(DstPlatform)/$(Configuration)-$(Architecture)
EngineOutputDir=bin/$(PLAT)/Morphic/
EngineIntDir=int/$(PLAT)/Morphic/
AppOutputDir=bin/$(PLAT)/SandboxApp/
AppIntDir=int/$(PLAT)/SandboxApp/

EngineInclude=Morphic/include/
EngineSrc=Morphic/src/
AppInclude=SandboxApp/include/
AppSrc=SandboxApp/src/

ifeq ($(SrcPlatform), Windows)
include WindowsMake.md
endif

default: make_folders
make_folders: 
	$(MakeFolders) $(EngineOutputDir)
	$(MakeFolders) $(EngineIntDir)
	$(MakeFolders) $(AppOutputDir)
	$(MakeFolders) $(AppIntDir)
build_engine_pch:
	$(CC) $(CF) $(CFlags) $(ECFlags) $(IncludeDirs) $(EngineIncludeDirs) $(CPCH)Morphic/pch.h $(OPCH)$(EngineIntDir)pch.pch $(OBJOutput)$(EngineIntDir) $(EngineSrc)pch.cpp
build_engine:
	$(CC) $(CF) $(CFlags) $(ECFlags) $(IncludeDirs) $(EngineIncludeDirs) $(UPCH)Morphic/pch.h $(OPCH)$(EngineIntDir)pch.pch $(OBJOutput)$(EngineIntDir) $(EngineFiles)
	$(LK) $(LFlags) $(ELFlags) $(EngineIntDir)*.obj $(LinkerOut)$(EngineOutputDir)Morphic.dll
	cp $(EngineOutputDir)Morphic.dll $(AppOutputDir)Morphic.dll
build_app:
	$(CC) $(CF) $(CFlags) $(ACFlags) $(IncludeDirs) $(AppIncludeDirs) $(OBJOutput)$(AppIntDir) $(AppFiles)
	$(LK) $(LFlags) $(ALFlags) $(LibPaths) $(AppLibPaths) $(Libs) $(AppLibs) $(AppIntDir)*.obj $(LinkerOut)$(AppOutputDir)App.exe
run:
	$(AppOutputDir)App.exe