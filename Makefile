#
# Makefile
#
# DVD
#

PATH		:= $(PATH) .
VPATH		= DSP3 MIPS IR_VFD IOP SETUP

.SUFFIXES:
.PHONY:		force 

sinclude	Makefile.utl

LIBDIR		= mipsel-elf
LIBPPCMDIR  = mipsel-elf-ppcm
LIBAACDIR   = mipsel-elf-aac
#LIBWMADIR   = mipsel-elf-wma
LIBDTSDIR   = mipsel-elf-dts
LIBSRVDIR	= srv-elf
GOAL  		= romL.obj
LDSCRIPT	= dvdL.ld
CFLAGS_ENDIAN	= -DLITTLE_ENDIAN

INIT0		= MIPS/init0.o
ROMINIT0	= MIPS/rominit.o
ROMFINIT0	= MIPS/romfinit.o
CRT0		= MIPS/crt0.o
BOOT_FLASH 	= MIPS/boot_flashs.o


INCLUDE_DIR	= -I. -Ih/ -Iosd/ -Isetup/  -Iemu/ -Inav/ -Iauth/ -Iservo/ -Ichinese/ -Iir_vfd/ -Ipeif/ -Igame/ -Isystem/ -Iauddrv/

#
# generic flags
#

#
# CFLAGS_COMPILE
#
#
#  __EMU__ / __BORLANDC__
#  used to define atapi interface
#
#  VIDEO_ONLY
#  disable audio functionality
#
#  SIMULATION/EMULATION/FINALSYS
#  setup environment according to debugging configuration
#
#  SIMULATION_FAST
#  accelerate some parameter during SIMULATION (or testing)
#
CFLAGS_SUPPORT	= -D__EMU__ -DFINALSYS
CFLAGS_SIM	= 
CFLAGS_COMPILE	= $(CFLAGS_SUPPORT) $(CFLAGS_SIM)


#
# CFLAGS_CPPX
# for dvdL.ldp parsing
#
CFLAGS_CPPX	= $(CFLAGS_COMPILE) -I. -Ih -x c++


#
# ld related flags (LDFLAGS)
#
LIBRARIES	=
LDFLAGS_LIB	= 
LDFLAGS		= -nostartfiles -T $(LDSCRIPT) -L$(LIBDIR) -L$(LIBPPCMDIR) -L$(LIBAACDIR) -L$(LIBDTSDIR) -L$(LIBSRVDIR) $(LDFLAGS_LIB) \
	   	--cref -Wl,--gc-sections,--sort-common,-Map,$*.map
#	   	--cref -Wl,-Map,$*.map
#		-Wl,--sort-common


#
# Sources
#
SOURCES_AUD	= \
		dsp3_config.c\
		audif.c\
		dsp3_if.c\
		dsp3_intr.c \

SOURCES_TV	= 

SOURCES_IOP	= \
		iop.c \
		ioprom.c \

SOURCES_KERN	= \
		kinf.c \
		kfptr.c \
		kernel.c

SOURCES_NAV	= \
		ninf.c\

SOURCES_CUST = \
		cust_nav.c\

SOURCES		= \
		sysmain2.c license.c \
		dvd_vr_func.c \
		zoomfact.c \
		membuf.c \
		membufv.c \
		emuio.c \
		sound.c \
		title.c \
		databuf.c \
		OSDShowFont.c\
		font_offset.c\
		read.c\
		prog.c\
		setup.c\
		setup_str.c\
		setup_ui1.c\
		disp.c\
		book.c\
		search.c\
		browse_func.c\
		safe.c\
		UartComm.c\
		score.c\
		double_title.c\
		osdfont_decompress.c\
		ircode.c\
		radio.c\
		ampvol.c\
		audctrl.c\
		gpio.c \
		userlogo.c\
		virtual_keyboard.c\
		LanguageUtil.c\
		cdplayer.c \
		c_i2c.c \
		periphGUI.c \
		TVGApp.c \
		atapi_.c \
		touch_panel.c\
		gps_GUI.c\
		flash_if.c\
		$(SOURCES_IOP) \
		$(SOURCES_KERN) \
		$(SOURCES_NAV) \
		$(SOURCES_AUD) \
		$(SOURCES_TV) \
		$(SOURCES_CUST) \
		
SOURCES_S	= intdrv.S
		
DEPENDS_C	= \
		$(addprefix MIPS/,$(SOURCES:.c=.d))

DEPENDS_S	= \
		$(addprefix MIPS/,$(SOURCES_S:.S=.d))

DEPENDS		= $(DEPENDS_C) $(DEPENDS_S)

OBJS		= $(DEPENDS:.d=.o)


#
# main target
#
all: $(GOAL)
	@$(CHKSUM) romL.bin 64
	@$(XB2) 0x70 romL.bin rom.bin
	@$(CHKSUM) rom.bin 32
#	@$(MODUAL) boot_flash.bin rom.bin
	@$(ECHO) \"all made\"	


#
# LIBRARY
# libdrv.a
#
SOURCES_DRVLIB	= \
		adv7176.c \
		sp711.c \
		cs8403a.c

DEPS_DRVLIB	= $(addprefix MIPS/,$(SOURCES_DRVLIB:.c=.d))
OBJS_DRVLIB	= $(DEPS_DRVLIB:.d=.o)

libdrv.a : $(OBJS_DRVLIB)
	$(XAR) -cr $@ $(OBJS_DRVLIB)

sinclude $(DEPS_DRVLIB)


#
# LIBRARY
# libmon.a
#
#SOURCES_MONLIB = \
#		dump.c \
#		monitor.c 

#DEPS_MONLIB	= $(addprefix MIPS/,$(SOURCES_MONLIB:.c=.d))
#OBJS_MONLIB	= $(DEPS_MONLIB:.d=.o)

libmon.a : $(OBJS_MONLIB)
	$(XAR) -cr $@ $(OBJS_MONLIB)

#sinclude $(DEPS_MONLIB)


#
# dvdL.ld
#
dvdL.ld: dvdL.ldp force
	@$(ECHO) \"generate linker script\"
	@$(CPP) $(CFLAGS_CPPX) dvdL.ldp > dvdL.ld

#
# GOAL
#
$(GOAL): %.obj: $(LIBRARIES) $(OBJS) $(INIT0) $(CRT0) $(ROMINIT0) $(BOOT_FLASH) dvdL.ld
	@$(ECHO) \"linking..\"
	@$(XCC) $(CFLAGS_MIPS) -o $@ $(INIT0) $(OBJS) $(CRT0) $(ROMINIT0) $(BOOT_FLASH) $(LDFLAGS)
	@$(ECHO) \"dumping..\"
	@$(XOBJDUMP) -j .rom1 -s $@ > $*.dump
	@$(XOBJDUMP) -j .ram1 -s $@ >> $*.dump
	@$(XOBJDUMP) -j .rom2 -s $@ >> $*.dump
	@$(XOBJDUMP) -j .rom3 -s $@ >> rom3.dump
#=======================================================================
#	@$(XOBJDUMP) -j .ramflash -s $@ >> $*.dump
#	@$(ECHO) \"packaging..\"
#	@$(DUMP2BIN) $*.dump $*.bin
#=======================================================================	
#	@$(XOBJDUMP) -j .ramflash -s $@ > flash.dump
	@$(XOBJDUMP) -j .drv_iop -s $@ > iop.dump
	@$(XOBJDUMP) -j .drv_iop_rst -s $@ > iop_rst.dump
	@$(XOBJDUMP) -j .drv_dvd -s $@ > dvd.dump
	@$(XOBJDUMP) -j .ramdrv1 -s $@ > mpeg.dump
	@$(XOBJDUMP) -j .ramdrv2 -s $@ > jpeg.dump
	@$(XOBJDUMP) -j .drv_ap1 -s $@ > ap1.dump
	@$(XOBJDUMP) -j .drv_cdrom -s $@ > cdrom.dump
	@$(XOBJDUMP) -j .boot_flash -s $@ > boot_flash.dump
	@$(XOBJDUMP) -j .drv_srvdp -s $@ > srvdsp.dump
	@$(XOBJDUMP) -j .drv_ap2 -s $@ > ap2.dump
	@$(XOBJDUMP) -j .drv_ap3 -s $@ > ap3.dump
	@$(XOBJDUMP) -j .drv_free -s $@ > free.dump
	@$(XOBJDUMP) -j .drv_dvb -s $@ > dvb.dump
	@$(XOBJDUMP) -j .drv_other -s $@ > drv_other.dump
	@$(XOBJDUMP) -j .drv_mp4 -s $@ > mp4.dump
	@$(XOBJDUMP) -j .drv_wma -s $@ > wma.dump
#=======================================================================	
#	@$(DUMP2BIN) flash.dump flash.bin
#	@$(FGZIP2) -c flash.bin > flash.rz

	@$(DUMP2BIN) iop.dump iop.bin
	@$(FGZIP2) -f iop.bin 

	@$(DUMP2BIN) iop_rst.dump iop_rst.bin
	@$(FGZIP2) -f iop_rst.bin

	@$(DUMP2BIN) dvd.dump dvd.bin
	@$(FGZIP2) -f dvd.bin

	@$(DUMP2BIN) mpeg.dump mpeg.bin
	@$(FGZIP2) -f mpeg.bin

	@$(DUMP2BIN) jpeg.dump jpeg.bin
	@$(FGZIP2) -f jpeg.bin

	@$(DUMP2BIN) ap1.dump ap1.bin
	@$(FGZIP2) -f ap1.bin 

	@$(DUMP2BIN) cdrom.dump cdrom.bin
	@$(FGZIP2) -f cdrom.bin

	@$(DUMP2BIN) srvdsp.dump srvdsp.bin
	@$(FGZIP2) -f srvdsp.bin

	@$(DUMP2BIN) ap2.dump ap2.bin
	@$(FGZIP2) -f ap2.bin

	@$(DUMP2BIN) ap3.dump ap3.bin
	@$(FGZIP2) -f ap3.bin

	@$(DUMP2BIN) free.dump free.bin
	@$(FGZIP2) -f free.bin

	@$(DUMP2BIN) dvb.dump dvb.bin
	@$(FGZIP2) -f dvb.bin

	@$(DUMP2BIN) drv_other.dump drv_other.bin
	@$(FGZIP2) -f drv_other.bin

	@$(DUMP2BIN) mp4.dump mp4.bin
	@$(FGZIP2) -f mp4.bin

	@$(DUMP2BIN) wma.dump wma.bin
	@$(FGZIP2) -f wma.bin
	
	@$(DUMP2BIN) boot_flash.dump boot_flash.bin

#	@$(XOBJDUMP) --disassemble -j .boot_flash --source romL.obj > boot_flash.dis
#	@$(XOBJDUMP) --disassemble -j .drv_ap1 --source romL.obj > drv_ap1.dis
#	@$(XOBJDUMP) --disassemble -j .ramdrv1 --source romL.obj > ramdrv1.dis
#	@$(XOBJDUMP) --disassemble -j .ramdrv2 --source romL.obj > ramdrv2.dis
#	@$(XOBJDUMP) --disassemble -j .drv_dvd --source romL.obj > drv_dvd.dis
#	@$(XOBJDUMP) --disassemble -j .drv_cdrom --source romL.obj > drv_cdrom.dis
#	@$(XOBJDUMP) --disassemble -j .drv_iop --source romL.obj > drv_iop.dis
#	@$(XOBJDUMP) --disassemble -j .drv_iop_rst --source romL.obj > drv_iop_rst.dis

#=======================================================================	
	@$(ECHO) \"packaging..\"
	@$(DUMP2BIN) $*.dump $*.bin
	@$(DUMP2BIN) rom3.dump rom3.bin
#=======================================================================	
	@$(MODUAL) $*.bin dvd.bin.gz mpeg.bin.gz jpeg.bin.gz ap1.bin.gz cdrom.bin.gz iop.bin.gz iop_rst.bin.gz drv_other.bin.gz srvdsp.bin.gz ap2.bin.gz ap3.bin.gz free.bin.gz rom3.bin mp4.bin.gz wma.bin.gz dvb.bin.gz


%.dis : %.obj
	@$(ECHO) \"disassembling..\"
	@$(XOBJDUMP) --disassemble -j .rom1 --source $< > $@
	@$(XOBJDUMP) --disassemble -j .drv_dvd --source $< >> $@
	@$(XOBJDUMP) --disassemble -j .drv_srvdp --source $< >> $@
	@$(XOBJDUMP) --disassemble -j .drv_cdrom --source $< >> $@
	@$(XOBJDUMP) --disassemble -j .drv_ap1 --source $< >> $@
	@$(XOBJDUMP) --disassemble -j .drv_ap2 --source $< >> $@
	@$(XOBJDUMP) --disassemble -j .drv_ap3 --source $< >> $@
	@$(XOBJDUMP) --disassemble -j .drv_free --source $< >> $@
	@$(XOBJDUMP) --disassemble -j .drv_dvb --source $< >> $@
	@$(XOBJDUMP) --disassemble -j .drv_mp4 --source $< >> $@
	@$(XOBJDUMP) --disassemble -j .drv_wma --source $< >> $@
	@$(XOBJDUMP) --disassemble -j .ramdrv1 --source $< >> $@
	@$(XOBJDUMP) --disassemble -j .ramdrv2 --source $< >> $@


#
# special commands.
#
MIPS/init0.o : user_init.h
MIPS/init0.o : init0.S ./h/regmapa.h ./h/sdctrl.h  ./sdram.h 
MIPS/crt0.o : crt0.S ./h/regmapa.h ./h/sdctrl.h ./user_init.h ./sdctrl.inc
MIPS/boot_flashs.o : boot_flashs.S ./h/regdef.h


#ioprom.inc: ioprom.bin
#	$(BINOBJ) IOPcode ioprom.bin > ioprom.inc

MIPS/font_offset.d : osdfont.inc
MIPS/font_offset.o : font_offset.c font.c osdfont.inc
	@$(ECHO) \"compile $<\"
	@$(XCC) $(CFLAGS_MIPS) -O0 -g0 -c -o $@ $<

MIPS/osdfont_decompress.d : osdfont.inc
MIPS/osdfont_decompress.o : osdfont_decompress.c font.c font_offset.c osdfont.inc
	@$(ECHO) \"compile $<\"
	@$(XCC) $(CFLAGS_MIPS) -O0 -g0 -c -o $@ $<

osdfont.inc: osdfont.bin
	@$(FGZIP2) -f $< 
	@$(BINOBJ) OSDfontbin $<.gz osdfont.inc

osdfont.bin: user_init.h font_ori.c font_traditional.c font_konka.c icon.c
	@$(FONT_PARSER)


ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),tar)
ifneq ($(MAKECMDGOALS),bak)
sinclude	$(DEPENDS)
endif
endif
endif


