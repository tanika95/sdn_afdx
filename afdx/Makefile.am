include ../../../Make.vars

CONFIGURE_DEPENCIES = $(srcdir)/Makefile.am

EXTRA_DIST =\
	meta.json

pkglib_LTLIBRARIES =		\
	afdx.la

afdx_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(top_srcdir)/src/nox
afdx_la_SOURCES =       afdx.cc \
			vl.cc vl.hh \
			network.cc network.hh \
			parametrs.cc parametrs.hh
afdx_la_LDFLAGS = -module -export-dynamic

NOX_RUNTIMEFILES = meta.json

all-local: nox-all-local
clean-local: nox-clean-local
install-exec-hook: nox-install-local
