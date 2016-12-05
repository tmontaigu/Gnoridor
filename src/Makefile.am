bin_PROGRAMS = gnoridor


#TODO Find a way to generate this a compile time
#gnoridor-resources.c:
#	 glib-compile-resources resources/gnoridor.gresource.xml --target=gnoridor-resources.c --generate-source


gnoridor_SOURCES = main.c \
		   gnoridor-board.c \
		   gnoridor-cell.c \
		   callback.c \
		   gnoridor-player.c \
		   gnoridor-resources.c \
	   	   gnoridor-board.h \
		   gnoridor-cell.h \
		   callback.h \
		   gnoridor-player.h


gnoridor_CFLAGS = $(GNORIDOR_CFLAGS)

gnoridor_LDADD = $(GNORIDOR_LIBS)




-include $(top_srcdir)/git.mk
