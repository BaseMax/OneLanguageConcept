##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=one
ConfigurationName      :=Debug
WorkspaceConfiguration := $(ConfigurationName)
WorkspacePath          :=/home/am/Project_codelite/wrk
ProjectPath            :=/home/am/Project_codelite/wrk
IntermediateDirectory  :=./build-$(ConfigurationName)/
OutDir                 :=./build-$(ConfigurationName)/
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=am
Date                   :=12/28/20
CodeLitePath           :=/home/am/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=./build-$(ConfigurationName)/bin/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :=$(IntermediateDirectory)/ObjectsList.txt
PCHCompileFlags        :=
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=./build-$(ConfigurationName)//parser.c$(ObjectSuffix) ./build-$(ConfigurationName)//one.c$(ObjectSuffix) ./build-$(ConfigurationName)//lexer.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: MakeIntermediateDirs $(OutputFile)

$(OutputFile): ./build-$(ConfigurationName)//.d $(Objects) 
	@mkdir -p "./build-$(ConfigurationName)/"
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@mkdir -p "./build-$(ConfigurationName)/"
	@mkdir -p ""./build-$(ConfigurationName)/bin""

./build-$(ConfigurationName)//.d:
	@mkdir -p "./build-$(ConfigurationName)/"

PreBuild:


##
## Objects
##
./build-$(ConfigurationName)//parser.c$(ObjectSuffix): parser.c ./build-$(ConfigurationName)//parser.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/am/Project_codelite/wrk/parser.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/parser.c$(ObjectSuffix) $(IncludePath)
./build-$(ConfigurationName)//parser.c$(DependSuffix): parser.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT./build-$(ConfigurationName)//parser.c$(ObjectSuffix) -MF./build-$(ConfigurationName)//parser.c$(DependSuffix) -MM parser.c

./build-$(ConfigurationName)//parser.c$(PreprocessSuffix): parser.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ./build-$(ConfigurationName)//parser.c$(PreprocessSuffix) parser.c

./build-$(ConfigurationName)//one.c$(ObjectSuffix): one.c ./build-$(ConfigurationName)//one.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/am/Project_codelite/wrk/one.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/one.c$(ObjectSuffix) $(IncludePath)
./build-$(ConfigurationName)//one.c$(DependSuffix): one.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT./build-$(ConfigurationName)//one.c$(ObjectSuffix) -MF./build-$(ConfigurationName)//one.c$(DependSuffix) -MM one.c

./build-$(ConfigurationName)//one.c$(PreprocessSuffix): one.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ./build-$(ConfigurationName)//one.c$(PreprocessSuffix) one.c

./build-$(ConfigurationName)//lexer.c$(ObjectSuffix): lexer.c ./build-$(ConfigurationName)//lexer.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/am/Project_codelite/wrk/lexer.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/lexer.c$(ObjectSuffix) $(IncludePath)
./build-$(ConfigurationName)//lexer.c$(DependSuffix): lexer.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT./build-$(ConfigurationName)//lexer.c$(ObjectSuffix) -MF./build-$(ConfigurationName)//lexer.c$(DependSuffix) -MM lexer.c

./build-$(ConfigurationName)//lexer.c$(PreprocessSuffix): lexer.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ./build-$(ConfigurationName)//lexer.c$(PreprocessSuffix) lexer.c


-include ./build-$(ConfigurationName)///*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


