#include<gtk/gtk.h>
#ifndef callback_h

#define callback_h

#define _MAKE_CALL_(widget, event)\
void on_##widget##_##event(GtkWidget *wid, gpointer data)

_MAKE_CALL_(menu_new, click);
_MAKE_CALL_(menu_score, click);
_MAKE_CALL_(menu_preference, click);
_MAKE_CALL_(menu_about, click);
_MAKE_CALL_(menu_thank, click);

_MAKE_CALL_(button_clear, click);
_MAKE_CALL_(button_ok, click);

void on_entry_insert_text(GtkWidget *entry, gchar *new_text, int new_text_length, int *position); 


#endif
