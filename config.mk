# fetchme's config.
# options can be turned on with either
# `Y' or `y'. to deselect an option, 
# comment it out.

# to set a custom color, 
# uncomment both CUSTOM_COLOR
# and CUSTOM_COLOR_VALUE
# M_CUSTOM_COLOR=y
# options are: RED,GREEN,YELLOW,BLUE,PURPLE,CYAN,WHITE
# M_CUSTOM_COLOR_VALUE=CYAN

M_USERNAME_HOSTNAME=y

M_DISTRO=y

M_KERNEL=y

M_UPTIME=y

# Off by default.
# Currently only works
# with pacman-based
# distros and 
# portage-based
# distros.
# M_PACKAGE=y

M_SHELL=y

M_RESOLUTION=y

M_REFRESH_RATE=y

M_WM=y

M_TERMINAL=y

# any option associated with CPU 
# needs to have CPU=y
M_CPU=y
M_CPU_THREADS=y
# commented out by default since 
# it's **experimental**
# M_CPU_TEMP=y
M_CPU_FREQUENCY=y

M_GPU=y

# any option associated with MEMORY
# needs to have MEMORY=y
M_MEMORY=y
M_MEMORY_PERCENT=y

# any option associated with DISK
# needs to have DISK=y
M_DISK=y
M_DISK_PERCENT=y
