project('Gnoridor' ,'c')
gtkdep = dependency('gtk+-3.0')

add_global_arguments('-std=c99', '-DUNIT_TEST=1', language : 'c')

gnome = import('gnome')
gnresources = gnome.compile_resources('gnoridor-resources', 'src/resources/gnoridor.gresource.xml')

sources_no_main = [
           'src/gnoridor-board.c',
           'src/gnoridor-cell.c',
           'src/callback.c',
           'src/gnoridor-player.c',
           'src/gnoridor-board.h',
           'src/gnoridor-cell.h',
           'src/callback.h',
           'src/gnoridor-player.h',]

sources = sources_no_main
sources += 'src/main.c'


executable('Gnoridor', sources, gnresources,dependencies : gtkdep, install : true)

test_dir = executable('test_direction', 'test/test_direction.c', sources_no_main, gnresources, dependencies : gtkdep)
test('test_direction', test_dir)
