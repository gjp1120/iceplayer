/*
 * GUI 
 *
 * gui_listview.c
 * This file is part of <iceplayer>
 *
 * Copyright (C) 2010 - gjp1120, license: GPL v3
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
#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "gui_listview.h"

/**
 * SECTION: gui_listview
 * @Short_description: 播放器用户图形界面的实现，列表部分
 * @Title: 列表界面
 * @Include: gui_listview.h
 *
 * 负责构建播放器的图形界面中的播放列表表和歌曲列表
 */

static iceplayer_GuiData_t *icep_gui;
static iceplayer_ListStoreData_t icep_liststore;
static __thread GError *error = NULL;

/**
 * static InitListStoreSongs():
 *
 * 这个函数用于初始化一个测试用的播放列表，以后也许没用？
 * 起码目前，这个函数仅应由GUI_InitListViewSongs()创建的新线程调用
 *
 * Returns: NULL代表成功
 */

static gpointer InitListStoreSongs(gpointer data)
{
  print_programming("GUI::ListStoreSongs::init()");

  GtkTreeIter iter;

  FILE *list_file = fopen("./data/songlist", "r");

  gchar *tmp_str = g_malloc(10240 * sizeof(gchar));

  while(fgets(tmp_str, 10240, list_file) != NULL)
	{
	  gchar **tmp_vec = g_strsplit(tmp_str, ",", -1);
	  gtk_list_store_append(icep_liststore.liststore_songs, &iter);
	  gtk_list_store_set(icep_liststore.liststore_songs, &iter,
						 SONG_TRACK_NUM, atoi(tmp_vec[0]),
						 SONG_TITLE_STR, tmp_vec[1],
						 SONG_ALBUM_STR, tmp_vec[2],
						 SONG_ARTIST_STR, tmp_vec[3],
						 SONG_LENGTH_INT, atoi(tmp_vec[4]),
						 -1);
	  g_strfreev(tmp_vec);
	}

  g_free(tmp_str);
  fclose(list_file);

  return NULL;
}

/**
 * GUI_InitListViewSongs():
 *
 * 这个函数用于初始化歌曲列表的TreeView;
 *
 * Returns: TRUE代表成功
 */

gboolean GUI_InitListViewSongs(GtkWidget *treeview)
{
  print_programming("GUI::ListViewSongs::init()");

  GtkCellRenderer *render;
  GtkTreeViewColumn *column;

  icep_liststore.liststore_songs = gtk_list_store_new(NUM_SONGLIST,
													  G_TYPE_UINT,
													  G_TYPE_STRING,
													  G_TYPE_STRING,
													  G_TYPE_STRING,
													  G_TYPE_UINT);

  g_thread_create(InitListStoreSongs, NULL, FALSE, &error);
  if(error != NULL)
	{
	  print_err(error->message);
	  g_error_free(error);
	  error = NULL;
	}

  render = gtk_cell_renderer_text_new();
  column = gtk_tree_view_column_new_with_attributes(_("Track"), render,
													"text", SONG_TRACK_NUM,
													NULL);
  gtk_tree_view_column_set_sort_column_id (column, SONG_TRACK_NUM);
  gtk_tree_view_append_column (GTK_TREE_VIEW(treeview), column);

  render = gtk_cell_renderer_text_new();
  column = gtk_tree_view_column_new_with_attributes(_("Title"), render,
													"text", SONG_TITLE_STR,
													NULL);
  gtk_tree_view_column_set_sort_column_id (column, SONG_TITLE_STR);
  gtk_tree_view_append_column (GTK_TREE_VIEW(treeview), column);

  render = gtk_cell_renderer_text_new();
  column = gtk_tree_view_column_new_with_attributes(_("Artist"), render,
													"text", SONG_ARTIST_STR,
													NULL);
  gtk_tree_view_column_set_sort_column_id (column, SONG_ARTIST_STR);
  gtk_tree_view_append_column (GTK_TREE_VIEW(treeview), column);

  render = gtk_cell_renderer_text_new();
  column = gtk_tree_view_column_new_with_attributes(_("Album"), render,
													"text", SONG_ALBUM_STR,
													NULL);
  gtk_tree_view_column_set_sort_column_id (column, SONG_ALBUM_STR);
  gtk_tree_view_append_column (GTK_TREE_VIEW(treeview), column);

  render = gtk_cell_renderer_text_new();
  column = gtk_tree_view_column_new_with_attributes(_("Length"), render,
													"text", SONG_LENGTH_INT,
													NULL);
  gtk_tree_view_column_set_sort_column_id (column, SONG_LENGTH_INT);
  gtk_tree_view_append_column (GTK_TREE_VIEW(treeview), column);


  gtk_tree_view_set_model(GTK_TREE_VIEW(treeview),
						  GTK_TREE_MODEL(icep_liststore.liststore_songs));

  gtk_tree_view_set_rules_hint(GTK_TREE_VIEW(treeview), TRUE);
  gtk_tree_view_set_search_column (GTK_TREE_VIEW (treeview),
								   SONG_TITLE_STR);

  return TRUE;
}
