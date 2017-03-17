project('Gnoridor' ,'c')
gtkdep = dependency('gtk+-3.0')

sources = ['src/main.c',
           'src/gnoridor-board.c',
           'src/gnoridor-cell.c',
           'src/callback.c',
           'src/gnoridor-player.c',
           'src/gnoridor-resources.c',
           'src/gnoridor-board.h',
           'src/gnoridor-cell.h',
           'src/callback.h',
           'src/gnoridor-player.h',]


executable('Gnoridor', sources ,dependencies : gtkdep)