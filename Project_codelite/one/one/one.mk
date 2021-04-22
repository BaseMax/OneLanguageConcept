##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=one
ConfigurationName      :=Debug
WorkspaceConfiguration := $(ConfigurationName)
WorkspacePath          :=/home/am/Project_codelite/one
ProjectPath            :=/home/am/Project_codelite/one/one
IntermediateDirectory  :=../build-$(ConfigurationName)/one
OutDir                 :=../build-$(ConfigurationName)/one
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=am
Date                   :=09/21/20
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
OutputFile             :=../build-$(ConfigurationName)/bin/$(ProjectName)
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
Objects0=../build-$(ConfigurationName)/one/token.c$(ObjectSuffix) ../build-$(ConfigurationName)/one/one.c$(ObjectSuffix) ../build-$(ConfigurationName)/one/scanner.c$(ObjectSuffix) ../build-$(ConfigurationName)/one/parser.c$(ObjectSuffix) ../build-$(ConfigurationName)/one/buffer.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: MakeIntermediateDirs $(OutputFile)

$(OutputFile): ../build-$(ConfigurationName)/one/.d $(Objects) 
	@mkdir -p "../build-$(ConfigurationName)/one"
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@mkdir -p "../build-$(ConfigurationName)/one"
	@mkdir -p ""../build-$(ConfigurationName)/bin""

../build-$(ConfigurationName)/one/.d:
	@mkdir -p "../build-$(ConfigurationName)/one"

PreBuild:


##
## Objects
##
../build-$(ConfigurationName)/one/token.c$(ObjectSuffix): token.c ../build-$(ConfigurationName)/one/token.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/am/Project_codelite/one/one/token.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/token.c$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/one/token.c$(DependSuffix): token.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/one/token.c$(ObjectSuffix) -MF../build-$(ConfigurationName)/one/token.c$(DependSuffix) -MM token.c

../build-$(ConfigurationName)/one/token.c$(PreprocessSuffix): token.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/one/token.c$(PreprocessSuffix) token.c

../build-$(ConfigurationName)/one/one.c$(ObjectSuffix): one.c ../build-$(ConfigurationName)/one/one.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/am/Project_codelite/one/one/one.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/one.c$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/one/one.c$(DependSuffix): one.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/one/one.c$(ObjectSuffix) -MF../build-$(ConfigurationName)/one/one.c$(DependSuffix) -MM one.c

../build-$(ConfigurationName)/one/one.c$(PreprocessSuffix): one.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/one/one.c$(PreprocessSuffix) one.c

../build-$(ConfigurationName)/one/scanner.c$(ObjectSuffix): scanner.c ../build-$(ConfigurationName)/one/scanner.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/am/Project_codelite/one/one/scanner.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/scanner.c$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/one/scanner.c$(DependSuffix): scanner.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/one/scanner.c$(ObjectSuffix) -MF../build-$(ConfigurationName)/one/scanner.c$(DependSuffix) -MM scanner.c

../build-$(ConfigurationName)/one/scanner.c$(PreprocessSuffix): scanner.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/one/scanner.c$(PreprocessSuffix) scanner.c

../build-$(ConfigurationName)/one/parser.c$(ObjectSuffix): parser.c ../build-$(ConfigurationName)/one/parser.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/am/Project_codelite/one/one/parser.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/parser.c$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/one/parser.c$(DependSuffix): parser.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/one/parser.c$(ObjectSuffix) -MF../build-$(ConfigurationName)/one/parser.c$(DependSuffix) -MM parser.c

../build-$(ConfigurationName)/one/parser.c$(PreprocessSuffix): parser.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/one/parser.c$(PreprocessSuffix) parser.c

../build-$(ConfigurationName)/one/buffer.c$(ObjectSuffix): buffer.c ../build-$(ConfigurationName)/one/buffer.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/am/Project_codelite/one/one/buffer.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/buffer.c$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/one/buffer.c$(DependSuffix): buffer.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/one/buffer.c$(ObjectSuffix) -MF../build-$(ConfigurationName)/one/buffer.c$(DependSuffix) -MM buffer.c

../build-$(ConfigurationName)/one/buffer.c$(PreprocessSuffix): buffer.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/one/buffer.c$(PreprocessSuffix) buffer.c


-include ../build-$(ConfigurationName)/one//*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


