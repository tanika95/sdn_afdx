include ../../../Make.vars

CONFIGURE_DEPENCIES = $(srcdir)/Makefile.am

EXTRA_DIST =\
	meta.json

pkglib_LTLIBRARIES =		\
	netcontrol.la

netcontrol_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(top_srcdir)/src/nox
netcontrol_la_SOURCES = Algorithm.cc Algorithm.hh \
			Config.cc Config.hh \
			Host.cc Host.hh \
			Netcontrol.cc Netcontrol.hh\
			Network.cc Network.hh \
			Settings.cc Settings.hh \
			Sla.cc Sla.hh \
			Switch.cc Switch.hh \
			Topology.cc Topology.hh \
			Vl.cc Vl.hh


netcontrol_la_LDFLAGS = -module -export-dynamic

NOX_RUNTIMEFILES = meta.json

all-local: nox-all-local
clean-local: nox-clean-local
install-exec-hook: nox-install-local
