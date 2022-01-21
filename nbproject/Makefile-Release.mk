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
CND_CONF=Release
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
	${OBJECTDIR}/rework/wbutton.o \
	${OBJECTDIR}/rework/wcheckboxes.o \
	${OBJECTDIR}/rework/winputline.o \
	${OBJECTDIR}/rework/wlistbox.o \
	${OBJECTDIR}/rework/wmemo.o \
	${OBJECTDIR}/rework/wradiobuttons.o \
	${OBJECTDIR}/rework/wstatictext.o \
	${OBJECTDIR}/tbuttonproperties.o \
	${OBJECTDIR}/tcheckboxesproperties.o \
	${OBJECTDIR}/tcolorfield.o \
	${OBJECTDIR}/tcomponentdialog.o \
	${OBJECTDIR}/tcustomdialog.o \
	${OBJECTDIR}/tdialogdesigner.o \
	${OBJECTDIR}/tdialogproperties.o \
	${OBJECTDIR}/tinputlineproperties.o \
	${OBJECTDIR}/tlistboxproperties.o \
	${OBJECTDIR}/tmemoproperties.o \
	${OBJECTDIR}/tprg.o \
	${OBJECTDIR}/tradiobuttonproperties.o \
	${OBJECTDIR}/trialdialog.o \
	${OBJECTDIR}/tselectcolordialog.o \
	${OBJECTDIR}/tstatictextproperties.o \
	${OBJECTDIR}/ttrialbutton.o \
	${OBJECTDIR}/ttrialcheckboxes.o \
	${OBJECTDIR}/ttrialdialogbackground.o \
	${OBJECTDIR}/ttrialinputline.o \
	${OBJECTDIR}/ttriallistbox.o \
	${OBJECTDIR}/ttrialmemo.o \
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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/designer.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/designer.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/designer ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/common.o: common.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/common.o common.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/rework/wbutton.o: rework/wbutton.cpp
	${MKDIR} -p ${OBJECTDIR}/rework
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/rework/wbutton.o rework/wbutton.cpp

${OBJECTDIR}/rework/wcheckboxes.o: rework/wcheckboxes.cpp
	${MKDIR} -p ${OBJECTDIR}/rework
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/rework/wcheckboxes.o rework/wcheckboxes.cpp

${OBJECTDIR}/rework/winputline.o: rework/winputline.cpp
	${MKDIR} -p ${OBJECTDIR}/rework
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/rework/winputline.o rework/winputline.cpp

${OBJECTDIR}/rework/wlistbox.o: rework/wlistbox.cpp
	${MKDIR} -p ${OBJECTDIR}/rework
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/rework/wlistbox.o rework/wlistbox.cpp

${OBJECTDIR}/rework/wmemo.o: rework/wmemo.cpp
	${MKDIR} -p ${OBJECTDIR}/rework
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/rework/wmemo.o rework/wmemo.cpp

${OBJECTDIR}/rework/wradiobuttons.o: rework/wradiobuttons.cpp
	${MKDIR} -p ${OBJECTDIR}/rework
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/rework/wradiobuttons.o rework/wradiobuttons.cpp

${OBJECTDIR}/rework/wstatictext.o: rework/wstatictext.cpp
	${MKDIR} -p ${OBJECTDIR}/rework
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/rework/wstatictext.o rework/wstatictext.cpp

${OBJECTDIR}/tbuttonproperties.o: tbuttonproperties.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tbuttonproperties.o tbuttonproperties.cpp

${OBJECTDIR}/tcheckboxesproperties.o: tcheckboxesproperties.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tcheckboxesproperties.o tcheckboxesproperties.cpp

${OBJECTDIR}/tcolorfield.o: tcolorfield.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tcolorfield.o tcolorfield.cpp

${OBJECTDIR}/tcomponentdialog.o: tcomponentdialog.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tcomponentdialog.o tcomponentdialog.cpp

${OBJECTDIR}/tcustomdialog.o: tcustomdialog.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tcustomdialog.o tcustomdialog.cpp

${OBJECTDIR}/tdialogdesigner.o: tdialogdesigner.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tdialogdesigner.o tdialogdesigner.cpp

${OBJECTDIR}/tdialogproperties.o: tdialogproperties.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tdialogproperties.o tdialogproperties.cpp

${OBJECTDIR}/tinputlineproperties.o: tinputlineproperties.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tinputlineproperties.o tinputlineproperties.cpp

${OBJECTDIR}/tlistboxproperties.o: tlistboxproperties.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tlistboxproperties.o tlistboxproperties.cpp

${OBJECTDIR}/tmemoproperties.o: tmemoproperties.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tmemoproperties.o tmemoproperties.cpp

${OBJECTDIR}/tprg.o: tprg.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tprg.o tprg.cpp

${OBJECTDIR}/tradiobuttonproperties.o: tradiobuttonproperties.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tradiobuttonproperties.o tradiobuttonproperties.cpp

${OBJECTDIR}/trialdialog.o: trialdialog.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/trialdialog.o trialdialog.cpp

${OBJECTDIR}/tselectcolordialog.o: tselectcolordialog.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tselectcolordialog.o tselectcolordialog.cpp

${OBJECTDIR}/tstatictextproperties.o: tstatictextproperties.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tstatictextproperties.o tstatictextproperties.cpp

${OBJECTDIR}/ttrialbutton.o: ttrialbutton.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ttrialbutton.o ttrialbutton.cpp

${OBJECTDIR}/ttrialcheckboxes.o: ttrialcheckboxes.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ttrialcheckboxes.o ttrialcheckboxes.cpp

${OBJECTDIR}/ttrialdialogbackground.o: ttrialdialogbackground.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ttrialdialogbackground.o ttrialdialogbackground.cpp

${OBJECTDIR}/ttrialinputline.o: ttrialinputline.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ttrialinputline.o ttrialinputline.cpp

${OBJECTDIR}/ttriallistbox.o: ttriallistbox.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ttriallistbox.o ttriallistbox.cpp

${OBJECTDIR}/ttrialmemo.o: ttrialmemo.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ttrialmemo.o ttrialmemo.cpp

${OBJECTDIR}/ttrialradiobuttons.o: ttrialradiobuttons.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ttrialradiobuttons.o ttrialradiobuttons.cpp

${OBJECTDIR}/ttrialstatictext.o: ttrialstatictext.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ttrialstatictext.o ttrialstatictext.cpp

${OBJECTDIR}/twinextmenu.o: twinextmenu.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/twinextmenu.o twinextmenu.cpp

${OBJECTDIR}/twinsizeindicator.o: twinsizeindicator.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/twinsizeindicator.o twinsizeindicator.cpp

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
