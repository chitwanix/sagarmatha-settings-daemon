/* -*- Mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2007 William Jon McCann <mccann@jhu.edu>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street - Suite 500, Boston, MA 02110-1335, USA.
 *
 */

#ifndef __SAGARMATHA_XSETTINGS_PLUGIN_H__
#define __SAGARMATHA_XSETTINGS_PLUGIN_H__

#include <glib.h>
#include <glib-object.h>
#include <gmodule.h>

#include "sagarmatha-settings-plugin.h"

G_BEGIN_DECLS

#define SAGARMATHA_TYPE_XSETTINGS_PLUGIN                (sagarmatha_xsettings_plugin_get_type ())
#define SAGARMATHA_XSETTINGS_PLUGIN(o)                  (G_TYPE_CHECK_INSTANCE_CAST ((o), SAGARMATHA_TYPE_XSETTINGS_PLUGIN, SagarmathaSettingsXSettingsPlugin))
#define SAGARMATHA_XSETTINGS_PLUGIN_CLASS(k)            (G_TYPE_CHECK_CLASS_CAST((k), SAGARMATHA_TYPE_XSETTINGS_PLUGIN, SagarmathaSettingsXSettingsPluginClass))
#define SAGARMATHA_IS_XSETTINGS_PLUGIN(o)               (G_TYPE_CHECK_INSTANCE_TYPE ((o), SAGARMATHA_TYPE_XSETTINGS_PLUGIN))
#define SAGARMATHA_IS_XSETTINGS_PLUGIN_CLASS(k)         (G_TYPE_CHECK_CLASS_TYPE ((k), SAGARMATHA_TYPE_XSETTINGS_PLUGIN))
#define SAGARMATHA_XSETTINGS_PLUGIN_GET_CLASS(o)        (G_TYPE_INSTANCE_GET_CLASS ((o), SAGARMATHA_TYPE_XSETTINGS_PLUGIN, SagarmathaSettingsXSettingsPluginClass))

typedef struct SagarmathaSettingsXSettingsPluginPrivate SagarmathaSettingsXSettingsPluginPrivate;

typedef struct
{
        SagarmathaSettingsPlugin          parent;
        SagarmathaSettingsXSettingsPluginPrivate *priv;
} SagarmathaSettingsXSettingsPlugin;

typedef struct
{
        SagarmathaSettingsPluginClass parent_class;
} SagarmathaSettingsXSettingsPluginClass;

GType   sagarmatha_xsettings_plugin_get_type            (void) G_GNUC_CONST;

/* All the plugins must implement this function */
G_MODULE_EXPORT GType register_sagarmatha_settings_plugin (GTypeModule *module);

G_END_DECLS

#endif /* __SAGARMATHA_XSETTINGS_PLUGIN_H__ */
