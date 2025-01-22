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
LDLIBSOPTIONS=../dlite/dist/Release/Cygwin-Windows/libdlite.a ../dlparser/dist/Release/Cygwin-Windows/libdlparser.a ../dltools/dist/Release/Cygwin-Windows/libdltools.a ../sqlite/dist/Release/Cygwin-Windows/libsqlite.a ../antlr/dist/Release/Cygwin-Windows/libantlr.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Release.mk dist/Release/Cygwin-Windows/test.exe

dist/Release/Cygwin-Windows/test.exe: ../dlite/dist/Release/Cygwin-Windows/libdlite.a

dist/Release/Cygwin-Windows/test.exe: ../dlparser/dist/Release/Cygwin-Windows/libdlparser.a

dist/Release/Cygwin-Windows/test.exe: ../dltools/dist/Release/Cygwin-Windows/libdltools.a

dist/Release/Cygwin-Windows/test.exe: ../sqlite/dist/Release/Cygwin-Windows/libsqlite.a

dist/Release/Cygwin-Windows/test.exe: ../antlr/dist/Release/Cygwin-Windows/libantlr.a

dist/Release/Cygwin-Windows/test.exe: ${OBJECTFILES}
	${MKDIR} -p dist/Release/Cygwin-Windows
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/test ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/main.o: nbproject/Makefile-${CND_CONF}.mk main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../shared -I../sqlite -I../dlite -I../dltools -I../dlparser -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:
	cd ../dlite && ${MAKE}  -f Makefile CONF=Release
	cd ../dlparser && ${MAKE}  -f Makefile CONF=Release
	cd ../dltools && ${MAKE}  -f Makefile CONF=Release
	cd ../sqlite && ${MAKE}  -f Makefile CONF=Release
	cd ../antlr && ${MAKE}  -f Makefile CONF=Release

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Release
	${RM} dist/Release/Cygwin-Windows/test.exe

# Subprojects
.clean-subprojects:
	cd ../dlite && ${MAKE}  -f Makefile CONF=Release clean
	cd ../dlparser && ${MAKE}  -f Makefile CONF=Release clean
	cd ../dltools && ${MAKE}  -f Makefile CONF=Release clean
	cd ../sqlite && ${MAKE}  -f Makefile CONF=Release clean
	cd ../antlr && ${MAKE}  -f Makefile CONF=Release clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
