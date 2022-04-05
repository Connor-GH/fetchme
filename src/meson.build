sources = ['fetchme.c']

executable('fetchme',
           sources,
           c_args: default_cflags,
           dependencies: [dep_pci, dep_xrandr, dep_x11],
           install : true)
