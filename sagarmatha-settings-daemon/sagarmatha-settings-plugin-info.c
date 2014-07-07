/* -*- Mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2007      William Jon McCann <mccann@jhu.edu>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Suite 500,
 * Boston, MA 02110-1335, USA.
 */

#include "config.h"

#include <string.h>

#include <glib.h>
#include <glib/gi18n.h>
#include <gmodule.h>
#include <gio/gio.h>

#include "sagarmatha-settings-plugin-info.h"
#include "sagarmatha-settings-module.h"
#include "sagarmatha-settings-plugin.h"
#include "sagarmatha-settings-profile.h"

#define SAGARMATHA_SETTINGS_PLUGIN_INFO_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), SAGARMATHA_TYPE_SETTINGS_PLUGIN_INFO, SagarmathaSettingsPluginInfoPrivate))

#define PLUGIN_GROUP "Sagarmatha Settings Plugin"

#define PLUGIN_PRIORITY_MAX 1
#define PLUGIN_PRIORITY_DEFAULT 100

struct SagarmathaSettingsPluginInfoPrivate
{
        char                    *file;
        GSettings               *settings;

        char                    *location;
        GTypeModule             *module;

        char                    *name;
        char                    *desc;
        char                   **authors;
        char                    *copyright;
        char                    *website;

        SagarmathaSettingsPlugin     *plugin;

        int                      enabled : 1;
        int                      active : 1;

        /* A plugin is unavailable if it is not possible to activate it
           due to an error loading the plugin module (e.g. for Python plugins
           when the interpreter has not been correctly initializated) */
        int                      available : 1;

        /* Priority determines the order in which plugins are started and
         * stopped. A lower number means higher priority. */
        guint                    priority;
};


enum {
        ACTIVATED,
        DEACTIVATED,
        LAST_SIGNAL
};

static guint signals [LAST_SIGNAL] = { 0, };

G_DEFINE_TYPE (SagarmathaSettingsPluginInfo, sagarmatha_settings_plugin_info, G_TYPE_OBJECT)

static void
sagarmatha_settings_plugin_info_finalize (GObject *object)
{
        SagarmathaSettingsPluginInfo *info;

        g_return_if_fail (object != NULL);
        g_return_if_fail (SAGARMATHA_IS_SETTINGS_PLUGIN_INFO (object));

        info = SAGARMATHA_SETTINGS_PLUGIN_INFO (object);

        g_return_if_fail (info->priv != NULL);

        if (info->priv->plugin != NULL) {
                g_debug ("Unref plugin %s", info->priv->name);

                g_object_unref (info->priv->plugin);

                /* info->priv->module must not be unref since it is not possible to finalize
                 * a type module */
        }

        g_free (info->priv->file);
        g_free (info->priv->location);
        g_free (info->priv->name);
        g_free (info->priv->desc);
        g_free (info->priv->website);
        g_free (info->priv->copyright);
        g_strfreev (info->priv->authors);

        if (info->priv->settings != NULL) {
                g_object_unref (info->priv->settings);
        }

        G_OBJECT_CLASS (sagarmatha_settings_plugin_info_parent_class)->finalize (object);
}

static void
sagarmatha_settings_plugin_info_class_init (SagarmathaSettingsPluginInfoClass *klass)
{
        GObjectClass   *object_class = G_OBJECT_CLASS (klass);

        object_class->finalize = sagarmatha_settings_plugin_info_finalize;

        signals [ACTIVATED] =
                g_signal_new ("activated",
                              G_TYPE_FROM_CLASS (object_class),
                              G_SIGNAL_RUN_LAST,
                              G_STRUCT_OFFSET (SagarmathaSettingsPluginInfoClass, activated),
                              NULL,
                              NULL,
                              g_cclosure_marshal_VOID__VOID,
                              G_TYPE_NONE,
                              0);
        signals [DEACTIVATED] =
                g_signal_new ("deactivated",
                              G_TYPE_FROM_CLASS (object_class),
                              G_SIGNAL_RUN_LAST,
                              G_STRUCT_OFFSET (SagarmathaSettingsPluginInfoClass, deactivated),
                              NULL,
                              NULL,
                              g_cclosure_marshal_VOID__VOID,
                              G_TYPE_NONE,
                              0);

        g_type_class_add_private (klass, sizeof (SagarmathaSettingsPluginInfoPrivate));
}

static void
sagarmatha_settings_plugin_info_init (SagarmathaSettingsPluginInfo *info)
{
        info->priv = SAGARMATHA_SETTINGS_PLUGIN_INFO_GET_PRIVATE (info);
}

static void
debug_info (SagarmathaSettingsPluginInfo *info)
{
        g_debug ("SagarmathaSettingsPluginInfo: name='%s' file='%s' location='%s'",
                 info->priv->name,
                 info->priv->file,
                 info->priv->location);
}

static gboolean
sagarmatha_settings_plugin_info_fill_from_file (SagarmathaSettingsPluginInfo *info,
                                           const char              *filename)
{
        GKeyFile *plugin_file = NULL;
        char     *str;
        int       priority;
        gboolean  ret;

        sagarmatha_settings_profile_start ("%s", filename);

        ret = FALSE;

        info->priv->file = g_strdup (filename);

        plugin_file = g_key_file_new ();
        if (! g_key_file_load_from_file (plugin_file, filename, G_KEY_FILE_NONE, NULL)) {
                g_warning ("Bad plugin file: %s", filename);
                goto out;
        }

        if (! g_key_file_has_key (plugin_file, PLUGIN_GROUP, "IAge", NULL)) {
                g_debug ("IAge key does not exist in file: %s", filename);
                goto out;
        }

        /* Check IAge=2 */
        if (g_key_file_get_integer (plugin_file, PLUGIN_GROUP, "IAge", NULL) != 0) {
                g_debug ("Wrong IAge in file: %s", filename);
                goto out;
        }

        /* Get Location */
        str = g_key_file_get_string (plugin_file, PLUGIN_GROUP, "Module", NULL);

        if ((str != NULL) && (*str != '\0')) {
                info->priv->location = str;
        } else {
                g_free (str);
                g_warning ("Could not find 'Module' in %s", filename);
                goto out;
        }

        /* Get Name */
        str = g_key_file_get_locale_string (plugin_file, PLUGIN_GROUP, "Name", NULL, NULL);
        if (str != NULL) {
                info->priv->name = str;
        } else {
                g_warning ("Could not find 'Name' in %s", filename);
                goto out;
        }

        /* Get Description */
        str = g_key_file_get_locale_string (plugin_file, PLUGIN_GROUP, "Description", NULL, NULL);
        if (str != NULL) {
                info->priv->desc = str;
        } else {
                g_debug ("Could not find 'Description' in %s", filename);
        }

        /* Get Authors */
        info->priv->authors = g_key_file_get_string_list (plugin_file, PLUGIN_GROUP, "Authors", NULL, NULL);
        if (info->priv->authors == NULL) {
                g_debug ("Could not find 'Authors' in %s", filename);
        }

        /* Get Copyright */
        str = g_key_file_get_string (plugin_file, PLUGIN_GROUP, "Copyright", NULL);
        if (str != NULL) {
                info->priv->copyright = str;
        } else {
                g_debug ("Could not find 'Copyright' in %s", filename);
        }

        /* Get Website */
        str = g_key_file_get_string (plugin_file, PLUGIN_GROUP, "Website", NULL);
        if (str != NULL) {
                info->priv->website = str;
        } else {
                g_debug ("Could not find 'Website' in %s", filename);
        }

        /* Get Priority */
        priority = g_key_file_get_integer (plugin_file, PLUGIN_GROUP, "Priority", NULL);
        if (priority >= PLUGIN_PRIORITY_MAX) {
                info->priv->priority = priority;
        } else {
                info->priv->priority = PLUGIN_PRIORITY_DEFAULT;
        }

        g_key_file_free (plugin_file);

        debug_info (info);

        /* If we know nothing about the availability of the plugin,
           set it as available */
        info->priv->available = TRUE;

        ret = TRUE;
 out:
        sagarmatha_settings_profile_end ("%s", filename);

        return ret;
}

SagarmathaSettingsPluginInfo *
sagarmatha_settings_plugin_info_new_from_file (const char *filename)
{
        SagarmathaSettingsPluginInfo *info;
        gboolean                 res;

        info = g_object_new (SAGARMATHA_TYPE_SETTINGS_PLUGIN_INFO, NULL);

        res = sagarmatha_settings_plugin_info_fill_from_file (info, filename);
        if (! res) {
                g_object_unref (info);
                info = NULL;
        }

        return info;
}

static void
plugin_enabled_cb (GSettings               *settings,
                   const gchar             *key,
                   SagarmathaSettingsPluginInfo *info)
{
        if (g_strcmp0 (key, "active") == 0) {
                if (g_settings_get_boolean (settings, "active"))
                        sagarmatha_settings_plugin_info_activate (info);
                else
                        sagarmatha_settings_plugin_info_deactivate (info);
        }
}

void
sagarmatha_settings_plugin_info_set_settings_prefix (SagarmathaSettingsPluginInfo *info,
                                                const char              *settings_prefix)
{
        int priority;

        info->priv->settings = g_settings_new (settings_prefix);
        info->priv->enabled = g_settings_get_boolean (info->priv->settings, "active");

        priority = g_settings_get_int (info->priv->settings, "priority");
        if (priority > 0)
                info->priv->priority = priority;

        g_signal_connect (G_OBJECT (info->priv->settings),
                          "changed",
                          G_CALLBACK (plugin_enabled_cb),
                          info);
}

static void
_deactivate_plugin (SagarmathaSettingsPluginInfo *info)
{
        sagarmatha_settings_plugin_deactivate (info->priv->plugin);
        g_signal_emit (info, signals [DEACTIVATED], 0);
}

gboolean
sagarmatha_settings_plugin_info_deactivate (SagarmathaSettingsPluginInfo *info)
{
        g_return_val_if_fail (SAGARMATHA_IS_SETTINGS_PLUGIN_INFO (info), FALSE);

        if (!info->priv->active || !info->priv->available) {
                return TRUE;
        }

        _deactivate_plugin (info);

        /* Update plugin state */
        info->priv->active = FALSE;

        return TRUE;
}


static gboolean
load_plugin_module (SagarmathaSettingsPluginInfo *info)
{
        char    *path;
        char    *dirname;
        gboolean ret;

        ret = FALSE;

        g_return_val_if_fail (SAGARMATHA_IS_SETTINGS_PLUGIN_INFO (info), FALSE);
        g_return_val_if_fail (info->priv->file != NULL, FALSE);
        g_return_val_if_fail (info->priv->location != NULL, FALSE);
        g_return_val_if_fail (info->priv->plugin == NULL, FALSE);
        g_return_val_if_fail (info->priv->available, FALSE);

        sagarmatha_settings_profile_start ("%s", info->priv->location);

        dirname = g_path_get_dirname (info->priv->file);
        g_return_val_if_fail (dirname != NULL, FALSE);

        path = g_module_build_path (dirname, info->priv->location);
        g_free (dirname);
        g_return_val_if_fail (path != NULL, FALSE);

        info->priv->module = G_TYPE_MODULE (sagarmatha_settings_module_new (path));
        g_free (path);

        if (!g_type_module_use (info->priv->module)) {
                g_warning ("Cannot load plugin '%s' since file '%s' cannot be read.",
                           info->priv->name,
                           sagarmatha_settings_module_get_path (SAGARMATHA_SETTINGS_MODULE (info->priv->module)));

                g_object_unref (G_OBJECT (info->priv->module));
                info->priv->module = NULL;

                /* Mark plugin as unavailable and fails */
                info->priv->available = FALSE;

                goto out;
        }

        info->priv->plugin = SAGARMATHA_SETTINGS_PLUGIN (sagarmatha_settings_module_new_object (SAGARMATHA_SETTINGS_MODULE (info->priv->module)));

        g_type_module_unuse (info->priv->module);
        ret = TRUE;
 out:
        sagarmatha_settings_profile_end ("%s", info->priv->location);
        return ret;
}

static gboolean
_activate_plugin (SagarmathaSettingsPluginInfo *info)
{
        gboolean res = TRUE;

        if (!info->priv->available) {
                /* Plugin is not available, don't try to activate/load it */
                return FALSE;
        }

        if (info->priv->plugin == NULL) {
                res = load_plugin_module (info);
        }

        if (res) {
                sagarmatha_settings_plugin_activate (info->priv->plugin);
                g_signal_emit (info, signals [ACTIVATED], 0);
        } else {
                g_warning ("Error activating plugin '%s'", info->priv->name);
        }

        return res;
}

gboolean
sagarmatha_settings_plugin_info_activate (SagarmathaSettingsPluginInfo *info)
{

        g_return_val_if_fail (SAGARMATHA_IS_SETTINGS_PLUGIN_INFO (info), FALSE);

        if (! info->priv->available) {
                return FALSE;
        }

        if (info->priv->active) {
                return TRUE;
        }

        if (_activate_plugin (info)) {
                info->priv->active = TRUE;
                return TRUE;
        }

        return FALSE;
}

gboolean
sagarmatha_settings_plugin_info_is_active (SagarmathaSettingsPluginInfo *info)
{
        g_return_val_if_fail (SAGARMATHA_IS_SETTINGS_PLUGIN_INFO (info), FALSE);

        return (info->priv->available && info->priv->active);
}

gboolean
sagarmatha_settings_plugin_info_get_enabled (SagarmathaSettingsPluginInfo *info)
{
        g_return_val_if_fail (SAGARMATHA_IS_SETTINGS_PLUGIN_INFO (info), FALSE);

        return (info->priv->enabled);
}

gboolean
sagarmatha_settings_plugin_info_is_available (SagarmathaSettingsPluginInfo *info)
{
        g_return_val_if_fail (SAGARMATHA_IS_SETTINGS_PLUGIN_INFO (info), FALSE);

        return (info->priv->available != FALSE);
}

const char *
sagarmatha_settings_plugin_info_get_name (SagarmathaSettingsPluginInfo *info)
{
        g_return_val_if_fail (SAGARMATHA_IS_SETTINGS_PLUGIN_INFO (info), NULL);

        return info->priv->name;
}

const char *
sagarmatha_settings_plugin_info_get_description (SagarmathaSettingsPluginInfo *info)
{
        g_return_val_if_fail (SAGARMATHA_IS_SETTINGS_PLUGIN_INFO (info), NULL);

        return info->priv->desc;
}

const char **
sagarmatha_settings_plugin_info_get_authors (SagarmathaSettingsPluginInfo *info)
{
        g_return_val_if_fail (SAGARMATHA_IS_SETTINGS_PLUGIN_INFO (info), (const char **)NULL);

        return (const char **)info->priv->authors;
}

const char *
sagarmatha_settings_plugin_info_get_website (SagarmathaSettingsPluginInfo *info)
{
        g_return_val_if_fail (SAGARMATHA_IS_SETTINGS_PLUGIN_INFO (info), NULL);

        return info->priv->website;
}

const char *
sagarmatha_settings_plugin_info_get_copyright (SagarmathaSettingsPluginInfo *info)
{
        g_return_val_if_fail (SAGARMATHA_IS_SETTINGS_PLUGIN_INFO (info), NULL);

        return info->priv->copyright;
}


const char *
sagarmatha_settings_plugin_info_get_location (SagarmathaSettingsPluginInfo *info)
{
        g_return_val_if_fail (SAGARMATHA_IS_SETTINGS_PLUGIN_INFO (info), NULL);

        return info->priv->location;
}

int
sagarmatha_settings_plugin_info_get_priority (SagarmathaSettingsPluginInfo *info)
{
        g_return_val_if_fail (SAGARMATHA_IS_SETTINGS_PLUGIN_INFO (info), PLUGIN_PRIORITY_DEFAULT);

        return info->priv->priority;
}

void
sagarmatha_settings_plugin_info_set_priority (SagarmathaSettingsPluginInfo *info,
                                         int                      priority)
{
        g_return_if_fail (SAGARMATHA_IS_SETTINGS_PLUGIN_INFO (info));

        info->priv->priority = priority;
}
