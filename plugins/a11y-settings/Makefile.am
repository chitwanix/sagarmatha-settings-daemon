plugin_name = a11y-settings

libexec_PROGRAMS = csd-test-a11y-settings

csd_test_a11y_settings_SOURCES =	\
	csd-a11y-settings-manager.h	\
	csd-a11y-settings-manager.c	\
	test-a11y-settings.c

csd_test_a11y_settings_CFLAGS =					\
	-I$(top_srcdir)/sagarmatha-settings-daemon			\
	-I$(top_srcdir)/plugins/common				\
	-DSAGARMATHA_SETTINGS_LOCALEDIR=\""$(datadir)/locale"\"	\
	$(PLUGIN_CFLAGS)					\
	$(SETTINGS_PLUGIN_CFLAGS)				\
	$(AM_CFLAGS)

csd_test_a11y_settings_LDADD =					\
	$(top_builddir)/sagarmatha-settings-daemon/libcsd.la		\
	$(top_builddir)/plugins/common/libcommon.la		\
	$(SETTINGS_PLUGIN_LIBS)

plugin_LTLIBRARIES = \
	liba11y-settings.la

liba11y_settings_la_SOURCES = 		\
	csd-a11y-settings-manager.c	\
	csd-a11y-settings-manager.h	\
	csd-a11y-settings-plugin.c	\
	csd-a11y-settings-plugin.h

liba11y_settings_la_CPPFLAGS = \
	-I$(top_srcdir)/sagarmatha-settings-daemon		\
	-DSAGARMATHA_SETTINGS_LOCALEDIR=\""$(datadir)/locale"\" \
	$(AM_CPPFLAGS)

liba11y_settings_la_CFLAGS = \
	$(PLUGIN_CFLAGS)		\
	$(SETTINGS_PLUGIN_CFLAGS)	\
	$(AM_CFLAGS)

liba11y_settings_la_LDFLAGS = 		\
	$(CSD_PLUGIN_LDFLAGS)

liba11y_settings_la_LIBADD  = 		\
	$(SETTINGS_PLUGIN_LIBS)

plugin_in_files = 		\
	a11y-settings.sagarmatha-settings-plugin.in

plugin_DATA = $(plugin_in_files:.sagarmatha-settings-plugin.in=.sagarmatha-settings-plugin)

EXTRA_DIST = 			\
	$(plugin_in_files)

CLEANFILES = 			\
	$(plugin_DATA)

DISTCLEANFILES =		\
	$(plugin_DATA)

@CSD_INTLTOOL_PLUGIN_RULE@

