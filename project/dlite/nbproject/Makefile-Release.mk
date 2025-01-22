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
	${OBJECTDIR}/store.o \
	${OBJECTDIR}/reasoner.o \
	${OBJECTDIR}/log.o \
	${OBJECTDIR}/node.o \
	${OBJECTDIR}/tbox.o \
	${OBJECTDIR}/factory.o \
	${OBJECTDIR}/symtable.o \
	${OBJECTDIR}/abox.o

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
	${MAKE}  -f nbproject/Makefile-Release.mk dist/Release/Cygwin-Windows/libdlite.a

dist/Release/Cygwin-Windows/libdlite.a: ${OBJECTFILES}
	${MKDIR} -p dist/Release/Cygwin-Windows
	${RM} dist/Release/Cygwin-Windows/libdlite.a
	${AR} rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libdlite.a ${OBJECTFILES} 
	$(RANLIB) dist/Release/Cygwin-Windows/libdlite.a

${OBJECTDIR}/store.o: nbproject/Makefile-${CND_CONF}.mk store.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../shared -I../sqlite -MMD -MP -MF $@.d -o ${OBJECTDIR}/store.o store.cpp

${OBJECTDIR}/reasoner.o: nbproject/Makefile-${CND_CONF}.mk reasoner.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../shared -I../sqlite -MMD -MP -MF $@.d -o ${OBJECTDIR}/reasoner.o reasoner.cpp

${OBJECTDIR}/log.o: nbproject/Makefile-${CND_CONF}.mk log.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../shared -I../sqlite -MMD -MP -MF $@.d -o ${OBJECTDIR}/log.o log.cpp

${OBJECTDIR}/node.o: nbproject/Makefile-${CND_CONF}.mk node.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../shared -I../sqlite -MMD -MP -MF $@.d -o ${OBJECTDIR}/node.o node.cpp

${OBJECTDIR}/tbox.o: nbproject/Makefile-${CND_CONF}.mk tbox.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../shared -I../sqlite -MMD -MP -MF $@.d -o ${OBJECTDIR}/tbox.o tbox.cpp

${OBJECTDIR}/factory.o: nbproject/Makefile-${CND_CONF}.mk factory.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../shared -I../sqlite -MMD -MP -MF $@.d -o ${OBJECTDIR}/factory.o factory.cpp

${OBJECTDIR}/symtable.o: nbproject/Makefile-${CND_CONF}.mk symtable.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../shared -I../sqlite -MMD -MP -MF $@.d -o ${OBJECTDIR}/symtable.o symtable.cpp

${OBJECTDIR}/abox.o: nbproject/Makefile-${CND_CONF}.mk abox.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../shared -I../sqlite -MMD -MP -MF $@.d -o ${OBJECTDIR}/abox.o abox.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Release
	${RM} dist/Release/Cygwin-Windows/libdlite.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
