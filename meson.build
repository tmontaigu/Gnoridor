project('Gnoridor' ,'c')
gtkdep = dependency('gtk+-3.0')

add_global_arguments('-std=c99', language : 'c')

gnome = import('gnome')
gnresources = gnome.compile_resources('gnoridor-resources', 'src/resources/gnoridor.gresource.xml')

sources = ['src/main.c',
           'src/gnoridor-board.c',
           'src/gnoridor-cell.c',
           'src/callback.c',
           'src/gnoridor-player.c',
           'src/gnoridor-board.h',
           'src/gnoridor-cell.h',
           'src/callback.h',
           'src/gnoridor-player.h',]


executable('Gnoridor', sources, gnresources,dependencies : gtkdep)
