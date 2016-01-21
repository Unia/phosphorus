/* PhWindow
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

#include <gtk/gtk.h>
#include <glib/gi18n.h>

#include "ph-thumbview.h"
#include "ph-window.h"

/* Copyright years. */
#define COPYRIGHT "2015-2016"

struct _PhWindowPrivate {
	GtkWidget *headerbar;
	PhThumbview *thumbview;
};

G_DEFINE_TYPE_WITH_PRIVATE (PhWindow, ph_window, GTK_TYPE_APPLICATION_WINDOW);

static void
ph_window_action_apply (GSimpleAction *action,
			GVariant      *parameter,
			gpointer       user_data)
{
	PhWindowPrivate *priv;

	priv = ph_window_get_instance_private (PH_WINDOW (user_data));

	ph_thumbview_activate (priv->thumbview);
}

static const GActionEntry window_actions[] = {
	{ "apply", ph_window_action_apply, NULL, NULL, NULL },
};

static void
ph_window_thumbview_activated (PhThumbview *thumbview, const gchar *filepath, gpointer user_data)
{
	PhApplication *application;

	/* FIXME: quite a waste to retrieve the same application all the time. */
	g_object_get (user_data, "application", &application, NULL);
	ph_application_proxy_plugin (application, filepath);
	g_object_unref (application);
}

static void
ph_window_thumbview_selection_changed (PhThumbview *thumbview, gpointer user_data)
{
	GAction *action;
	gboolean enabled;

	action = g_action_map_lookup_action (G_ACTION_MAP (user_data), "apply");
	g_object_get (G_OBJECT (action), "enabled", &enabled, NULL);

	if (G_UNLIKELY (!enabled)) {
		g_simple_action_set_enabled (G_SIMPLE_ACTION (action), TRUE);
	}
}

static void
ph_window_class_init (PhWindowClass *ph_window_class)
{
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (ph_window_class);

	gtk_widget_class_set_template_from_resource (widget_class, "/org/unia/phosphorus/window.ui");

	gtk_widget_class_bind_template_child_private (widget_class, PhWindow, headerbar);
	gtk_widget_class_bind_template_child_private (widget_class, PhWindow, thumbview);

	gtk_widget_class_bind_template_callback (widget_class, ph_window_thumbview_activated);
	gtk_widget_class_bind_template_callback (widget_class, ph_window_thumbview_selection_changed);
}

static void
ph_window_init (PhWindow *window)
{
	PhWindowPrivate *priv;
	GAction *action;

	priv = ph_window_get_instance_private (window);

	gtk_widget_init_template (GTK_WIDGET (window));
	gtk_header_bar_set_title (GTK_HEADER_BAR (priv->headerbar), g_get_application_name ());

	g_action_map_add_action_entries (G_ACTION_MAP (window),
					 window_actions,
					 G_N_ELEMENTS (window_actions),
					 window);

	action = g_action_map_lookup_action (G_ACTION_MAP (window), "apply");
	g_simple_action_set_enabled (G_SIMPLE_ACTION (action), FALSE);
}

PhWindow *
ph_window_new (PhApplication *application)
{
	g_return_val_if_fail (PH_IS_APPLICATION (application), NULL);

	return g_object_new (PH_TYPE_WINDOW,
			     "application", application,
			     NULL);
}

void
ph_window_show_about_dialog (PhWindow *window)
{
	g_return_if_fail (PH_IS_WINDOW (window));

	static const char *authors[] = {
		"Jente Hidskes <hjdskes@gmail.com>",
		NULL,
	};

	gtk_show_about_dialog (GTK_WINDOW (window),
			       "program-name", g_get_application_name (),
			       "version", PACKAGE_VERSION,
			       "copyright", "Copyright \xc2\xa9 "COPYRIGHT" Jente Hidskes",
			       "comments", _("Browse and set wallpapers"),
			       "authors", authors,
			       /* Translators: translate this to give yourself credits. */
			       "translator-credits", _("translator-credits"),
			       "website-label", _("Website"),
			       "website", PACKAGE_URL,
			       "logo-icon-name", gtk_window_get_default_icon_name (),
			       "wrap-license", TRUE,
			       "license-type", GTK_LICENSE_GPL_3_0,
			       NULL);
}

void
ph_window_close (PhWindow *window)
{
	g_return_if_fail (PH_IS_WINDOW (window));
	gtk_widget_destroy (GTK_WIDGET (window));
}

void
ph_window_scan_directories (PhWindow *window, PhRecurseType recurse, gchar * const *directories)
{
	PhWindowPrivate *priv;

	g_return_if_fail (PH_IS_WINDOW (window));
	g_return_if_fail (directories != NULL);

	priv = ph_window_get_instance_private (window);

	for (; *directories; directories++) {
		ph_thumbview_add_directory (priv->thumbview, recurse, *directories);
	}
}
