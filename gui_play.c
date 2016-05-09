#include<gtk/gtk.h>
#include<stdio.h>
#include<string.h>

#include "guess.h"
#include "gui_play.h"
#include "gui.h"

void reset_input()
{
	int i;
	for(i = 0; i<4; i++)
		gtk_entry_set_text(GTK_ENTRY(entry[i]), "");
	current_in_entry_index=0;
	gtk_widget_grab_focus(entry[0]);
}

void reset_game()
{
	random_num = produce_a_random_number();
	current_times = 0;
	reset_guessed();
	reset_input();
	int i = 0;
	for(; i<8; i++)
		gtk_label_set_text(GTK_LABEL(label[i]), "");
	gtk_image_set_from_pixbuf(GTK_IMAGE(image), picture_buf[0]);
}       

static void do_missed(int state, unsigned int input)
{
	char buf[32];
	sprintf(buf,"%d->%dA%dB", input, state/10, state%10);
	gtk_label_set_text(GTK_LABEL(label[current_times-1]), buf);
	reset_input();
}
static void do_pro_duplicate(unsigned int input)
{
	GtkWidget *dialog;
	gchar info[64];
	sprintf(info, "你已经猜过%d了", input);
	dialog = gtk_message_dialog_new(NULL, 
		 GTK_DIALOG_DESTROY_WITH_PARENT,
		 GTK_MESSAGE_ERROR,
		 GTK_BUTTONS_OK, info);
	gtk_window_set_icon(GTK_WINDOW(dialog), window_icon_buf);
	gtk_window_set_title(GTK_WINDOW(dialog), "输入有误");
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
	reset_input();
}
static void do_win(unsigned int input)
{
	GtkWidget *dialog;
	gchar info[64];
	sprintf(info, "猜对了！你真聪明!\n答案:%d", input);
	dialog = gtk_message_dialog_new(NULL, 
		 GTK_DIALOG_DESTROY_WITH_PARENT,
		 GTK_MESSAGE_INFO,
		 GTK_BUTTONS_OK, info, "title");
	gtk_window_set_icon(GTK_WINDOW(dialog), window_icon_buf);
	gtk_window_set_title(GTK_WINDOW(dialog), "猜对了");
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
	reset_game();
}
static void do_time_out()
{
	GtkWidget *dialog;
	gchar info[64];
	sprintf(info, "很遗憾，你己超时\n正确答案:%d", random_num);
	dialog = gtk_message_dialog_new(NULL, 
		 GTK_DIALOG_DESTROY_WITH_PARENT,
		 GTK_MESSAGE_ERROR,
		 GTK_BUTTONS_OK, info);
	gtk_window_set_icon(GTK_WINDOW(dialog), window_icon_buf);
	gtk_window_set_title(GTK_WINDOW(dialog), "超时");
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
	reset_game();
}
static void do_bad_input(void)
{
	GtkWidget *dialog;
	gchar info[64];
	sprintf(info, "输入数字不完整！\n请输入4个数字");
	dialog = gtk_message_dialog_new(NULL, 
		 GTK_DIALOG_DESTROY_WITH_PARENT,
		 GTK_MESSAGE_ERROR,
		 GTK_BUTTONS_OK, info);
	gtk_window_set_icon(GTK_WINDOW(dialog), window_icon_buf);
	gtk_window_set_title(GTK_WINDOW(dialog), "输入有误");
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
	reset_input();
}

static unsigned int get_input(void)
{
	gchar figures[4];
	unsigned int out;
	int  i;
	for(i=0; i<4; i++)
	{
		char *str = gtk_entry_get_text(GTK_ENTRY(entry[i]));
		if(strcmp(str,"")==0)
			return 0;
		gchar c = str[0];
		figures[i] = c-'0';
	}
	out  = (int)figures[0] * 1000;
	out += (int)figures[1] * 100;
	out += (int)figures[2] * 10;
	out += (int)figures[3];
	return out;
}  

void gui_play_game()
{
	unsigned int current_input = get_input();
	int state;

	if(!current_input)
	{
		do_bad_input();
		return;
	}
	if(!not_guessed(current_input))
	{
		do_pro_duplicate(current_input);
		return;
	}

	regist_guessed(current_input);
	state = compare(random_num, current_input);
	current_times++;
	gtk_image_set_from_pixbuf(GTK_IMAGE(image), picture_buf[current_times-1]);
	if(100 == state)
		do_win(current_input);
	else if(current_times < 8)
		do_missed(state, current_input);
	else
		do_time_out();
}
