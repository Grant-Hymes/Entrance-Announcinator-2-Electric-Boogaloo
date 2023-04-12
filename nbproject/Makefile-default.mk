#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/FinalProject.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/FinalProject.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=FinalProject_Main_v001.c FinalProject_LEDLibrary_v001.c FinalProject_ASMLibrary.s

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/FinalProject_Main_v001.o ${OBJECTDIR}/FinalProject_LEDLibrary_v001.o ${OBJECTDIR}/FinalProject_ASMLibrary.o
POSSIBLE_DEPFILES=${OBJECTDIR}/FinalProject_Main_v001.o.d ${OBJECTDIR}/FinalProject_LEDLibrary_v001.o.d ${OBJECTDIR}/FinalProject_ASMLibrary.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/FinalProject_Main_v001.o ${OBJECTDIR}/FinalProject_LEDLibrary_v001.o ${OBJECTDIR}/FinalProject_ASMLibrary.o

# Source Files
SOURCEFILES=FinalProject_Main_v001.c FinalProject_LEDLibrary_v001.c FinalProject_ASMLibrary.s



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/FinalProject.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ64GA002
MP_LINKER_FILE_OPTION=,--script=p24FJ64GA002.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/FinalProject_Main_v001.o: FinalProject_Main_v001.c  .generated_files/flags/default/fd9d770c4814c10fd9d0a47d1243d96019f5b5a9 .generated_files/flags/default/4f26fc17b1b08a26e7499c8c7a622ac16dba8976
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/FinalProject_Main_v001.o.d 
	@${RM} ${OBJECTDIR}/FinalProject_Main_v001.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FinalProject_Main_v001.c  -o ${OBJECTDIR}/FinalProject_Main_v001.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/FinalProject_Main_v001.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/FinalProject_LEDLibrary_v001.o: FinalProject_LEDLibrary_v001.c  .generated_files/flags/default/a51d6ec85189de6f7458993100cdcfba7a88a5ac .generated_files/flags/default/4f26fc17b1b08a26e7499c8c7a622ac16dba8976
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/FinalProject_LEDLibrary_v001.o.d 
	@${RM} ${OBJECTDIR}/FinalProject_LEDLibrary_v001.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FinalProject_LEDLibrary_v001.c  -o ${OBJECTDIR}/FinalProject_LEDLibrary_v001.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/FinalProject_LEDLibrary_v001.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/FinalProject_Main_v001.o: FinalProject_Main_v001.c  .generated_files/flags/default/8e186f68f3f12881b3ffadc574c1fadd28d1a461 .generated_files/flags/default/4f26fc17b1b08a26e7499c8c7a622ac16dba8976
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/FinalProject_Main_v001.o.d 
	@${RM} ${OBJECTDIR}/FinalProject_Main_v001.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FinalProject_Main_v001.c  -o ${OBJECTDIR}/FinalProject_Main_v001.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/FinalProject_Main_v001.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/FinalProject_LEDLibrary_v001.o: FinalProject_LEDLibrary_v001.c  .generated_files/flags/default/77b97c83977842b1c700be77b68b88ea901816d2 .generated_files/flags/default/4f26fc17b1b08a26e7499c8c7a622ac16dba8976
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/FinalProject_LEDLibrary_v001.o.d 
	@${RM} ${OBJECTDIR}/FinalProject_LEDLibrary_v001.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FinalProject_LEDLibrary_v001.c  -o ${OBJECTDIR}/FinalProject_LEDLibrary_v001.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/FinalProject_LEDLibrary_v001.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/FinalProject_ASMLibrary.o: FinalProject_ASMLibrary.s  .generated_files/flags/default/a5d21de1396cb622bb690dadbfb8588177615579 .generated_files/flags/default/4f26fc17b1b08a26e7499c8c7a622ac16dba8976
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/FinalProject_ASMLibrary.o.d 
	@${RM} ${OBJECTDIR}/FinalProject_ASMLibrary.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  FinalProject_ASMLibrary.s  -o ${OBJECTDIR}/FinalProject_ASMLibrary.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  -Wa,-MD,"${OBJECTDIR}/FinalProject_ASMLibrary.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/FinalProject_ASMLibrary.o: FinalProject_ASMLibrary.s  .generated_files/flags/default/778e1f76aaa34178c5aad7deeb3e53588c1ddb3e .generated_files/flags/default/4f26fc17b1b08a26e7499c8c7a622ac16dba8976
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/FinalProject_ASMLibrary.o.d 
	@${RM} ${OBJECTDIR}/FinalProject_ASMLibrary.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  FinalProject_ASMLibrary.s  -o ${OBJECTDIR}/FinalProject_ASMLibrary.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  -Wa,-MD,"${OBJECTDIR}/FinalProject_ASMLibrary.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/FinalProject.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/FinalProject.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)      -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/FinalProject.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/FinalProject.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/FinalProject.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
