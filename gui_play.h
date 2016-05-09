#include<gtk/gtk.h>
#ifndef gui_play_h

#define gui_play_h

gchar current_in_entry[4];
int current_in_entry_index;

unsigned int random_num;
int current_times;
void show_window(int argc, char *argv[]);

#define gui_mode_run(argc,argv) show_window(argc, argv)

void reset_game(void);
void reset_input(void);
void gui_play_game(void);

#endif
