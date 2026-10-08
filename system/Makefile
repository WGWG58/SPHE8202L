#
# Makefile
# Other system related files
#
sinclude	../Makefile.sutl

GOAL		= libsys.a

INCLUDE_DIR	= -I. -I../ -I../h -I../setup -I../ir_vfd -I../emu/ -I../nav/ -I../dsp3 -I../fs 

CFLAGS_COMPILE	= -ffunction-sections

#
# generic flags
#
SOURCES_HDD	= \
		hdd_play.c \
		hdd_file.c \
		hdd_copy.c \
		hdd_gui.c \

SOURCES_DRV	= \
	      	usbpll.c

SOURCES_HW	= \
		hwif.c hwif2.c \

SOURCES		= \
	  	spif.c \
		emu.c \
		reset.c \
		sft.c \
		util.c\
		memcfg.c \
		setvideo.c \
		sysmain.c \
		UartTxd.c\
		sound_if.c\
		polling.c\
		sleep.c \
		riscint.c\
		riscint1.c\
		riscint2.c\
		riscint3.c\
		riscint4.c\
		srv2.c\
		macro.c \
		cardif.c\
		8202_usb_card_if.c\
		jpegeffect_help.c\
		fs_message_show.c\
		$(SOURCES_HDD) \
		$(SOURCES_DRV) \
		$(SOURCES_HW)
	
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

$(GOAL): MIPS $(OBJS) force
	@$(ECHO) \"update library..\"
	@$(XAR) -cr $(GOAL) $(OBJS) 


#
#
#
ifneq ($(MAKECMDGOALS),clean)
sinclude	$(DEPENDS)
endif


