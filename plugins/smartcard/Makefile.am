plugin_name = smartcard

libexec_PROGRAMS = csd-test-smartcard

csd_test_smartcard_SOURCES =	\
	csd-smartcard-manager.h	\
	csd-smartcard-manager.c	\
	csd-smartcard.h         \
	csd-smartcard.c         \
	test-smartcard.c

csd_test_smartcard_CFLAGS =					\
	-I$(top_srcdir)/sagarmatha-settings-daemon			\
	-I$(top_srcdir)/plugins/common				\
	-DSYSCONFDIR=\""$(sysconfdir)"\" \
	-DLIBDIR=\""$(libdir)"\" \
	-DSAGARMATHA_SETTINGS_LOCALEDIR=\""$(datadir)/locale"\"	\
	$(NSS_CFLAGS)						\
	$(PLUGIN_CFLAGS)					\
	$(SETTINGS_PLUGIN_CFLAGS)				\
	$(AM_CFLAGS)

csd_test_smartcard_LDADD =					\
	$(top_builddir)/sagarmatha-settings-daemon/libcsd.la		\
	$(top_builddir)/plugins/common/libcommon.la		\
	$(NSS_LIBS)						\
	$(SETTINGS_PLUGIN_LIBS)

plugin_LTLIBRARIES = \
	libsmartcard.la

libsmartcard_la_SOURCES = \
	csd-smartcard-plugin.h  \
	csd-smartcard-plugin.c  \
	csd-smartcard.h         \
	csd-smartcard.c         \
	csd-smartcard-manager.h \
	csd-smartcard-manager.c

libsmartcard_la_CPPFLAGS = \
	-I$(top_srcdir)/sagarmatha-settings-daemon \
	-DSAGARMATHA_SETTINGS_LOCALEDIR=\""$(datadir)/locale"\" \
	-DSYSCONFDIR=\""$(sysconfdir)"\" \
	-DLIBDIR=\""$(libdir)"\" \
	-DCSD_SMARTCARD_MANAGER_NSS_DB=\""$(NSS_DATABASE)"\" \
	$(AM_CPPFLAGS)

libsmartcard_la_CFLAGS = \
	$(PLUGIN_CFLAGS)	\
	$(SETTINGS_PLUGIN_CFLAGS) \
	$(NSS_CFLAGS)	\
	$(AM_CFLAGS)

libsmartcard_la_LDFLAGS = \
	$(CSD_PLUGIN_LDFLAGS)

libsmartcard_la_LIBADD = \
	$(SETTINGS_PLUGIN_LIBS)	\
	$(NSS_LIBS)

@CSD_INTLTOOL_PLUGIN_RULE@

plugin_in_files = \
	smartcard.sagarmatha-settings-plugin.in

plugin_DATA = $(plugin_in_files:.sagarmatha-settings-plugin.in=.sagarmatha-settings-plugin)

EXTRA_DIST = \
	$(plugin_in_files)

CLEANFILES = \
	$(plugin_DATA)

DISTCLEANFILES = \
	$(plugin_DATA)
