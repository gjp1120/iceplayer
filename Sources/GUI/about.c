/*
 * show information about this program
 *
 * about.c
 * This file is part of <iceplayer>
 *
 * Copyright (C) 2011 - gjp1120, license: GPL v3
 *
 * <iceplayer> is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * <iceplayer> is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with <iceplayer>; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, 
 * Boston, MA  02110-1301  USA
 */
#include <gtk/gtk.h>
#include "about.h"

#define COMMENTS \
  "A Media Player Base On Gstreamer & Gtk From Canton China ! 2010 GPL"

void GUI_Dialogs_About(void)
{
  print_programming("GUI::Dialogs::About()");

  GtkWidget *about_dialog;

  const gchar *authors[] = { "gjp1120 gjp1120@gmail.com",
							 "HuangJiaCheng jasy.ice@163.com",
							 NULL };

  about_dialog = gtk_about_dialog_new();

  gtk_container_set_border_width(GTK_CONTAINER(about_dialog), 5);
  gtk_window_set_destroy_with_parent(GTK_WINDOW(about_dialog), TRUE);
  gtk_window_set_keep_above(GTK_WINDOW(about_dialog), TRUE);

  gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(about_dialog), "5.0dev1");
  gtk_about_dialog_set_name(GTK_ABOUT_DIALOG(about_dialog), PROG_NAME);
  gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(about_dialog), COMMENTS);
  gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(about_dialog),
							   "http://www.iceplayer.org");
  gtk_about_dialog_set_license(GTK_ABOUT_DIALOG (about_dialog), "GPLv3");
  gtk_about_dialog_set_website_label(GTK_ABOUT_DIALOG(about_dialog),
									 "www.iceplayer.org  \n"
									 "jasy.ice@163.com&gjp1120@gmail.com");
  gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(about_dialog), authors);
  
  gtk_dialog_run(GTK_DIALOG(about_dialog));
  gtk_widget_destroy(about_dialog);
}
