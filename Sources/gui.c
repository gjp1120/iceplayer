#include <gtk/gtk.h>

gboolean iceplayer_ui_init(int *argc, char ***argv)
{
    gtk_init(argc, argv);

    return TRUE;
}

