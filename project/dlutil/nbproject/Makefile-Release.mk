#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc.exe
CCC=g++.exe
CXX=g++.exe
FC=
AS=

# Macros
CND_PLATFORM=Cygwin-Windows
CND_CONF=Release
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/main.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=../dltools/dist/Release/Cygwin-Windows/libdltools.a ../dlparser/dist/Release/Cygwin-Windows/libdlparser.a ../antlr/dist/Release/Cygwin-Windows/libantlr.a ../dlite/dist/Release/Cygwin-Windows/libdlite.a ../sqlite/dist/Release/Cygwin-Windows/libsqlite.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Release.mk dist/Release/Cygwin-Windows/dlutil.exe

dist/Release/Cygwin-Windows/dlutil.exe: ../dltools/dist/Release/Cygwin-Windows/libdltools.a

dist/Release/Cygwin-Windows/dlutil.exe: ../dlparser/dist/Release/Cygwin-Windows/libdlparser.a

dist/Release/Cygwin-Windows/dlutil.exe: ../antlr/dist/Release/Cygwin-Windows/libantlr.a

dist/Release/Cygwin-Windows/dlutil.exe: ../dlite/dist/Release/Cygwin-Windows/libdlite.a

dist/Release/Cygwin-Windows/dlutil.exe: ../sqlite/dist/Release/Cygwin-Windows/libsqlite.a

dist/Release/Cygwin-Windows/dlutil.exe: ${OBJECTFILES}
	${MKDIR} -p dist/Release/Cygwin-Windows
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/dlutil ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/main.o: nbproject/Makefile-${CND_CONF}.mk main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../shared -I../dlite -I../dltools -I../dlparser -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:
	cd ../dltools && ${MAKE}  -f Makefile CONF=Release
	cd ../dlparser && ${MAKE}  -f Makefile CONF=Release
	cd ../antlr && ${MAKE}  -f Makefile CONF=Release
	cd ../dlite && ${MAKE}  -f Makefile CONF=Release
	cd ../sqlite && ${MAKE}  -f Makefile CONF=Release

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Release
	${RM} dist/Release/Cygwin-Windows/dlutil.exe

# Subprojects
.clean-subprojects:
	cd ../dltools && ${MAKE}  -f Makefile CONF=Release clean
	cd ../dlparser && ${MAKE}  -f Makefile CONF=Release clean
	cd ../antlr && ${MAKE}  -f Makefile CONF=Release clean
	cd ../dlite && ${MAKE}  -f Makefile CONF=Release clean
	cd ../sqlite && ${MAKE}  -f Makefile CONF=Release clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
