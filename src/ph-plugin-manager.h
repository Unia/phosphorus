/* PhPluginManager
 *
 * Copyright (C) 2016 Jente Hidskes
 *
 * Author: Jente Hidskes <hjdskes@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <glib-object.h>

#include <plugin/ph-plugin.h>

#include "ph-application.h"

G_BEGIN_DECLS

#define PH_PLUGIN_MANAGER_TYPE ph_plugin_manager_get_type ()

G_DECLARE_FINAL_TYPE (PhPluginManager, ph_plugin_manager, PH, PLUGIN_MANAGER, GObject)

PhPluginManager *ph_plugin_manager_get_default (PhApplication *application);

void             ph_plugin_manager_proxy_plugins (PhPluginManager *manager, const gchar *filepath);

G_END_DECLS

