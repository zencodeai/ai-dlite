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
	${OBJECTDIR}/fmtinfix.o \
	${OBJECTDIR}/session.o

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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Debug.mk dist/Debug/Cygwin-Windows/libdltools.a

dist/Debug/Cygwin-Windows/libdltools.a: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/Cygwin-Windows
	${RM} dist/Debug/Cygwin-Windows/libdltools.a
	${AR} rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libdltools.a ${OBJECTFILES} 
	$(RANLIB) dist/Debug/Cygwin-Windows/libdltools.a

${OBJECTDIR}/fmtinfix.o: nbproject/Makefile-${CND_CONF}.mk fmtinfix.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../dlite -I../dlparser -I../dltools -I../shared -I../sqlite -MMD -MP -MF $@.d -o ${OBJECTDIR}/fmtinfix.o fmtinfix.cpp

${OBJECTDIR}/session.o: nbproject/Makefile-${CND_CONF}.mk session.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../dlite -I../dlparser -I../dltools -I../shared -I../sqlite -MMD -MP -MF $@.d -o ${OBJECTDIR}/session.o session.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug
	${RM} dist/Debug/Cygwin-Windows/libdltools.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
