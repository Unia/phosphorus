/* Utilities
 *
 * Copyright (C) 2015-2016 Jente Hidskes
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <glib.h>

#include "util.h"

/* FIXME: find better way to do this. */
gboolean
ph_file_is_image (const gchar *file)
{
	static const gchar *filetypes[] = {
		".png",  ".PNG",
		".jpg",  ".JPG",
		".jpeg", ".JPEG",
		".gif",  ".GIF",
	};
	static guint n = G_N_ELEMENTS (filetypes);

	for (guint i = 0; i < n; i++) {
		if (g_strrstr (file, filetypes[i])) {
			return TRUE;
		}
	}

	return FALSE;
}

void
ph_get_plugin_dirs (gchar **plugin_dir, gchar **plugin_data_dir)
{
	*plugin_dir = g_build_filename (LIB_DIR, "phosphorus", "plugins", NULL);
	*plugin_data_dir = g_build_filename (DATA_DIR, "phosphorus", "plugins", NULL);
}

void
ph_get_user_dir (gchar **user_dir)
{
	const gchar *user_data_dir;

	user_data_dir = g_get_user_data_dir ();
	*user_dir = g_build_filename (user_data_dir, "phosphorus", "plugins", NULL);
}

