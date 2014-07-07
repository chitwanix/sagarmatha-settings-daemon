/* -*- Mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2008 Red Hat, Inc.
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

#ifndef __SAGARMATHA_SETTINGS_PLUGIN_INFO_H__
#define __SAGARMATHA_SETTINGS_PLUGIN_INFO_H__

#include <glib-object.h>
#include <gmodule.h>

G_BEGIN_DECLS
#define SAGARMATHA_TYPE_SETTINGS_PLUGIN_INFO              (sagarmatha_settings_plugin_info_get_type())
#define SAGARMATHA_SETTINGS_PLUGIN_INFO(obj)              (G_TYPE_CHECK_INSTANCE_CAST((obj), SAGARMATHA_TYPE_SETTINGS_PLUGIN_INFO, SagarmathaSettingsPluginInfo))
#define SAGARMATHA_SETTINGS_PLUGIN_INFO_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST((klass),  SAGARMATHA_TYPE_SETTINGS_PLUGIN_INFO, SagarmathaSettingsPluginInfoClass))
#define SAGARMATHA_IS_SETTINGS_PLUGIN_INFO(obj)           (G_TYPE_CHECK_INSTANCE_TYPE((obj), SAGARMATHA_TYPE_SETTINGS_PLUGIN_INFO))
#define SAGARMATHA_IS_SETTINGS_PLUGIN_INFO_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), SAGARMATHA_TYPE_SETTINGS_PLUGIN_INFO))
#define SAGARMATHA_SETTINGS_PLUGIN_INFO_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS((obj),  SAGARMATHA_TYPE_SETTINGS_PLUGIN_INFO, SagarmathaSettingsPluginInfoClass))

typedef struct SagarmathaSettingsPluginInfoPrivate SagarmathaSettingsPluginInfoPrivate;

typedef struct
{
        GObject                         parent;
        SagarmathaSettingsPluginInfoPrivate *priv;
} SagarmathaSettingsPluginInfo;

typedef struct
{
        GObjectClass parent_class;

        void          (* activated)         (SagarmathaSettingsPluginInfo *info);
        void          (* deactivated)       (SagarmathaSettingsPluginInfo *info);
} SagarmathaSettingsPluginInfoClass;

GType            sagarmatha_settings_plugin_info_get_type           (void) G_GNUC_CONST;

SagarmathaSettingsPluginInfo *sagarmatha_settings_plugin_info_new_from_file (const char *filename);

void             sagarmatha_settings_plugin_info_set_settings_prefix (SagarmathaSettingsPluginInfo *info, const char *settings_prefix);
gboolean         sagarmatha_settings_plugin_info_activate        (SagarmathaSettingsPluginInfo *info);
gboolean         sagarmatha_settings_plugin_info_deactivate      (SagarmathaSettingsPluginInfo *info);

gboolean         sagarmatha_settings_plugin_info_is_active       (SagarmathaSettingsPluginInfo *info);
gboolean         sagarmatha_settings_plugin_info_get_enabled     (SagarmathaSettingsPluginInfo *info);
gboolean         sagarmatha_settings_plugin_info_is_available    (SagarmathaSettingsPluginInfo *info);

const char      *sagarmatha_settings_plugin_info_get_name        (SagarmathaSettingsPluginInfo *info);
const char      *sagarmatha_settings_plugin_info_get_description (SagarmathaSettingsPluginInfo *info);
const char     **sagarmatha_settings_plugin_info_get_authors     (SagarmathaSettingsPluginInfo *info);
const char      *sagarmatha_settings_plugin_info_get_website     (SagarmathaSettingsPluginInfo *info);
const char      *sagarmatha_settings_plugin_info_get_copyright   (SagarmathaSettingsPluginInfo *info);
const char      *sagarmatha_settings_plugin_info_get_location    (SagarmathaSettingsPluginInfo *info);
int              sagarmatha_settings_plugin_info_get_priority    (SagarmathaSettingsPluginInfo *info);

void             sagarmatha_settings_plugin_info_set_priority    (SagarmathaSettingsPluginInfo *info,
                                                             int                      priority);

G_END_DECLS

#endif  /* __SAGARMATHA_SETTINGS_PLUGIN_INFO_H__ */
