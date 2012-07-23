/*
 * Main
 *
 * main.c
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
#include <gmodule.h>

/**
 * SECTION: main
 * @Short_description: 播放器入口函数
 * @Title: 主函数
 * @Include: 
 *
 */

static const gchar *module_name = "Main";

int main(int argc, char **argv)
{
  gchar *gui_module_path = g_module_build_path(".", "iceplayer_gui");
  GModule *gui_mod = g_module_open(gui_module_path, G_MODULE_BIND_LAZY);

	int (*ui_init_func)(int *, char ***);
	g_module_symbol(gui_mod, "iceplayer_ui_init", (gpointer *)&ui_init_func);
  ui_init_func(&argc, &argv);


  return 0;
}
