#
# ir_vfd/Makefile
#

.SUFFIXES:
.PHONY:		force

sinclude	../Makefile.sutl

GOAL		= libir.a

INCLUDE_DIR	= -I. -I../ -I../h  -I../setup -I../ir_vfd -I../emu/ -I../nav/ -I../dsp3


#
# CFLAGS_COMPILE
#
CFLAGS_SUPPORT	= 
CFLAGS_SIM	= 
CFLAGS_COMPILE	= $(CFLAGS_SUPPORT) $(CFLAGS_SIM)
		

#
# SOURCES
#
SOURCES		= \
		ir_drv.c\
		ir_filter.c\
		ir_parser.c\
		ircmd.c\
		bit_rate.c\
		time.c\
		vfd.c\
		rw_nvmem.c\
		rsm_upd.c
		
DEPENDS_C	= \
		$(addprefix MIPS/,$(SOURCES:.c=.d))

DEPENDS		= $(DEPENDS_C)

OBJS		= $(DEPENDS:.d=.o)
ASMS		= $(DEPENDS:.d=.s))
DISASMS		= $(DEPENDS:.d=.dis))

.PHONY:		all clean depends bak debug tar


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
ifneq ($(MAKECMDGOALS),tar)
ifneq ($(MAKECMDGOALS),bak)
sinclude	$(DEPENDS)
endif
endif
endif


