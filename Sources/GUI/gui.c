/*
 * GUI 
 *
 * gui.c
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
#include "gui.h"
#include "../common.h"
#include "about.h"
#include "config.h"
#include "signal.h"
#include "gui_listview.h"

/**
 * SECTION: gui
 * @Short_description: 播放器用户图形界面的实现
 * @Title: 图形界面
 * @Include: gui.h
 *
 * 负责构建播放器的图形界面
 */

static const gchar *module_name = "GUI";
static iceplayer_GuiData_t iceplayer_gui;
static __thread GError *error = NULL;
static GtkSettings *settings;

/*
 * do_window_main_fullscreen():
 * 
 * 使主窗口在全屏模式之间切换
 */

static void do_window_main_fullscreen(void)
{
  print_programming("GUI::MainWindow::do_fullscreen()");

  if(gdk_window_get_state(GDK_WINDOW(iceplayer_gui.window_main->window))
	 & GDK_WINDOW_STATE_FULLSCREEN)
	{
	  gtk_window_unfullscreen(GTK_WINDOW(iceplayer_gui.window_main));
	}
  else
	{
	  gtk_window_fullscreen(GTK_WINDOW(iceplayer_gui.window_main));
	}
}

/*
 * GtkToggleActionEntry[] iceplayer_mw_menubar_toggleactions:
 * GtkActionEntry[] iceplayer_mw_menubar_actions:
 *
 * 主窗体的MenuBar内容，快捷键以及回调函数
 */

static GtkActionEntry iceplayer_mw_menubar_actions[] = 
  {
	{"MusicMenu", NULL, N_("_Music")},
	{"New_Playlist", NULL, N_("New Playlist"), "<control>N",
	 N_("Create a new playlist"), NULL},
	{"Add_Music", GTK_STOCK_ADD, N_("Import _File..."), NULL,
	 N_("Choose file to be added to the Playlist"), NULL},
	{"Add_Folder", GTK_STOCK_ADD, N_("_Import Folder..."), NULL,
	 N_("Choose folder to be added to the Playlist"), NULL},
	{"AutoScan", NULL, N_("_Scan Removable Media"), NULL,
	 N_("Scan for new Removable Media"), NULL},
	{"Save_Playlist", NULL, N_("_Save to File..."), "<control><alt>S",
	 N_("Save a playlist to a file"), NULL},
	{"Quit", NULL, N_("_Quit"), "<control>q",
	 N_("Quit the iceplayer"), G_CALLBACK(iceplayer_quit)},

	{"EditMenu", NULL, N_("_Edit")},
	{"CutItem", NULL, N_("Cu_t"), "<control>X", N_("Cut selection"), NULL},
	{"CopyItem", NULL, N_("_Copy"), "<control>C", N_("Copy selection"), NULL},
	{"PasteItem", NULL, N_("_Paste"), "<control>V",
	 N_("Paste selection"), NULL},
	{"SelectALL", NULL, N_("Select All"), "<control>A",
	 N_("Select all songs"), NULL},
	{"DeSelectALL", NULL, N_("Deselect All"), NULL,
	 N_("Deselect all songs"), NULL},
	{"Add_to_Playlist", NULL, N_("_Add to Playlist")},
	{"Remove_from_Playlist", NULL, N_("Remove from Playlist"), NULL,
	 N_("Remove each selected song from the playlist"), NULL},
	{"Delete_from_Disk", NULL, N_("Delete from Disk"), NULL,
	 N_("Delete each selected song from the disk"), NULL},

	{"ViewMenu", NULL, N_("_View")},
	{"Mini_Mode", NULL, N_("M_ini Mode"), NULL, 
	 N_("Make the main window smaller"), NULL},

	{"ControlMenu", NULL, N_("_Control")},
	{"Play", NULL, N_("_Play"), NULL, N_("Start playback"), NULL},

	{"SettingsMenu", NULL, N_("Settings")},

	{"HelpMenu", NULL, N_("_Help")},
	{"About", NULL, N_("_About"), "F1",
	 N_("Show program info"), G_CALLBACK(GUI_Dialogs_About)}
  };

//iceplayer_mw_menubar_actions的条目数
static const gint sz_actions = G_N_ELEMENTS(iceplayer_mw_menubar_actions);

static GtkToggleActionEntry iceplayer_mw_menubar_toggleactions[] = 
  {
	{"Fullscreen_Mode", NULL, N_("_Fullscreen Mode"), "F11",
	 N_("Make the main window fullscreen"), 
	 G_CALLBACK(do_window_main_fullscreen), FALSE},
  };

//iceplayer_mw_menubar_toggleactions的条目数
static const gint sz_toggleactions = \
  G_N_ELEMENTS(iceplayer_mw_menubar_toggleactions);

/*
 *const gchar *iceplayer_gui_menu_xml:
 *菜单结构
 */

static const gchar *iceplayer_gui_menu_xml = 
  "<ui>"
  "  <menubar name='MenuBar'>"
  "	 <menu action='MusicMenu'>"
  "	   <menuitem action='New_Playlist'/>"
  "	   <separator/>"
  "	   <menuitem action='Add_Music'/>"
  "	   <menuitem action='Add_Folder'/>"
  "	   <menuitem action='AutoScan'/>"
  "	   <separator/>"
  "	   <menuitem action='Save_Playlist'/>"
  "	   <separator/>"
  "	   <menuitem action='Quit'/>"
  "	 </menu>"
  "	 <menu action='EditMenu'>"
  "	   <menuitem action='CutItem'/>"
  "	   <menuitem action='CopyItem'/>"
  "	   <menuitem action='PasteItem'/>"
  "	   <separator/>"
  "	   <menuitem action='SelectALL'/>"
  "	   <menuitem action='DeSelectALL'/>"
  "	   <separator/>"
  "	   <menu action='Add_to_Playlist'/>"
  "	   <separator/>"
  "	   <menuitem action='Remove_from_Playlist'/>"
  "	   <menuitem action='Delete_from_Disk'/>"
  "	 </menu>"
  "	 <menu action='ViewMenu'>"
  "	   <menuitem action='Mini_Mode'/>"
  "	   <menuitem action='Fullscreen_Mode'/>"
  "	 </menu>"
  "	 <menu action='ControlMenu'>"
  "	   <menuitem action='Play'/>"
  "	   <separator/>"
  "	 </menu>"
  "	 <menu action='SettingsMenu'>"
  "	 </menu>"
  "	 <menu action='HelpMenu'>"
  "	   <menuitem action='About'/>"
  "	 </menu>"
  "  </menubar>"
  "</ui>";


/**
 * static GUI_InitMainWindowLayout():
 *
 * 主窗体内容整理
 */

static void GUI_InitMainWindowLayout(void)
{
  print_programming("GUI::MainWindow::layout_init()");

  GtkWidget *vbox_main = gtk_vbox_new(FALSE, 0);
  GtkWidget *menubar = \
	gtk_ui_manager_get_widget(iceplayer_gui.uimgr_main, "/MenuBar");

  gtk_box_pack_start(GTK_BOX(vbox_main), menubar, FALSE, FALSE, 0);

  GtkWidget *sw_tw_lists = gtk_scrolled_window_new(NULL, NULL);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(sw_tw_lists),
								 GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
  gtk_container_add(GTK_CONTAINER(sw_tw_lists), iceplayer_gui.treeview_lists);

GtkWidget *sw_tw_songs = gtk_scrolled_window_new(NULL, NULL);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(sw_tw_songs),
								 GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
  gtk_container_add(GTK_CONTAINER(sw_tw_songs), iceplayer_gui.treeview_songs);

  GtkWidget *vbox_infobar = gtk_vbox_new(FALSE, 0);

  GtkWidget *hbox_infobar_title = gtk_hbox_new(FALSE, 0);
  gtk_label_set_justify(GTK_LABEL(iceplayer_gui.infobar_label_title),
						GTK_JUSTIFY_LEFT);
  gtk_box_pack_start(GTK_BOX(hbox_infobar_title),
					 iceplayer_gui.infobar_label_title, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox_infobar), hbox_infobar_title,
					 FALSE, FALSE, 0);

  GtkWidget *hbox_infobar_msg = gtk_hbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX(hbox_infobar_msg),
					 iceplayer_gui.infobar_label, FALSE, FALSE, 0);
  gtk_label_set_justify(GTK_LABEL(iceplayer_gui.infobar_label),
						GTK_JUSTIFY_LEFT);
  gtk_box_pack_start(GTK_BOX(vbox_infobar), hbox_infobar_msg, FALSE, FALSE, 0);

  gtk_box_pack_start(GTK_BOX(gtk_info_bar_get_content_area(GTK_INFO_BAR(iceplayer_gui.infobar))), vbox_infobar, FALSE, FALSE, 10);

  GtkWidget *vbox_list = gtk_vbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox_list), iceplayer_gui.infobar,
					 FALSE, FALSE, 0);
  gtk_box_pack_end(GTK_BOX(vbox_list), sw_tw_songs, TRUE, TRUE, 0);

  gtk_paned_add1(GTK_PANED(iceplayer_gui.hpaned_main),
				 sw_tw_lists);
  gtk_paned_add2(GTK_PANED(iceplayer_gui.hpaned_main),
				 vbox_list);
  gtk_paned_set_position(GTK_PANED(iceplayer_gui.hpaned_main),
						 Config_getInt(module_name, "window_main_paned_pos"));

  gtk_box_pack_start(GTK_BOX(vbox_main), iceplayer_gui.hpaned_main,
					 TRUE, TRUE, 0);
  gtk_box_pack_end(GTK_BOX(vbox_main), iceplayer_gui.statusbar_main,
				   FALSE, FALSE, 0);
  gtk_container_add(GTK_CONTAINER(iceplayer_gui.window_main), vbox_main);
}

/**
 * static GUI_InitMainWindowState():
 *
 * 初始化主窗口，菜单中按钮状态
 */

static void GUI_InitMainWindowState(void)
{
  print_programming("GUI::MainWindow::state_init()");

  if(Config_getBool(module_name, "window_main_is_fullscreen"))
	{
	  GtkToggleAction *ta = GTK_TOGGLE_ACTION(gtk_action_group_get_action(iceplayer_gui.actiongroup_main, "Fullscreen_Mode"));
	  gtk_toggle_action_set_active(ta, TRUE);
	}

  gtk_widget_hide_all(iceplayer_gui.infobar);
}

/**
 *static GUI_ConnectMainWindowSignals():
 *
 *为主窗体和组件连接信号
 */

static void GUI_ConnectMainWindowSignals(void)
{
  print_programming("GUI::MainWindow::connect_signals()");

  struct SignalData{
	gulong signalID;
  };

}

/**
 * static GUI_CreateMainWindow():
 *
 * 建立主窗体
 */

static void GUI_CreateMainWindow(void)
{
  print_programming("GUI::MainWindow::init()");

  iceplayer_gui.window_main = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name(iceplayer_gui.window_main, "iceplayer_WindowMain");
  gtk_window_set_title(GTK_WINDOW(iceplayer_gui.window_main),
					   "iceplayer Dev 5.0");
  gtk_window_set_default_size(GTK_WINDOW(iceplayer_gui.window_main),
							  Config_getInt(module_name, "window_main_width"),
							  Config_getInt(module_name, "window_main_height"));
  gtk_window_move(GTK_WINDOW(iceplayer_gui.window_main), 
				  Config_getInt(module_name, "window_main_x"),
				  Config_getInt(module_name, "window_main_y"));
  g_signal_connect(iceplayer_gui.window_main, "delete-event",
				   G_CALLBACK(iceplayer_quit), NULL);

  //从这里开始，全是初始化UIManager的代码
  iceplayer_gui.actiongroup_main = gtk_action_group_new("iceplayer Actions");
  gtk_action_group_set_translation_domain(iceplayer_gui.actiongroup_main,
										  PROG_NAME);
  gtk_action_group_add_actions(iceplayer_gui.actiongroup_main,
							   iceplayer_mw_menubar_actions,
							   sz_actions, NULL);
  gtk_action_group_add_toggle_actions(iceplayer_gui.actiongroup_main,
									  iceplayer_mw_menubar_toggleactions,
									  sz_toggleactions, NULL);
  iceplayer_gui.uimgr_main = gtk_ui_manager_new();
  gtk_ui_manager_insert_action_group(iceplayer_gui.uimgr_main,
									 iceplayer_gui.actiongroup_main, 0);
  if(!gtk_ui_manager_add_ui_from_string(iceplayer_gui.uimgr_main,
										iceplayer_gui_menu_xml, -1,
										&error))
	{
	  print_err(error->message);
	  g_error_free(error);
	  gtk_main_quit();
	}

  gtk_window_add_accel_group(GTK_WINDOW(iceplayer_gui.window_main),
			         gtk_ui_manager_get_accel_group(iceplayer_gui.uimgr_main));
  //到此为止，UIManager完成

  iceplayer_gui.hpaned_main = gtk_hpaned_new();
  gtk_widget_set_name(iceplayer_gui.hpaned_main, "HPaned");
  iceplayer_gui.treeview_lists = gtk_tree_view_new();
  gtk_widget_set_name(iceplayer_gui.treeview_lists, "TreeViewLists");
  iceplayer_gui.treeview_songs = gtk_tree_view_new();
  gtk_widget_set_name(iceplayer_gui.treeview_songs, "TreeViewSongs");
  GUI_InitListViewSongs(iceplayer_gui.treeview_songs);
  iceplayer_gui.statusbar_main = gtk_statusbar_new();
  gtk_widget_set_name(iceplayer_gui.statusbar_main, "StatusBar");
  iceplayer_gui.infobar = gtk_info_bar_new();
  gtk_widget_set_name(iceplayer_gui.infobar, "InfoBar");
  iceplayer_gui.infobar_label_title = gtk_label_new("");
  iceplayer_gui.infobar_label = gtk_label_new("");

  GUI_InitMainWindowLayout();
  GUI_ConnectMainWindowSignals();

  gtk_widget_show_all(iceplayer_gui.window_main);

  GUI_InitMainWindowState();
}

/**
 * GUI_fini():
 *
 * 完成最后的清理工作,同时保存GUI状态;
 *
 * Returns: FALSE表示成功
 */

gboolean GUI_fini(void)
{
  print_programming("GUI::quit()");
  
  if(gdk_window_get_state(GDK_WINDOW(iceplayer_gui.window_main->window))
	 & GDK_WINDOW_STATE_FULLSCREEN)
	{
	  Config_setBool(module_name, "window_main_is_fullscreen", TRUE);
	}
  else
	{
	  gint main_window_width = 0;
	  gint main_window_height = 0;

	  gint main_window_x = 0;
	  gint main_window_y = 0;

	  Config_setBool(module_name, "window_main_is_fullscreen", FALSE);
	  gtk_window_get_size(GTK_WINDOW(iceplayer_gui.window_main),
						  &main_window_width, &main_window_height);
	  gtk_window_get_position(GTK_WINDOW(iceplayer_gui.window_main),
							  &main_window_x, &main_window_y);
	  Config_setInt(module_name, "window_main_width", main_window_width);
	  Config_setInt(module_name, "window_main_height", main_window_height);
	  Config_setInt(module_name, "window_main_x", main_window_x);
	  Config_setInt(module_name, "window_main_y", main_window_y);

	  Config_setInt(module_name, "window_main_paned_pos",
					gtk_paned_get_position(GTK_PANED(iceplayer_gui.hpaned_main)));
	  
	}

  return FALSE;
}

/**
 * GUI_init():
 *
 * 初始化图形用户界面(主窗口)，注意：这个函数只应被调用一次
 *
 * Returns: 初始化是否成功
 */

gboolean GUI_init(void)
{
  print_programming("GUI::init()");

  static gboolean gui_is_inited = FALSE;

  if(gui_is_inited) return FALSE;

  settings = gtk_settings_get_default();

  if(g_file_test("./data/gtkrc", G_FILE_TEST_IS_REGULAR))
	{
	  gtk_rc_add_default_file("./data/gtkrc");
	  gtk_rc_reparse_all();

	  if(settings != NULL)
		{
		  gtk_rc_reparse_all_for_settings(settings, TRUE);
		}
	}
  else
	{
	  print_err("./gtkrc不存在!");
	}

  if(!gtk_window_set_default_icon_from_file(ICEPLAYER_ICON, &error))
	{
	  print_err(error->message);
	  g_error_free(error);
	  error = NULL;
	}

  GUI_CreateMainWindow();

  GUI_MainWindow_showinfo(_("Welcome to iceplayer!"), _("iceplayer 5.0 Dev1"),
						  10, GTK_MESSAGE_INFO);

  return TRUE;
}

/**
 * GUI_Get_Datastruct():
 *
 * 仅供内部函数使用，这就是说：不要在插件中调用这个函数，一旦调用，后果自负^_^
 *
 * Returns: 到iceplayer_GuiData_t的指针
 */

iceplayer_GuiData_t *GUI_Get_Datastruct(void)
{
  print_programming("GUI::Get_Datastruct()");

  return &iceplayer_gui;
}

/**
 * static clean_after_showinfo():
 *
 * 这个函数仅供GUI_MainWindow_showinfo()调用，用于在定义时间后隐藏InfoBar
 *
 * Returns: 一定为FALSE，代表成功
 */


static gboolean clean_after_showinfo(gpointer data)
{
  print_programming("GUI::MainWindow::showinfo --> clean_after()");
  
  gtk_widget_hide_all(iceplayer_gui.infobar);
  return FALSE;
}

/**
 * GUI_MainWindow_showinfo():
 *
 * 在主窗口的InfoBar中显示信息
 */

void GUI_MainWindow_showinfo(const gchar *title_str, const gchar *info_str,
							 const guint timeout, GtkMessageType type)
{
  print_programming("GUI::MainWindow::showinfo()");

  gchar *markup_title = \
	g_markup_printf_escaped("<span weight='bold'>%s</span>", title_str);
  gtk_label_set_markup(GTK_LABEL(iceplayer_gui.infobar_label_title),
					   markup_title);
  g_free(markup_title);

  gtk_label_set_label(GTK_LABEL(iceplayer_gui.infobar_label), info_str);
  gtk_info_bar_set_message_type(GTK_INFO_BAR(iceplayer_gui.infobar), type);

  gtk_widget_show_all(iceplayer_gui.infobar);

  g_timeout_add_seconds(timeout, clean_after_showinfo, NULL);
}
