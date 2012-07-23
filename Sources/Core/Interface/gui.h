/*
 * gui_callbacks.h
 * Copyright (C) Kevin DeKorte 2006 <kdekorte@gmail.com>
 * 
 * iceplayer is free software.
 * 
 * You may redistribute it and/or modify it under the terms of the
 * GNU General Public License, as published by the Free Software
 * Foundation; either version 3 of the License, or (at your option)
 * any later version.
 * 
 * iceplayer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Gvieneral Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with iceplayer.  If not, write to:
 *  The Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor
 *  Boston, MA  02110-1301, USA.
 */

#include "common.h" 

#ifndef _GUI_CALLBACKS_H_
#define _GUI_CALLBACKS_H_

struct CoreforUI_Object
{
		gboolean (*quit)(void);
};

#endif /* _GUI_CALLBACKS_H_ */
