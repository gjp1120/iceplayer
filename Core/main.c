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
#include <gtk/gtk.h>
#include "common.h"
#include "gui.h"
#include "config.h"

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
  print_programming("main()");

  print_debug("Gtk::Init()");
  gtk_init(&argc, &argv);

  bindtextdomain(PROG_NAME, "@localedir@");
  bind_textdomain_codeset(PROG_NAME, "UTF-8");
  textdomain(PROG_NAME);

  print_debug("Config::Init()");
  Config_init();

  print_debug("GUI::Init()");
  GUI_init();

  print_debug("Gtk::Main::run()");
  gtk_main();

  return 0;
}
