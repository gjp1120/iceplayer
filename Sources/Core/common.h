/*
 * COMMON Declaration
 *
 * common.h
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
#include <libintl.h>
#include <glib/gi18n.h>
#include <glib.h>

#ifndef __COMMON_H
#define __COMMON_H

#define TTY_FONT_BLUE "\033[34m"
#define TTY_FONT_YELLOW "\033[33m"
#define TTY_FONT_RED "\033[31m"
#define TTY_FONT_BLACK "\033[30m"
#define TTY_FONT_GREEN "\033[32m"

#define PROG_NAME "iceplayer"

#define ICEPLAYER_ICON "@datadir@/iceplayer.png"

#define STRINGS_LENGTH 1024

#define print_debug(x)													\
  g_print(TTY_FONT_YELLOW "Thread&%#x (%s) "							\
		  TTY_FONT_BLUE"Debug:"											\
		  TTY_FONT_BLACK " %s\n", (guint)g_thread_self(),				\
		  __PRETTY_FUNCTION__, x)

#define print_programming(x)											\
  g_print(TTY_FONT_YELLOW "Thread&%#x "									\
		  TTY_FONT_GREEN "Programming:"									\
		  TTY_FONT_BLACK " %s\n", (guint)g_thread_self(), x)

#define print_err(x)													\
  g_printerr(TTY_FONT_YELLOW "Thread&%#x (%s) "							\
			 TTY_FONT_RED "*ERROR*"										\
			 TTY_FONT_BLACK ": %s\n", (guint)g_thread_self(),			\
			 __PRETTY_FUNCTION__, x);


G_BEGIN_DECLS;

gboolean iceplayer_quit(void);

G_END_DECLS;

#endif //__COMMON_H
