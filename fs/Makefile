#
# fs/Makefile
#

sinclude	../Makefile.sutl
GOAL		= libfs.a
INCLUDE_DIR	= -I. -I../ -I../h -I../setup -I../auth -I../ir_vfd -I../emu/ -I../nav/

#
# CFLAGS_COMPILE
#
CFLAGS_SUPPORT	=
CFLAGS_SIM	= 
CFLAGS_COMPILE	= $(CFLAGS_SUPPORT) $(CFLAGS_SIM)


#
# Sources
#
SOURCES	= \
		fsGUI.c\
		fsGUIX.c\
		fsGUI_util.c\
		fsGUIShowFont.c \
		fs_nav_upgrade.c\
		fs_file_ext_info_tab.c\
		DRM_UI.c \
		Subtitle.c\
		ShowMp4OSDText.c\
		
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


