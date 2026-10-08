#
# Makefile
#

.SUFFIXES:
.PHONY:		force
.PHONY:		all clean depends bak debug tar

sinclude	../Makefile.sutl
GOAL		= libosd.a
INCLUDE_DIR	= -I. -I../ -I../h -I../ir_vfd -I../nav/ -I../dsp3 -I../setup

#
# generic flags
#
CFLAGS_SUPPORT	=
CFLAGS_SIM	=
CFLAGS_COMPILE	= -ffunction-sections
#CFLAGS_COMPILE	= $(CFLAGS_SUPPORT) $(CFLAGS_SIM)

#
# Sources
#
SOURCES	= \
		osd3.c \
		osd_BmpUI.c \
		osd_midi.c \
		osdutil.c \
		osdv2.c \
		osd_hw.c\
		osd_draw.c\
		osd_palette.c\
		osd_pal_rgb_32b.c\
		osd_customers.c\
		osd_ShowWarningBox.c\
		osd_WndProc.c\
		osd_AppRegionInit.c\
		osd_AppDraw.c\
		osd_hw_highlight.c\
		
DEPENDS_C	= \
		$(addprefix MIPS/,$(SOURCES:.c=.d))

DEPENDS		= $(DEPENDS_C)

OBJS		= $(DEPENDS:.d=.o)
ASMS		= $(DEPENDS:.d=.s))
DISASMS		= $(DEPENDS:.d=.dis))


#
# main target
#
all:	$(GOAL)
	@$(ECHO) \"$(GOAL) made\"


#
#
#
$(GOAL): MIPS $(OBJS) force
	@$(ECHO) \"update library..\"
	@$(XAR) -cr $(GOAL) $(OBJS)


#
#
#
ifneq ($(MAKECMDGOALS),clean)
sinclude	$(DEPENDS)
endif


