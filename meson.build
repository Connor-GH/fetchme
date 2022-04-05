project('fetchme-easy-C', 'c',
  version : '0.1.0',
  license : 'GPL-3.0-or-later',
  default_options : ['warning_level=3'])

default_cflags = []

# Dependencies
dep_xrandr = dependency('xrandr', version: '>= 1.0')
dep_x11 = dependency('x11', version: '>= 1.0')
dep_pci = dependency('libpci')

# Source directory
subdir('src')
