include config.mk
SRCDIR = src

MODULES =
# these source files are essential.
SOURCES = $(SRCDIR)/fetchme.c $(SRCDIR)/modules/color.c

# comment modules out to not build or include them

# if you want to define a custom color instead 
# of a distro-chosen one, you do it here.
# uncomment both lines and choose your color 
# on the second one.
# your options are below.
RED   	=\"\\033[1\;31m\"
GREEN	=\"\\033[1\;32m\"
YELLOW	=\"\\033[1\;33m\"
BLUE 	=\"\\033[1\;34m\"
PURPLE	=\"\\033[1\;35m\"
CYAN	=\"\\033[1\;36m\"
WHITE	=\"\\033[1\;37m\"
ifneq (,$(filter $(CUSTOM_COLOR),Y y))
	MODULES += -DCUSTOM_COLOR
ifneq ($(CUSTOM_COLOR_VALUE), RED)
	MODULES += -DCUSTOM_COLOR_VALUE=$(RED)
else ifeq ($(CUSTOM_COLOR_VALUE), GREEN)
	MODULES += -DCUSTOM_COLOR_VALUE=$(GREEN)
else ifeq ($(CUSTOM_COLOR_VALUE), YELLOW)
	MODULES += -DCUSTOM_COLOR_VALUE=$(YELLOW)
else ifeq ($(CUSTOM_COLOR_VALUE), BLUE)
	MODULES += -DCUSTOM_COLOR_VALUE=$(BLUE)
else ifeq ($(CUSTOM_COLOR_VALUE), PURPLE)
	MODULES += -DCUSTOM_COLOR_VALUE=$(PURPLE)
else ifeq ($(CUSTOM_COLOR_VALUE), CYAN)
	MODULES += -DCUSTOM_COLOR_VALUE=$(CYAN)
else ifeq ($(CUSTOM_COLOR_VALUE), WHITE)
	MODULES += -DCUSTOM_COLOR_VALUE=$(WHITE)
else
	MODULES += -DCUSTOM_COLOR_VALUE=\"\\033[0m\"
endif
endif # CUSTOM_COLOR

# username@hostname
ifneq (,$(filter $(USERNAME_HOSTNAME),Y y))
	MODULES += -DUSERNAME_HOSTNAME
	SOURCES += $(SRCDIR)/modules/username_at_hostname.c
endif

# distro info (Distro name, architecture)
ifneq (,$(filter $(DISTRO),Y y))
	MODULES += -DDISTRO
	SOURCES += $(SRCDIR)/modules/distro.c
endif

# kernel version
ifneq (,$(filter $(KERNEL),Y y))
	MODULES += -DKERNEL
	SOURCES += $(SRCDIR)/modules/kernel.c
endif

# uptime information (hours, minutes)
ifneq (,$(filter $(UPTIME),Y y))
	MODULES += -DUPTIME
	SOURCES += $(SRCDIR)/modules/uptime_info.c
endif

# package count from package manager
ifneq (,$(filter $(PACKAGE),Y y))
	MODULES += -DPACKAGE
	SOURCES += $(SRCDIR)/modules/package_count.c
endif

# the shell the user is currently using

ifneq (,$(filter $(_SHELL),Y y))
	MODULES += -DSHELL
	SOURCES += $(SRCDIR)/modules/shell.c
endif

# resolution the screen is using. detected from libx11. 
# resolution does not work on TTY.
ifneq (,$(filter $(RESOLUTION),Y y))
	MODULES += -DRESOLUTION
	SOURCES += $(SRCDIR)/modules/resolution.c
	M_LFLAGS += -lX11
# refresh rate the screen is using. detected from libxrandr.
# refresh rate is dependant on the resolution module, so 
# you will need both if you want refresh rate.
# the resolution module is not dependant on refresh rate though, 
# so you can use it by itself. refresh rate does not work on TTY.
ifneq (,$(filter $(REFRESH_RATE),Y y))
	MODULES += -DREFRESH_RATE
	SOURCES += $(SRCDIR)/modules/refresh_rate.c
	M_LFLAGS += -lXrandr
endif
endif # RESOLUTION

# window manager detection. detects the window manager of 
## KDE, for example, as KWin.
ifneq (,$(filter $(WM),Y y))
	MODULES += -DWM
	SOURCES += $(SRCDIR)/modules/wm.c
endif

# what terminal emulator is in $TERM.
ifneq (,$(filter $(TERMINAL),Y y))
	MODULES += -DTERMINAL
	SOURCES += $(SRCDIR)/modules/terminal.c
endif

# what cpu the user has.
ifneq (,$(filter $(CPU),Y y))
	MODULES += -DCPU
	SOURCES += $(SRCDIR)/modules/cpu_info.c
# additional cpu settings. requires the CPU module.
ifneq (,$(filter $(CPU_THREADS),Y y))
	MODULES += -DCPU_THREADS
endif
# temperature is currently very experimental and left off by default.
ifneq (,$(filter $(CPU_TEMP),Y y))
	MODULES += -DCPU_TEMP
endif
ifneq (,$(filter $(CPU_FREQUENCY),Y y))
	MODULES += -DCPU_FREQUENCY
endif
endif # CPU

# GPU name and (potentially) die codename.
# requires libpci. if you do not want GPU detection, comment
# out both lines.
ifneq (,$(filter $(GPU),Y y))
	MODULES += -DGPU
	SOURCES += $(SRCDIR)/modules/gpu_info.c
	M_LFLAGS += -lpci
endif

# memory usage.
ifneq (,$(filter $(MEMORY),Y y))
	MODULES += -DMEMORY
	SOURCES += $(SRCDIR)/modules/memory_info.c
# memory usage in percent. requires the MEMORY module.
ifneq (,$(filter $(MEMORY_PERCENT),Y y))
	MODULES += -DMEMORY_PERCENT
endif
endif # MEMORY

# disk usage in MB, GB, or TB if permitted.
ifneq (,$(filter $(DISK),Y y))
	MODULES += -DDISK
	SOURCES += $(SRCDIR)/modules/disk.c
# disk usage in percent. requires the DISK module.
ifneq (,$(filter $(DISK_PERCENT),Y y))
	MODULES += -DDISK_PERCENT
endif
endif # DISK
