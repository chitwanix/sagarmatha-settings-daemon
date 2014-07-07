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

#ifndef __SAGARMATHA_XSETTINGS_MANAGER_H
#define __SAGARMATHA_XSETTINGS_MANAGER_H

#include <glib-object.h>

G_BEGIN_DECLS

#define SAGARMATHA_TYPE_XSETTINGS_MANAGER         (sagarmatha_xsettings_manager_get_type ())
#define SAGARMATHA_XSETTINGS_MANAGER(o)           (G_TYPE_CHECK_INSTANCE_CAST ((o), SAGARMATHA_TYPE_XSETTINGS_MANAGER, SagarmathaSettingsXSettingsManager))
#define SAGARMATHA_XSETTINGS_MANAGER_CLASS(k)     (G_TYPE_CHECK_CLASS_CAST((k), SAGARMATHA_TYPE_XSETTINGS_MANAGER, SagarmathaSettingsXSettingsManagerClass))
#define SAGARMATHA_IS_XSETTINGS_MANAGER(o)        (G_TYPE_CHECK_INSTANCE_TYPE ((o), SAGARMATHA_TYPE_XSETTINGS_MANAGER))
#define SAGARMATHA_IS_XSETTINGS_MANAGER_CLASS(k)  (G_TYPE_CHECK_CLASS_TYPE ((k), SAGARMATHA_TYPE_XSETTINGS_MANAGER))
#define SAGARMATHA_XSETTINGS_MANAGER_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), SAGARMATHA_TYPE_XSETTINGS_MANAGER, SagarmathaSettingsXSettingsManagerClass))

typedef struct SagarmathaSettingsXSettingsManagerPrivate SagarmathaSettingsXSettingsManagerPrivate;

typedef struct
{
        GObject                     parent;
        SagarmathaSettingsXSettingsManagerPrivate *priv;
} SagarmathaSettingsXSettingsManager;

typedef struct
{
        GObjectClass   parent_class;
} SagarmathaSettingsXSettingsManagerClass;

GType                   sagarmatha_xsettings_manager_get_type            (void);

SagarmathaSettingsXSettingsManager * sagarmatha_xsettings_manager_new                 (void);
gboolean                sagarmatha_xsettings_manager_start               (SagarmathaSettingsXSettingsManager *manager,
                                                                     GError               **error);
void                    sagarmatha_xsettings_manager_stop                (SagarmathaSettingsXSettingsManager *manager);

G_END_DECLS

#endif /* __SAGARMATHA_XSETTINGS_MANAGER_H */
