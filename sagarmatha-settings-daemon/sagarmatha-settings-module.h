/* -*- Mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2005 - Paolo Maggi
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

#ifndef SAGARMATHA_SETTINGS_MODULE_H
#define SAGARMATHA_SETTINGS_MODULE_H

#include <glib-object.h>

G_BEGIN_DECLS

#define SAGARMATHA_TYPE_SETTINGS_MODULE               (sagarmatha_settings_module_get_type ())
#define SAGARMATHA_SETTINGS_MODULE(obj)               (G_TYPE_CHECK_INSTANCE_CAST ((obj), SAGARMATHA_TYPE_SETTINGS_MODULE, SagarmathaSettingsModule))
#define SAGARMATHA_SETTINGS_MODULE_CLASS(klass)       (G_TYPE_CHECK_CLASS_CAST ((klass), SAGARMATHA_TYPE_SETTINGS_MODULE, SagarmathaSettingsModuleClass))
#define SAGARMATHA_IS_SETTINGS_MODULE(obj)            (G_TYPE_CHECK_INSTANCE_TYPE ((obj), SAGARMATHA_TYPE_SETTINGS_MODULE))
#define SAGARMATHA_IS_SETTINGS_MODULE_CLASS(klass)    (G_TYPE_CHECK_CLASS_TYPE ((obj), SAGARMATHA_TYPE_SETTINGS_MODULE))
#define SAGARMATHA_SETTINGS_MODULE_GET_CLASS(obj)     (G_TYPE_INSTANCE_GET_CLASS((obj), SAGARMATHA_TYPE_SETTINGS_MODULE, SagarmathaSettingsModuleClass))

typedef struct _SagarmathaSettingsModule SagarmathaSettingsModule;

GType                    sagarmatha_settings_module_get_type          (void) G_GNUC_CONST;

SagarmathaSettingsModule     *sagarmatha_settings_module_new               (const gchar *path);

const char              *sagarmatha_settings_module_get_path          (SagarmathaSettingsModule *module);

GObject                 *sagarmatha_settings_module_new_object        (SagarmathaSettingsModule *module);

G_END_DECLS

#endif
