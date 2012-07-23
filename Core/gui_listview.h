#include <gtk/gtk.h>

#include "common.h"
#include "gui.h"

#ifndef __GUI_LISTVIEW_H
#define __GUI_LISTVIEW_H

G_BEGIN_DECLS;

typedef enum {
  SONG_TRACK_NUM,
  SONG_TITLE_STR,
  SONG_ARTIST_STR,
  SONG_ALBUM_STR,
  SONG_LENGTH_INT,
  NUM_SONGLIST,
}iceplayer_liststore_songs_column;

typedef struct {
  GtkListStore *liststore_songs;
  GtkListStore *liststore_lists;
}iceplayer_ListStoreData_t;

gboolean GUI_InitListViewSongs(GtkWidget *);

G_END_DECLS;

#endif //__GUI_LISTVIEW_H
