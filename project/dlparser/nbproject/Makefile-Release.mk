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
	${OBJECTDIR}/OntologyLexer.o \
	${OBJECTDIR}/context.o \
	${OBJECTDIR}/dlparser.o \
	${OBJECTDIR}/OntologyParser.o

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
	${MAKE}  -f nbproject/Makefile-Release.mk dist/Release/Cygwin-Windows/libdlparser.a

dist/Release/Cygwin-Windows/libdlparser.a: ${OBJECTFILES}
	${MKDIR} -p dist/Release/Cygwin-Windows
	${RM} dist/Release/Cygwin-Windows/libdlparser.a
	${AR} rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libdlparser.a ${OBJECTFILES} 
	$(RANLIB) dist/Release/Cygwin-Windows/libdlparser.a

${OBJECTDIR}/OntologyLexer.o: nbproject/Makefile-${CND_CONF}.mk OntologyLexer.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../shared -I../dlite -I../dltools -I../antlr -I../antlr/include -I../sqlite -MMD -MP -MF $@.d -o ${OBJECTDIR}/OntologyLexer.o OntologyLexer.c

${OBJECTDIR}/context.o: nbproject/Makefile-${CND_CONF}.mk context.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../shared -I../dlite -I../dltools -I../antlr -I../antlr/include -I../sqlite -MMD -MP -MF $@.d -o ${OBJECTDIR}/context.o context.cpp

${OBJECTDIR}/dlparser.o: nbproject/Makefile-${CND_CONF}.mk dlparser.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../shared -I../dlite -I../dltools -I../antlr -I../antlr/include -I../sqlite -MMD -MP -MF $@.d -o ${OBJECTDIR}/dlparser.o dlparser.cpp

${OBJECTDIR}/OntologyParser.o: nbproject/Makefile-${CND_CONF}.mk OntologyParser.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../shared -I../dlite -I../dltools -I../antlr -I../antlr/include -I../sqlite -MMD -MP -MF $@.d -o ${OBJECTDIR}/OntologyParser.o OntologyParser.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Release
	${RM} dist/Release/Cygwin-Windows/libdlparser.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
