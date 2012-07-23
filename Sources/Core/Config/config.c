/*
 * Config
 *
 * config.c
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
#include "config.h"

/**
 * SECTION: config
 * @Short_description: 配置模块，隔离配置实现
 * @Title: 配置模块
 * @Include: config.h
 *
 * 配置模块
 * 请所有的配置信息都使用这里的函数保存和读取
 */

static const gchar *module_name = "Config";
static GKeyFile *keyfile;
static __thread GError *error = NULL;

gint Config_getInt(const gchar *group_name, const gchar *key)
{
  print_programming("Config::getInt()");

  gint ret;

  ret = g_key_file_get_integer(keyfile, group_name, key, &error);
  if(error != NULL)
	{
	  print_err(error->message);
	  g_error_free(error);
	  error = NULL;
	}

  return ret;
}

gchar *Config_getStr(const gchar *group_name, const gchar *key)
{
  print_programming("Config::getStr()");

  gchar *ret;

  ret = g_key_file_get_string(keyfile, group_name, key, &error);
  if(error != NULL)
	{
	  print_err(error->message);
	  g_error_free(error);
	  error = NULL;
	}

  return ret;
}

gboolean Config_getBool(const gchar *group_name, const gchar *key)
{
  print_programming("Config::getBool()");

  gboolean ret;

  ret = g_key_file_get_boolean(keyfile, group_name, key, &error);
  if(error != NULL)
	{
	  print_err(error->message);
	  g_error_free(error);
	  error = NULL;
	}

  return ret;
}

void Config_setBool(const gchar *group_name,const gchar *key, gboolean _val)
{
  print_programming("Config::setBool()");

  g_key_file_set_boolean(keyfile, group_name, key, _val);
}

void Config_setInt(const gchar *group_name, const gchar *key, gint _val)
{
  print_programming("Config::setInt()");

  g_key_file_set_integer(keyfile, group_name, key, _val);
}

void Config_setStr(const gchar *group_name, const gchar *key, const gchar *_val)
{
  print_programming("Config::setStr()");

  g_key_file_set_string(keyfile, group_name, key, _val);
}

/**
 * Config_fini():
 *
 * 负责收尾工作：将所有配置保存到文件
 *
 * Returns: 是否成功结束
 */

gboolean Config_fini(gpointer data)
{
  print_programming("Config::fini()");

  gsize length;
  gchar *temp = g_key_file_to_data(keyfile, &length, &error);
  if(error != NULL)
	{
	  print_err(error->message);
	  g_error_free(error);
	  error = NULL;
	}
  
  g_file_set_contents("./data/iceplayer.conf", temp, length, &error);
  if(error != NULL)
	{
	  print_err(error->message);
	  g_error_free(error);
	  error = NULL;
	}

  g_key_file_free(keyfile);
  keyfile = NULL;

  return FALSE;
}

/**
 * Config_init():
 *
 * 负责初始化配置系统。
 * 这个函数应在所有自定义初始化函数之前运行。
 *
 * Returns: 初始化是否成功
 */

gboolean Config_init()
{
  print_programming("Config::init()");

  keyfile = g_key_file_new();

  if(!g_key_file_load_from_file(keyfile, "./data/iceplayer.conf",
								G_KEY_FILE_KEEP_COMMENTS |
								G_KEY_FILE_KEEP_TRANSLATIONS, &error))
	{
	  print_err(error->message);
	  g_error_free(error);
	  error = NULL;
	}


  if(!g_key_file_has_group(keyfile, "GUI"))
	{
	  print_err("GUI group not found");
	}

  return TRUE;
}
