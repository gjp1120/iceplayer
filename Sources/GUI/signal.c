/*
 * 回调函数
 *
 * signal.c
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
#include "common.h"
#include "gui.h"
#include "signal.h"

/**
 * SECTION: signal
 * @Short_description: 回调函数的实现
 * @Title: 回调模块
 * @Include: signal.h
 *
 * 负责实现各种回调函数
 */

static const gchar *module_name = "Signal";
static __thread GError *error = NULL;

