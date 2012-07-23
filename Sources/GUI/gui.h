/*
 * GUI Declaration
 *
 * gui.h
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
#include "../common.h"

#ifndef __GUI_H
#define __GUI_H

G_BEGIN_DECLS;

typedef struct
{
  GtkWidget *window_main;
  GtkWidget *hpaned_main;
  GtkWidget *treeview_lists; //播放列表列表
  GtkWidget *treeview_songs; //歌曲列表
  GtkWidget *statusbar_main;

  //这是用来放置主窗口的警告的
  GtkWidget *infobar;
  GtkWidget *infobar_label_title;
  GtkWidget *infobar_label;

  GtkActionGroup *actiongroup_main;
  GtkUIManager *uimgr_main;
}iceplayer_GuiData_t;

gboolean GUI_init(void);
gboolean GUI_fini(void);

void GUI_MainWindow_showinfo(const gchar *, const gchar *,
							 const guint, GtkMessageType);

iceplayer_GuiData_t *GUI_Get_Datastruct(void);


G_END_DECLS;

#endif //__GUI_H
