libexec_PROGRAMS = sagarmatha-fallback-mount-helper

sagarmatha_fallback_mount_helper_SOURCES = \
	sagarmatha-fallback-mount-helper.c \
	csd-automount-manager.c \
	csd-automount-manager.h \
	csd-autorun.c \
	csd-autorun.h

sagarmatha_fallback_mount_helper_CPPFLAGS = \
	-I$(top_srcdir)/sagarmatha-settings-daemon		\
	-DSAGARMATHA_SETTINGS_LOCALEDIR=\""$(datadir)/locale"\" \
	$(AM_CPPFLAGS)

sagarmatha_fallback_mount_helper_CFLAGS =	\
	$(SETTINGS_PLUGIN_CFLAGS)	\
	$(SYSTEMD_CFLAGS)		\
	$(AUTOMOUNT_CFLAGS)

sagarmatha_fallback_mount_helper_LDADD =	\
	$(SETTINGS_PLUGIN_LIBS)		\
	$(SYSTEMD_LIBS)			\
	$(AUTOMOUNT_LIBS)		\
	$(top_builddir)/sagarmatha-settings-daemon/libcsd.la

autostartdir = $(datadir)/applications
autostart_in_files = sagarmatha-fallback-mount-helper.desktop.in
autostart_in_in_files = sagarmatha-fallback-mount-helper.desktop.in.in
autostart_DATA = $(autostart_in_files:.desktop.in=.desktop)

$(autostart_in_files): $(autostart_in_in_files)
	@sed -e "s|\@LIBEXECDIR\@|$(libexecdir)|" $< > $@

@INTLTOOL_DESKTOP_RULE@

EXTRA_DIST = $(autostart_in_in_files)

CLEANFILES = $(autostart_DATA) $(autostart_in_files)
