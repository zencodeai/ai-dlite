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
CND_CONF=Debug
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
LDLIBSOPTIONS=../dltools/dist/Debug/Cygwin-Windows/libdltools.a ../dlparser/dist/Debug/Cygwin-Windows/libdlparser.a ../antlr/dist/Debug/Cygwin-Windows/libantlr.a ../dlite/dist/Debug/Cygwin-Windows/libdlite.a ../sqlite/dist/Debug/Cygwin-Windows/libsqlite.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Debug.mk dist/Debug/Cygwin-Windows/dlutil.exe

dist/Debug/Cygwin-Windows/dlutil.exe: ../dltools/dist/Debug/Cygwin-Windows/libdltools.a

dist/Debug/Cygwin-Windows/dlutil.exe: ../dlparser/dist/Debug/Cygwin-Windows/libdlparser.a

dist/Debug/Cygwin-Windows/dlutil.exe: ../antlr/dist/Debug/Cygwin-Windows/libantlr.a

dist/Debug/Cygwin-Windows/dlutil.exe: ../dlite/dist/Debug/Cygwin-Windows/libdlite.a

dist/Debug/Cygwin-Windows/dlutil.exe: ../sqlite/dist/Debug/Cygwin-Windows/libsqlite.a

dist/Debug/Cygwin-Windows/dlutil.exe: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/Cygwin-Windows
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/dlutil ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/main.o: nbproject/Makefile-${CND_CONF}.mk main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../shared -I../dlite -I../dltools -I../dlparser -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:
	cd ../dltools && ${MAKE}  -f Makefile CONF=Debug
	cd ../dlparser && ${MAKE}  -f Makefile CONF=Debug
	cd ../antlr && ${MAKE}  -f Makefile CONF=Debug
	cd ../dlite && ${MAKE}  -f Makefile CONF=Debug
	cd ../sqlite && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug
	${RM} dist/Debug/Cygwin-Windows/dlutil.exe

# Subprojects
.clean-subprojects:
	cd ../dltools && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../dlparser && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../antlr && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../dlite && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../sqlite && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
