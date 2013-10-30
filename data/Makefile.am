NULL =

apidir = $(includedir)/sagarmatha-settings-daemon-$(CSD_API_VERSION)/sagarmatha-settings-daemon
api_DATA = csd-enums.h

gsettings_ENUM_NAMESPACE = org.sagarmatha.settings-daemon
gsettings_ENUM_FILES = $(top_srcdir)/data/$(api_DATA)

gsettings_SCHEMAS =							\
	org.sagarmatha.settings-daemon.peripherals.gschema.xml		\
	org.sagarmatha.settings-daemon.plugins.gschema.xml			\
	org.sagarmatha.settings-daemon.plugins.keyboard.gschema.xml		\
	org.sagarmatha.settings-daemon.plugins.power.gschema.xml		\
	org.sagarmatha.settings-daemon.plugins.color.gschema.xml		\
	org.sagarmatha.settings-daemon.plugins.media-keys.gschema.xml	\
	org.sagarmatha.settings-daemon.plugins.xsettings.gschema.xml		\
	org.sagarmatha.settings-daemon.plugins.housekeeping.gschema.xml	\
	org.sagarmatha.settings-daemon.plugins.print-notifications.gschema.xml	\
	org.sagarmatha.settings-daemon.plugins.xrandr.gschema.xml		\
	org.sagarmatha.settings-daemon.plugins.orientation.gschema.xml	\
    org.sagarmatha.settings-daemon.plugins.background.gschema.xml

@INTLTOOL_XML_NOMERGE_RULE@

@GSETTINGS_RULES@

@INTLTOOL_DESKTOP_RULE@
desktopdir = $(datadir)/applications
desktop_in_files = sagarmatha-settings-daemon.desktop.in.in
desktop_DATA = $(desktop_in_files:.desktop.in.in=.desktop)

sagarmatha-settings-daemon.desktop.in: sagarmatha-settings-daemon.desktop.in.in
	$(AM_V_GEN) sed -e "s|\@libexecdir\@|$(libexecdir)|" $< > $@.tmp && mv $@.tmp $@

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = sagarmatha-settings-daemon.pc

@INTLTOOL_XML_NOMERGE_RULE@

man_MANS = sagarmatha-settings-daemon.1

dbusservice_in_files = org.freedesktop.IBus.service.in

EXTRA_DIST = 					\
	$(man_MANS)				\
	$(convert_DATA)				\
	$(gsettings_SCHEMAS:.xml=.xml.in.in)	\
	$(desktop_in_files)			\
	$(gsettings_ENUM_FILES)			\
	sagarmatha-settings-daemon.pc.in		\
	$(api_DATA)				\
	$(dbusservice_in_files)			\
	$(NULL)

DISTCLEANFILES = 			\
	$(gsettings_SCHEMAS)		\
	$(desktop_DATA)			\
	sagarmatha-settings-daemon.desktop.in \
	$(NULL)

MAINTAINERCLEANFILES =			\
	*~				\
	Makefile.in			\
	$(gsettings_SCHEMAS:.xml=.valid)

