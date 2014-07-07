/* -*- Mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2007 William Jon McCann <mccann@jhu.edu>
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
 * Foundation, Inc., 51 Franklin Street - Suite 500, Boston, MA 02110-1335, USA.
 *
 */

#ifndef __SAGARMATHA_SETTINGS_MANAGER_H
#define __SAGARMATHA_SETTINGS_MANAGER_H

#include <glib-object.h>

G_BEGIN_DECLS

#define SAGARMATHA_TYPE_SETTINGS_MANAGER         (sagarmatha_settings_manager_get_type ())
#define SAGARMATHA_SETTINGS_MANAGER(o)           (G_TYPE_CHECK_INSTANCE_CAST ((o), SAGARMATHA_TYPE_SETTINGS_MANAGER, SagarmathaSettingsManager))
#define SAGARMATHA_SETTINGS_MANAGER_CLASS(k)     (G_TYPE_CHECK_CLASS_CAST((k), SAGARMATHA_TYPE_SETTINGS_MANAGER, SagarmathaSettingsManagerClass))
#define SAGARMATHA_IS_SETTINGS_MANAGER(o)        (G_TYPE_CHECK_INSTANCE_TYPE ((o), SAGARMATHA_TYPE_SETTINGS_MANAGER))
#define SAGARMATHA_IS_SETTINGS_MANAGER_CLASS(k)  (G_TYPE_CHECK_CLASS_TYPE ((k), SAGARMATHA_TYPE_SETTINGS_MANAGER))
#define SAGARMATHA_SETTINGS_MANAGER_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), SAGARMATHA_TYPE_SETTINGS_MANAGER, SagarmathaSettingsManagerClass))

typedef struct SagarmathaSettingsManagerPrivate SagarmathaSettingsManagerPrivate;

typedef struct
{
        GObject                      parent;
        SagarmathaSettingsManagerPrivate *priv;
} SagarmathaSettingsManager;

typedef struct
{
        GObjectClass   parent_class;

        void          (* plugin_activated)         (SagarmathaSettingsManager *manager,
                                                    const char           *name);
        void          (* plugin_deactivated)       (SagarmathaSettingsManager *manager,
                                                    const char           *name);
} SagarmathaSettingsManagerClass;

typedef enum
{
        SAGARMATHA_SETTINGS_MANAGER_ERROR_GENERAL
} SagarmathaSettingsManagerError;

#define SAGARMATHA_SETTINGS_MANAGER_ERROR sagarmatha_settings_manager_error_quark ()

GQuark                 sagarmatha_settings_manager_error_quark         (void);
GType                  sagarmatha_settings_manager_get_type   (void);

SagarmathaSettingsManager * sagarmatha_settings_manager_new        (void);
gboolean               sagarmatha_settings_manager_start      (SagarmathaSettingsManager *manager,
                                                          GError              **error);
void                   sagarmatha_settings_manager_stop       (SagarmathaSettingsManager *manager);

G_END_DECLS

#endif /* __SAGARMATHA_SETTINGS_MANAGER_H */
