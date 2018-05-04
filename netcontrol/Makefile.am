include ../../../Make.vars

CONFIGURE_DEPENCIES = $(srcdir)/Makefile.am

EXTRA_DIST =\
	meta.json

pkglib_LTLIBRARIES =		\
	netcontrol.la

netcontrol_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(top_srcdir)/src/nox
netcontrol_la_SOURCES =       netcontrol.cc \
			vl.cc vl.hh \
			vlset.cc vlset.hh \
			network.cc network.hh \
			parametrs.cc parametrs.hh \
			settings.cc settings.hh \
			algorithm.cc algorithm.hh \
			topology.cc topology.hh \
			host.cc host.hh

netcontrol_la_LDFLAGS = -module -export-dynamic

NOX_RUNTIMEFILES = meta.json

all-local: nox-all-local
clean-local: nox-clean-local
install-exec-hook: nox-install-local
