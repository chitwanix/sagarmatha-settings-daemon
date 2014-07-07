/* -*- Mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2002-2005 Paolo Maggi
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

#ifndef __SAGARMATHA_SETTINGS_PLUGIN_H__
#define __SAGARMATHA_SETTINGS_PLUGIN_H__

#include <glib-object.h>
#include <gmodule.h>

G_BEGIN_DECLS
#define SAGARMATHA_TYPE_SETTINGS_PLUGIN              (sagarmatha_settings_plugin_get_type())
#define SAGARMATHA_SETTINGS_PLUGIN(obj)              (G_TYPE_CHECK_INSTANCE_CAST((obj), SAGARMATHA_TYPE_SETTINGS_PLUGIN, SagarmathaSettingsPlugin))
#define SAGARMATHA_SETTINGS_PLUGIN_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST((klass),  SAGARMATHA_TYPE_SETTINGS_PLUGIN, SagarmathaSettingsPluginClass))
#define SAGARMATHA_IS_SETTINGS_PLUGIN(obj)           (G_TYPE_CHECK_INSTANCE_TYPE((obj), SAGARMATHA_TYPE_SETTINGS_PLUGIN))
#define SAGARMATHA_IS_SETTINGS_PLUGIN_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), SAGARMATHA_TYPE_SETTINGS_PLUGIN))
#define SAGARMATHA_SETTINGS_PLUGIN_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS((obj),  SAGARMATHA_TYPE_SETTINGS_PLUGIN, SagarmathaSettingsPluginClass))

typedef struct
{
        GObject parent;
} SagarmathaSettingsPlugin;

typedef struct
{
        GObjectClass parent_class;

        /* Virtual public methods */
        void            (*activate)                     (SagarmathaSettingsPlugin *plugin);
        void            (*deactivate)                   (SagarmathaSettingsPlugin *plugin);
} SagarmathaSettingsPluginClass;

GType            sagarmatha_settings_plugin_get_type           (void) G_GNUC_CONST;

void             sagarmatha_settings_plugin_activate           (SagarmathaSettingsPlugin *plugin);
void             sagarmatha_settings_plugin_deactivate         (SagarmathaSettingsPlugin *plugin);

/*
 * Utility macro used to register plugins
 *
 * use: SAGARMATHA_SETTINGS_PLUGIN_REGISTER (PluginName, plugin_name)
 */
#define SAGARMATHA_SETTINGS_PLUGIN_REGISTER(PluginName, plugin_name)                \
        G_DEFINE_DYNAMIC_TYPE (PluginName,                                     \
                               plugin_name,                                    \
                               SAGARMATHA_TYPE_SETTINGS_PLUGIN)                     \
                                                                               \
G_MODULE_EXPORT GType                                                          \
register_sagarmatha_settings_plugin (GTypeModule *type_module)                      \
{                                                                              \
        plugin_name##_register_type (type_module);                             \
                                                                               \
        return plugin_name##_get_type();                                       \
}                                                                              \
                                                                               \
static void                                                                    \
plugin_name##_class_finalize (PluginName##Class *plugin_name##_class)          \
{                                                                              \
}                                                                              \

G_END_DECLS

#endif  /* __SAGARMATHA_SETTINGS_PLUGIN_H__ */
