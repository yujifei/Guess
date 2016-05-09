#include<gtk/gtk.h>
#include<string.h>
#include<stdio.h>
#include "callback.h"
#include "gui_play.h"
#include "gui.h"


_MAKE_CALL_(menu_about, click)
{
	GtkWidget *dialog;
	const gchar *info = "输入4个不同数字，输出形式为nAmB，\nn表示猜对数字且位置正确的数字个数，\
			    \nm表示猜对数字但位置不对的数字个数，\n最多8次机会，祝你好运";
	dialog = gtk_message_dialog_new(data,
		 GTK_DIALOG_DESTROY_WITH_PARENT,
		 GTK_MESSAGE_INFO,
		 GTK_BUTTONS_OK, info, "title");
	gtk_window_set_title(GTK_WINDOW(dialog), "游戏简介");
	gtk_window_set_icon(GTK_WINDOW(dialog), window_icon_buf);
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}

_MAKE_CALL_(menu_thank, click)
{
	GtkWidget *dialog = gtk_about_dialog_new();

	gtk_about_dialog_set_name(GTK_ABOUT_DIALOG(dialog), "猜数字");
	gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), "1.0");
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog), "Copyright(c) 2009 庾吉飞编写");
	gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog), "猜数字是一个简单的而且十分无聊的游戏，它只会让你知道人类有多变态.如果发现有人在使用这个程序的话他很可能需要送去检查一下精神状态喔!");
	gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog), "http://www.gtk.org");
	gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog), window_icon_buf);
	gtk_window_set_icon(GTK_WINDOW(dialog), window_icon_buf);


	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}

_MAKE_CALL_(menu_new, click)
{
	reset_game();
}

static void focus_next(GtkWidget *c_entry)
{
	int i = 0, current;
	for(; i<4; i++)
		if((int)c_entry == (int)entry[i])
			current = i;
	if(current == 3)
		gtk_widget_grab_focus(entry[0]);
	else
		gtk_widget_grab_focus(entry[current+1]);
}

static int in_current_entry(gchar c)
{
	int i = 0;
	for(;i<current_in_entry_index; i++)
		if(current_in_entry[i] == c)
			return 1;
	return 0;
}
void on_entry_insert_text(GtkWidget *entry, gchar *new_text, int new_text_length, int *position)
{
	if(new_text[0]<'0' || new_text[0]>'9')
		new_text[0] = '\0';

	else if(in_current_entry(new_text[0]))
		new_text[0] = '\0';

	else if(strlen(gtk_entry_get_text(GTK_ENTRY(entry))) > 0)
		new_text[0] = '\0';
	else
	{
		current_in_entry[current_in_entry_index++] = new_text[0];
		focus_next(entry);
	}
}

_MAKE_CALL_(button_clear, click)
{
	int i;
	for(i = 0; i<4; i++)
		gtk_entry_set_text(GTK_ENTRY(entry[i]), "");
	current_in_entry_index = 0;
	gtk_widget_grab_focus(entry[0]);
}

_MAKE_CALL_(button_ok, click)
{
	gui_play_game();
}
