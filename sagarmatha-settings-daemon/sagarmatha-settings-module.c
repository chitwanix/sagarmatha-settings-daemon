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

#include "config.h"

#include "sagarmatha-settings-module.h"

#include <gmodule.h>

typedef struct _SagarmathaSettingsModuleClass SagarmathaSettingsModuleClass;

struct _SagarmathaSettingsModuleClass
{
        GTypeModuleClass parent_class;
};

struct _SagarmathaSettingsModule
{
        GTypeModule parent_instance;

        GModule    *library;

        char       *path;
        GType       type;
};

typedef GType (*SagarmathaSettingsModuleRegisterFunc) (GTypeModule *);

G_DEFINE_TYPE (SagarmathaSettingsModule, sagarmatha_settings_module, G_TYPE_TYPE_MODULE)

static gboolean
sagarmatha_settings_module_load (GTypeModule *gmodule)
{
        SagarmathaSettingsModule            *module;
        SagarmathaSettingsModuleRegisterFunc register_func;
        gboolean                        res;

        module = CINNAMON_SETTINGS_MODULE (gmodule);

        g_debug ("Loading %s", module->path);

        module->library = g_module_open (module->path, 0);

        if (module->library == NULL) {
                g_warning ("%s", g_module_error ());

                return FALSE;
        }

        /* extract symbols from the lib */
        res = g_module_symbol (module->library, "register_sagarmatha_settings_plugin", (void *) &register_func);
        if (! res) {
                g_warning ("%s", g_module_error ());
                g_module_close (module->library);

                return FALSE;
        }

        g_assert (register_func);

        module->type = register_func (gmodule);

        if (module->type == 0) {
                g_warning ("Invalid gnome settings plugin in module %s", module->path);
                return FALSE;
        }

        return TRUE;
}

static void
sagarmatha_settings_module_unload (GTypeModule *gmodule)
{
        SagarmathaSettingsModule *module = CINNAMON_SETTINGS_MODULE (gmodule);

        g_debug ("Unloading %s", module->path);

        g_module_close (module->library);

        module->library = NULL;
        module->type = 0;
}

const gchar *
sagarmatha_settings_module_get_path (SagarmathaSettingsModule *module)
{
        g_return_val_if_fail (CINNAMON_IS_SETTINGS_MODULE (module), NULL);

        return module->path;
}

GObject *
sagarmatha_settings_module_new_object (SagarmathaSettingsModule *module)
{
        g_debug ("Creating object of type %s", g_type_name (module->type));

        if (module->type == 0) {
                return NULL;
        }

        return g_object_new (module->type, NULL);
}

static void
sagarmatha_settings_module_init (SagarmathaSettingsModule *module)
{
        g_debug ("SagarmathaSettingsModule %p initialising", module);
}

static void
sagarmatha_settings_module_finalize (GObject *object)
{
        SagarmathaSettingsModule *module = CINNAMON_SETTINGS_MODULE (object);

        g_debug ("SagarmathaSettingsModule %p finalizing", module);

        g_free (module->path);

        G_OBJECT_CLASS (sagarmatha_settings_module_parent_class)->finalize (object);
}

static void
sagarmatha_settings_module_class_init (SagarmathaSettingsModuleClass *class)
{
        GObjectClass *object_class = G_OBJECT_CLASS (class);
        GTypeModuleClass *module_class = G_TYPE_MODULE_CLASS (class);

        object_class->finalize = sagarmatha_settings_module_finalize;

        module_class->load = sagarmatha_settings_module_load;
        module_class->unload = sagarmatha_settings_module_unload;
}

SagarmathaSettingsModule *
sagarmatha_settings_module_new (const char *path)
{
        SagarmathaSettingsModule *result;

        if (path == NULL || path[0] == '\0') {
                return NULL;
        }

        result = g_object_new (CINNAMON_TYPE_SETTINGS_MODULE, NULL);

        g_type_module_set_name (G_TYPE_MODULE (result), path);
        result->path = g_strdup (path);

        return result;
}