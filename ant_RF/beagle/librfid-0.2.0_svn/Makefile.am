AUTOMAKE_OPTIONS = foreign dist-bzip2 1.6

include $(top_srcdir)/Makefile.flags.am
include rf2/utiles/Variables_Make


SUBDIRS = etc include src

if ENABLE_SPIDEV
SUBDIRS += rf2
endif

if ENABLE_FIRMWARE
else
SUBDIRS += utils
endif

if ENABLE_WIN32
SUBDIRS += win32
endif

EXTRA_DIST = LICENSING librfid.spec openct-cm5121-librfid.patch README.MinGW

$(OBJECTS): libtool
libtool: $(LIBTOOL_DEPS)
	$(SHELL) ./config.status --recheck
