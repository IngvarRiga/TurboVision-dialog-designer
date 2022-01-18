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
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW_TDM-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/common.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/rework/wstatictext.o \
	${OBJECTDIR}/tcolorfield.o \
	${OBJECTDIR}/tcomponentdialog.o \
	${OBJECTDIR}/tcustomdialog.o \
	${OBJECTDIR}/tdialogdesigner.o \
	${OBJECTDIR}/tdialogproperties.o \
	${OBJECTDIR}/tprg.o \
	${OBJECTDIR}/trialdialog.o \
	${OBJECTDIR}/tselectcolordialog.o \
	${OBJECTDIR}/tstatictextproperties.o \
	${OBJECTDIR}/ttrialbutton.o \
	${OBJECTDIR}/ttrialcheckboxes.o \
	${OBJECTDIR}/ttrialdialogbackground.o \
	${OBJECTDIR}/ttrialinputline.o \
	${OBJECTDIR}/ttriallistbox.o \
	${OBJECTDIR}/ttrialradiobuttons.o \
	${OBJECTDIR}/ttrialstatictext.o \
	${OBJECTDIR}/twinextmenu.o \
	${OBJECTDIR}/twinsizeindicator.o


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
LDLIBSOPTIONS=-ltvision

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/designer.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/designer.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/designer ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/common.o: common.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DRUS -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/common.o common.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DRUS -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/rework/wstatictext.o: rework/wstatictext.cpp
	${MKDIR} -p ${OBJECTDIR}/rework
	${RM} "$@.d"
	$(COMPILE.cc) -g -DRUS -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/rework/wstatictext.o rework/wstatictext.cpp

${OBJECTDIR}/tcolorfield.o: tcolorfield.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DRUS -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tcolorfield.o tcolorfield.cpp

${OBJECTDIR}/tcomponentdialog.o: tcomponentdialog.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DRUS -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tcomponentdialog.o tcomponentdialog.cpp

${OBJECTDIR}/tcustomdialog.o: tcustomdialog.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DRUS -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tcustomdialog.o tcustomdialog.cpp

${OBJECTDIR}/tdialogdesigner.o: tdialogdesigner.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DRUS -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tdialogdesigner.o tdialogdesigner.cpp

${OBJECTDIR}/tdialogproperties.o: tdialogproperties.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DRUS -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tdialogproperties.o tdialogproperties.cpp

${OBJECTDIR}/tprg.o: tprg.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DRUS -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tprg.o tprg.cpp

${OBJECTDIR}/trialdialog.o: trialdialog.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DRUS -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/trialdialog.o trialdialog.cpp

${OBJECTDIR}/tselectcolordialog.o: tselectcolordialog.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DRUS -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tselectcolordialog.o tselectcolordialog.cpp

${OBJECTDIR}/tstatictextproperties.o: tstatictextproperties.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DRUS -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tstatictextproperties.o tstatictextproperties.cpp

${OBJECTDIR}/ttrialbutton.o: ttrialbutton.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DRUS -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ttrialbutton.o ttrialbutton.cpp

${OBJECTDIR}/ttrialcheckboxes.o: ttrialcheckboxes.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DRUS -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ttrialcheckboxes.o ttrialcheckboxes.cpp

${OBJECTDIR}/ttrialdialogbackground.o: ttrialdialogbackground.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DRUS -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ttrialdialogbackground.o ttrialdialogbackground.cpp

${OBJECTDIR}/ttrialinputline.o: ttrialinputline.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DRUS -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ttrialinputline.o ttrialinputline.cpp

${OBJECTDIR}/ttriallistbox.o: ttriallistbox.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DRUS -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ttriallistbox.o ttriallistbox.cpp

${OBJECTDIR}/ttrialradiobuttons.o: ttrialradiobuttons.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DRUS -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ttrialradiobuttons.o ttrialradiobuttons.cpp

${OBJECTDIR}/ttrialstatictext.o: ttrialstatictext.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DRUS -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ttrialstatictext.o ttrialstatictext.cpp

${OBJECTDIR}/twinextmenu.o: twinextmenu.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DRUS -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/twinextmenu.o twinextmenu.cpp

${OBJECTDIR}/twinsizeindicator.o: twinsizeindicator.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DRUS -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/twinsizeindicator.o twinsizeindicator.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
