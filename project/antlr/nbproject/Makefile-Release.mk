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
	${OBJECTDIR}/src/antlr3rewritestreams.o \
	${OBJECTDIR}/src/antlr3stringstream.o \
	${OBJECTDIR}/src/antlr3convertutf.o \
	${OBJECTDIR}/src/antlr3tokenstream.o \
	${OBJECTDIR}/src/antlr3inputstream.o \
	${OBJECTDIR}/src/antlr3string.o \
	${OBJECTDIR}/src/antlr3ucs2inputstream.o \
	${OBJECTDIR}/src/antlr3treeparser.o \
	${OBJECTDIR}/src/antlr3baserecognizer.o \
	${OBJECTDIR}/src/antlr3bitset.o \
	${OBJECTDIR}/src/antlr3intstream.o \
	${OBJECTDIR}/src/antlr3lexer.o \
	${OBJECTDIR}/src/antlr3exception.o \
	${OBJECTDIR}/src/antlr3commontreeadaptor.o \
	${OBJECTDIR}/src/antlr3commontoken.o \
	${OBJECTDIR}/src/antlr3commontree.o \
	${OBJECTDIR}/src/antlr3filestream.o \
	${OBJECTDIR}/src/antlr3parser.o \
	${OBJECTDIR}/src/antlr3basetree.o \
	${OBJECTDIR}/src/antlr3commontreenodestream.o \
	${OBJECTDIR}/src/antlr3debughandlers.o \
	${OBJECTDIR}/src/antlr3basetreeadaptor.o \
	${OBJECTDIR}/src/antlr3collections.o \
	${OBJECTDIR}/src/antlr3cyclicdfa.o \
	${OBJECTDIR}/src/antlr3encodings.o

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
	${MAKE}  -f nbproject/Makefile-Release.mk dist/Release/Cygwin-Windows/libantlr.a

dist/Release/Cygwin-Windows/libantlr.a: ${OBJECTFILES}
	${MKDIR} -p dist/Release/Cygwin-Windows
	${RM} dist/Release/Cygwin-Windows/libantlr.a
	${AR} rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libantlr.a ${OBJECTFILES} 
	$(RANLIB) dist/Release/Cygwin-Windows/libantlr.a

${OBJECTDIR}/src/antlr3rewritestreams.o: nbproject/Makefile-${CND_CONF}.mk src/antlr3rewritestreams.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -Iinclude -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/antlr3rewritestreams.o src/antlr3rewritestreams.c

${OBJECTDIR}/src/antlr3stringstream.o: nbproject/Makefile-${CND_CONF}.mk src/antlr3stringstream.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -Iinclude -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/antlr3stringstream.o src/antlr3stringstream.c

${OBJECTDIR}/src/antlr3convertutf.o: nbproject/Makefile-${CND_CONF}.mk src/antlr3convertutf.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -Iinclude -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/antlr3convertutf.o src/antlr3convertutf.c

${OBJECTDIR}/src/antlr3tokenstream.o: nbproject/Makefile-${CND_CONF}.mk src/antlr3tokenstream.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -Iinclude -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/antlr3tokenstream.o src/antlr3tokenstream.c

${OBJECTDIR}/src/antlr3inputstream.o: nbproject/Makefile-${CND_CONF}.mk src/antlr3inputstream.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -Iinclude -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/antlr3inputstream.o src/antlr3inputstream.c

${OBJECTDIR}/src/antlr3string.o: nbproject/Makefile-${CND_CONF}.mk src/antlr3string.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -Iinclude -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/antlr3string.o src/antlr3string.c

${OBJECTDIR}/src/antlr3ucs2inputstream.o: nbproject/Makefile-${CND_CONF}.mk src/antlr3ucs2inputstream.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -Iinclude -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/antlr3ucs2inputstream.o src/antlr3ucs2inputstream.c

${OBJECTDIR}/src/antlr3treeparser.o: nbproject/Makefile-${CND_CONF}.mk src/antlr3treeparser.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -Iinclude -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/antlr3treeparser.o src/antlr3treeparser.c

${OBJECTDIR}/src/antlr3baserecognizer.o: nbproject/Makefile-${CND_CONF}.mk src/antlr3baserecognizer.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -Iinclude -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/antlr3baserecognizer.o src/antlr3baserecognizer.c

${OBJECTDIR}/src/antlr3bitset.o: nbproject/Makefile-${CND_CONF}.mk src/antlr3bitset.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -Iinclude -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/antlr3bitset.o src/antlr3bitset.c

${OBJECTDIR}/src/antlr3intstream.o: nbproject/Makefile-${CND_CONF}.mk src/antlr3intstream.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -Iinclude -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/antlr3intstream.o src/antlr3intstream.c

${OBJECTDIR}/src/antlr3lexer.o: nbproject/Makefile-${CND_CONF}.mk src/antlr3lexer.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -Iinclude -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/antlr3lexer.o src/antlr3lexer.c

${OBJECTDIR}/src/antlr3exception.o: nbproject/Makefile-${CND_CONF}.mk src/antlr3exception.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -Iinclude -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/antlr3exception.o src/antlr3exception.c

${OBJECTDIR}/src/antlr3commontreeadaptor.o: nbproject/Makefile-${CND_CONF}.mk src/antlr3commontreeadaptor.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -Iinclude -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/antlr3commontreeadaptor.o src/antlr3commontreeadaptor.c

${OBJECTDIR}/src/antlr3commontoken.o: nbproject/Makefile-${CND_CONF}.mk src/antlr3commontoken.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -Iinclude -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/antlr3commontoken.o src/antlr3commontoken.c

${OBJECTDIR}/src/antlr3commontree.o: nbproject/Makefile-${CND_CONF}.mk src/antlr3commontree.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -Iinclude -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/antlr3commontree.o src/antlr3commontree.c

${OBJECTDIR}/src/antlr3filestream.o: nbproject/Makefile-${CND_CONF}.mk src/antlr3filestream.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -Iinclude -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/antlr3filestream.o src/antlr3filestream.c

${OBJECTDIR}/src/antlr3parser.o: nbproject/Makefile-${CND_CONF}.mk src/antlr3parser.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -Iinclude -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/antlr3parser.o src/antlr3parser.c

${OBJECTDIR}/src/antlr3basetree.o: nbproject/Makefile-${CND_CONF}.mk src/antlr3basetree.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -Iinclude -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/antlr3basetree.o src/antlr3basetree.c

${OBJECTDIR}/src/antlr3commontreenodestream.o: nbproject/Makefile-${CND_CONF}.mk src/antlr3commontreenodestream.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -Iinclude -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/antlr3commontreenodestream.o src/antlr3commontreenodestream.c

${OBJECTDIR}/src/antlr3debughandlers.o: nbproject/Makefile-${CND_CONF}.mk src/antlr3debughandlers.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -Iinclude -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/antlr3debughandlers.o src/antlr3debughandlers.c

${OBJECTDIR}/src/antlr3basetreeadaptor.o: nbproject/Makefile-${CND_CONF}.mk src/antlr3basetreeadaptor.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -Iinclude -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/antlr3basetreeadaptor.o src/antlr3basetreeadaptor.c

${OBJECTDIR}/src/antlr3collections.o: nbproject/Makefile-${CND_CONF}.mk src/antlr3collections.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -Iinclude -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/antlr3collections.o src/antlr3collections.c

${OBJECTDIR}/src/antlr3cyclicdfa.o: nbproject/Makefile-${CND_CONF}.mk src/antlr3cyclicdfa.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -Iinclude -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/antlr3cyclicdfa.o src/antlr3cyclicdfa.c

${OBJECTDIR}/src/antlr3encodings.o: nbproject/Makefile-${CND_CONF}.mk src/antlr3encodings.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -Iinclude -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/antlr3encodings.o src/antlr3encodings.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Release
	${RM} dist/Release/Cygwin-Windows/libantlr.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
