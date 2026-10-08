#
# Makefile
# DVD presentation engin files
#

.SUFFIXES:
.PHONY:		force

VPATH		= MIPS
sinclude	../Makefile.sutl

TARGET		= mipsel-elf
#PREFIX		= $(TARGET)-

GOAL		= libdsp3.a
GOAL_AAC	= libdsp3_aac.a
GOAL_PPCM   = libdsp3_ppcm.a
# GOAL_WMA    = libdsp3_wma.a
GOAL_DTS    = libdsp3_dts.a

INCLUDE_DIR	= -I. -I../ -I../h -I../ir_vfd -I../nav

# modified by Jack Ciao for 1002 on 2006/08/28
ifeq	(1002, ${IC_VER})
	CFLAGS_MACHINE	= -membedded-data
else
	CFLAGS_MACHINE	= -m728 -membedded-data
endif

CFLAGS_C	= \
		-g \
		-O2 -Os \
		-fno-writable-strings \
		-fstrength-reduce \
		-fthread-jumps \
		-W -Wall \
		$(INCLUDE_DIR)

		# -fforce-mem \
		# -fforce-addr \

CFLAGS_S	= \
		-g1 \
		-O2 \
		$(INCLUDE_DIR)

CFLAGS_ENDIAN	= -DLITTLE_ENDIAN

#
# generic flags
#
CFLAGS_SUPPORT	=
CFLAGS_SIM	=

CFLAGS_COMPILE	= \
		$(CFLAGS_SUPPORT) $(CFLAGS_SIM) $(CFLAGS_ENDIAN)

CFLAGS_MIPS	= $(CFLAGS_MACHINE) $(CFLAGS_C) $(CFLAGS_COMPILE)
CFLAGS_MIPS_S	= $(CFLAGS_MACHINE) $(CFLAGS_S) $(CFLAGS_COMPILE)

LDFLAGS		= -nostartfiles -T $(LDSCRIPT) -L. $(LIBRARIES) --cref
		# -Wl,--sort-common
		#
		#

SOURCES	= \
		dsp3rom.d16.945.ac3.c \
		dsp3rom.d16.ac3.2ch.c \
		dsp3rom.d16.ac3.5.1ch.16M.c \
		dsp3rom.d16.ac3.c \
		dsp3rom.d16.ac3.raw.analog.2ch.c \
		dsp3rom.d16.ac3.spi.8200.c \
		dsp3rom.d16.ac3.spi.8202.c \
		dsp3rom.d16.cd.2ch.c \
		dsp3rom.d16.cd.c \
		dsp3rom.d16.cd.mp3.encoder.c \
		dsp3rom.d16.cd.spi.8200.c \
		dsp3rom.d16.cd.spi.8202.c \
		dsp3rom.d16.hdcd.c \
		dsp3rom.d16.lpcm.2ch.c \
		dsp3rom.d16.lpcm.2ch.EQ.16M.c \
		dsp3rom.d16.lpcm.c \
		dsp3rom.d16.lpcm.fudo.c \
		dsp3rom.d16.midi.c \
		dsp3rom.d16.mp3.2ch.c \
		dsp3rom.d16.mp3.2ch.EQ.16M.c \
		dsp3rom.d16.mp3.c \
		dsp3rom.d16.mp3.6ch.c \
		dsp3rom.d16.mp3.mix.c \
		dsp3rom.d16.mp3.jpg.c \
		dsp3rom.d16.spg.c\
		dsp3mp3d.c \
		dsp3mp3p.c \
		dsp3mp3ed.c\
		dsp3rom.d16.nes.2ch.c \
		dsp3rom.d16.nes.c \
		dsp3rom.d16.noise.c \
		dsp3rom.d16.noise.8200.c \
		dsp3rom.d16.spdif.2ch.c \
		dsp3rom.d16.spdif.dts.c \
		dsp3rom.d16.tuner.c \
		dsp3rom.d16.wma.2ch.c \
		dsp3rom.d16.wma.c \
		dsp3rom.d16.ogg.c \
		dsp3oggd.c \

SOURCES_PPCM  = \
		dsp3rom.d16.ppcm.c \

#SOURCES_WMA  = \
#		dsp3rom.d16.wma.2ch.c \
#		dsp3rom.d16.wma.c \

SOURCES_AAC  = \
		dsp3aacd.c \
		dsp3rom.d16.aac.c \

SOURCES_DTS  = \
		dsp3rom.d16.dts.8200.c \
		dsp3rom.d16.dts.8202.c \
		dsp3rom.d16.108.dtscd.c \
		dsp3rom.d16.945.dts.c \
		dsp3rom.d16.dts.spi.8200.c \
		dsp3rom.d16.dts.spi.8202.c \
		dsp3rom.d16.dtscd.c \
		dsp3rom.d16_dts.dts.c \
		dsp3rom.d16.dts.5.1ch.16M.c \
		dsp3rom.d16.raw.dtscd.c \

DEPENDS_C	= \
		$(addprefix MIPS/,$(SOURCES:.c=.d))

DEPENDS_C_PPCM	= \
		$(addprefix MIPS/,$(SOURCES_PPCM:.c=.d))

DEPENDS_C_AAC	= \
		$(addprefix MIPS/,$(SOURCES_AAC:.c=.d))

#DEPENDS_C_WMA	= \
#		$(addprefix MIPS/,$(SOURCES_WMA:.c=.d))

DEPENDS_C_DTS	= \
		$(addprefix MIPS/,$(SOURCES_DTS:.c=.d))

#DEPENDS		= $(DEPENDS_C) $(DEPENDS_C_WMA) $(DEPENDS_C_DTS) &(DEPENDS_C_PPCM) &(DEPENDS_C_AAC)
DEPENDS		= $(DEPENDS_C) $(DEPENDS_C_DTS) &(DEPENDS_C_PPCM) &(DEPENDS_C_AAC)

OBJS    	= $(DEPENDS_C:.d=.o)
OBJS_PPCM	= $(DEPENDS_C_PPCM:.d=.o)
OBJS_AAC	= $(DEPENDS_C_AAC:.d=.o)
#OBJS_WMA	= $(DEPENDS_C_WMA:.d=.o)
OBJS_DTS	= $(DEPENDS_C_DTS:.d=.o)
ASMS		= $(DEPENDS:.d=.s)
DISASMS		= $(DEPENDS:.d=.dis)

.PHONY:		all



#
# main target
#
all:	$(GOAL)



#
# GOAL
#
$(GOAL_PPCM) : $(OBJS_PPCM) force
	@$(XAR) -cr $(GOAL_PPCM) $(OBJS_PPCM)
	@$(ECHO) \"$(GOAL_PPCM) made\"

$(GOAL_AAC) : $(OBJS_AAC) force
	@$(XAR) -cr $(GOAL_AAC) $(OBJS_AAC)
	@$(ECHO) \"$(GOAL_AAC) made\"

#$(GOAL_WMA) : $(OBJS_WMA) force
#	@$(XAR) -cr $(GOAL_WMA) $(OBJS_WMA)
#	@$(ECHO) \"$(GOAL_WMA) made\"

$(GOAL_DTS) : $(OBJS_DTS) force
	@$(XAR) -cr $(GOAL_DTS) $(OBJS_DTS)
	@$(ECHO) \"$(GOAL_DTS) made\"

#$(GOAL): $(OBJS) $(GOAL_WMA) $(GOAL_DTS) $(GOAL_PPCM) $(GOAL_AAC) force
$(GOAL): $(OBJS) $(GOAL_DTS) $(GOAL_PPCM) $(GOAL_AAC) force
	@$(ECHO) \"update library..\"
	@$(XAR) -cr $(GOAL) $(OBJS)
	@$(ECHO) \"$(GOAL) made\"



#
# disassembly
#
%.dis : %.obj
	@$(ECHO) \"disassembling..\"
	@$(XOBJDUMP) --disassemble -j .rom1 --source $< > $@

MIPS/%.dis : %.o
	@$(XOBJDUMP) --source -d --syms $< > $@



#
# building needed files
#
#SOURCES_ALL = $(SOURCES) $(SOURCES_PPCM) $(SOURCES_AAC) $(SOURCES_WMA) $(SOURCES_DTS)
SOURCES_ALL = $(SOURCES) $(SOURCES_PPCM) $(SOURCES_AAC) $(SOURCES_DTS)
$(SOURCES_ALL) : %.c : %.inc

MIPS/%.bin : $(addprefix ../DSP3_SRC/, %)
	@../package/makeim -b $< $@

%.inc : MIPS/%.bin
	@$(FGZIP2) -f $<
	@$(BINOBJ) DSPcode $<.gz $@

dsp3mp3d.inc dsp3mp3p.inc : %.inc : %.bin
	@$(FGZIP2) -f $<
	@$(BINOBJ) DSPcode $<.gz $@

dsp3mp3ed.inc : %.inc : %.bin
	@$(FGZIP2) -f $<
	@$(BINOBJ) DSPcode $<.gz $@

dsp3aacd.inc : %.inc : %.bin
	@$(FGZIP2) -f $<
	@$(BINOBJ) DSPcode $<.gz $@

dsp3oggd.inc : %.inc : %.bin
	@$(FGZIP2) -f $<
	@$(BINOBJ) DSPcode $<.gz $@		

MIPS/%.o : %.c
	@$(ECHO) \"compile $<\"
	@$(XCC) $(CFLAGS_MIPS) -O0 -g0 -c -o $@ $<

sinclude	$(DEPENDS)
