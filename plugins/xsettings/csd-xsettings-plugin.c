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

#include "config.h"

#include <glib/gi18n-lib.h>
#include <gmodule.h>

#include "sagarmatha-settings-plugin.h"
#include "csd-xsettings-plugin.h"
#include "csd-xsettings-manager.h"

struct SagarmathaSettingsXSettingsPluginPrivate {
        SagarmathaSettingsXSettingsManager *manager;
};

#define SAGARMATHA_XSETTINGS_PLUGIN_GET_PRIVATE(object) (G_TYPE_INSTANCE_GET_PRIVATE ((object), SAGARMATHA_TYPE_XSETTINGS_PLUGIN, SagarmathaSettingsXSettingsPluginPrivate))

SAGARMATHA_SETTINGS_PLUGIN_REGISTER (SagarmathaSettingsXSettingsPlugin, sagarmatha_xsettings_plugin)

static void
sagarmatha_xsettings_plugin_init (SagarmathaSettingsXSettingsPlugin *plugin)
{
        plugin->priv = SAGARMATHA_XSETTINGS_PLUGIN_GET_PRIVATE (plugin);

        g_debug ("SagarmathaSettingsXSettingsPlugin initializing");

        plugin->priv->manager = sagarmatha_xsettings_manager_new ();
}

static void
sagarmatha_xsettings_plugin_finalize (GObject *object)
{
        SagarmathaSettingsXSettingsPlugin *plugin;

        g_return_if_fail (object != NULL);
        g_return_if_fail (SAGARMATHA_IS_XSETTINGS_PLUGIN (object));

        g_debug ("SagarmathaSettingsXSettingsPlugin finalizing");

        plugin = SAGARMATHA_XSETTINGS_PLUGIN (object);

        g_return_if_fail (plugin->priv != NULL);

        if (plugin->priv->manager != NULL) {
                g_object_unref (plugin->priv->manager);
        }

        G_OBJECT_CLASS (sagarmatha_xsettings_plugin_parent_class)->finalize (object);
}

static void
impl_activate (SagarmathaSettingsPlugin *plugin)
{
        gboolean res;
        GError  *error;

        g_debug ("Activating xsettings plugin");

        error = NULL;
        res = sagarmatha_xsettings_manager_start (SAGARMATHA_XSETTINGS_PLUGIN (plugin)->priv->manager, &error);
        if (! res) {
                g_warning ("Unable to start xsettings manager: %s", error->message);
                g_error_free (error);
        }
}

static void
impl_deactivate (SagarmathaSettingsPlugin *plugin)
{
        g_debug ("Deactivating xsettings plugin");
        sagarmatha_xsettings_manager_stop (SAGARMATHA_XSETTINGS_PLUGIN (plugin)->priv->manager);
}

static void
sagarmatha_xsettings_plugin_class_init (SagarmathaSettingsXSettingsPluginClass *klass)
{
        GObjectClass             *object_class = G_OBJECT_CLASS (klass);
        SagarmathaSettingsPluginClass *plugin_class = SAGARMATHA_SETTINGS_PLUGIN_CLASS (klass);

        object_class->finalize = sagarmatha_xsettings_plugin_finalize;

        plugin_class->activate = impl_activate;
        plugin_class->deactivate = impl_deactivate;

        g_type_class_add_private (klass, sizeof (SagarmathaSettingsXSettingsPluginPrivate));
}
