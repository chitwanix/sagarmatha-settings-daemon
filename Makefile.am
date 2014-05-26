NULL =

INCLUDES = \
	-DDATADIR=\""$(datadir)"\"				\
	-DCINNAMON_SETTINGS_LOCALEDIR=\""$(datadir)/locale"\"	\
	-DLIBEXECDIR=\""$(libexecdir)"\" 			\
	-DCINNAMON_SETTINGS_PLUGINDIR=\""$(plugindir)"\"		\
	$(WARN_CFLAGS)						\
	$(DISABLE_DEPRECATED_CFLAGS)				\
	$(SETTINGS_DAEMON_CFLAGS)				\
	$(LIBNOTIFY_CFLAGS)					\
	$(GNOME_DESKTOP_CFLAGS)					\
	$(SYSTEMD_CFLAGS)					\
	$(NULL)

privlibdir = $(pkglibdir)-$(CSD_API_VERSION)

privlib_LTLIBRARIES =		\
	libcsd.la		\
	$(NULL)

libcsd_la_SOURCES =		\
	sagarmatha-settings-profile.c	\
	sagarmatha-settings-profile.h	\
	sagarmatha-settings-session.c	\
	sagarmatha-settings-session.h	\
	$(NULL)

libcsd_la_CPPFLAGS = 		\
	$(DISABLE_DEPRECATED_CFLAGS)	\
	$(NULL)

libcsd_la_CFLAGS =		\
	$(NULL)

libcsd_la_LIBADD =		\
	$(SYSTEMD_LIBS)		\
	$(GIOUNIX_LIBS)		\
	$(NULL)

libcsd_la_LDFLAGS =		\
	-export-dynamic		\
	-avoid-version		\
	-no-undefined		\
	$(NULL)

csddir = $(libexecdir)

csd_PROGRAMS = \
	sagarmatha-settings-daemon

apidir   = $(includedir)/sagarmatha-settings-daemon-$(CSD_API_VERSION)/sagarmatha-settings-daemon
api_DATA = 				\
	sagarmatha-settings-plugin.h

sagarmatha_settings_daemon_SOURCES =		\
	main.c				\
	sagarmatha-settings-manager.c	\
	sagarmatha-settings-manager.h	\
	sagarmatha-settings-plugin.c		\
	sagarmatha-settings-plugin.h		\
	sagarmatha-settings-plugin-info.c	\
	sagarmatha-settings-plugin-info.h	\
	sagarmatha-settings-module.c		\
	sagarmatha-settings-module.h		\
	$(NULL)

sagarmatha_settings_daemon_CPPFLAGS = \
	$(AM_CPPFLAGS)

sagarmatha_settings_daemon_CFLAGS = 		\
	$(AM_CFLAGS)

sagarmatha_settings_daemon_LDFLAGS = 	\
	$(AM_LDFLAGS)

sagarmatha_settings_daemon_LDADD = 		\
	libcsd.la		\
	$(SETTINGS_DAEMON_LIBS)		\
	$(LIBNOTIFY_LIBS)		\
	$(GNOME_DESKTOP_LIBS)		\
	$(NULL)

# vim: ts=8
