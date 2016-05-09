/*GUI for guess*/

#include<gtk/gtk.h>
#include "callback.h"
#include "gui_play.h"
#include "gui.h"

void load_picture()
{
	GError *err = NULL;
	int i;
	
	window_icon_buf = gdk_pixbuf_new_from_file(window_icon_path, &err);
	
	for(i = 0; i < TOTAL_PICTURE; i++)
	{
		picture_buf[i] = gdk_pixbuf_new_from_file(picture_path[i], &err);
	}
}

GtkWidget * make_menu()
{
	GtkWidget *menubar;
	GtkWidget *game_menu;
	GtkWidget *game;
	GtkWidget *new;
	GtkWidget *score;
	GtkWidget *quit;

	GtkWidget *set_menu;
	GtkWidget *setting;
	GtkWidget *preference;

	GtkWidget *help_menu;
	GtkWidget *help;
	GtkWidget *about;
	GtkWidget *thank;

	GtkWidget *sep;

	menubar   = gtk_menu_bar_new();
	game_menu = gtk_menu_new();
	set_menu  = gtk_menu_new();
	help_menu = gtk_menu_new();

	game  = gtk_menu_item_new_with_mnemonic("游戏(_G)");
	new   = gtk_image_menu_item_new_from_stock(GTK_STOCK_NEW, NULL);
	score = gtk_menu_item_new_with_label("得分");
	sep   = gtk_separator_menu_item_new();
	quit  = gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT, NULL);

	setting = gtk_menu_item_new_with_mnemonic("设置(_S)");
	preference = gtk_menu_item_new_with_label("首选项");

	help    = gtk_menu_item_new_with_mnemonic("帮助(_H)");
	about	= gtk_menu_item_new_with_label("游戏简介");
	thank	= gtk_menu_item_new_with_label("致谢");

	
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(game), game_menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(game_menu), new);
	gtk_menu_shell_append(GTK_MENU_SHELL(game_menu), score);
	gtk_menu_shell_append(GTK_MENU_SHELL(game_menu), sep);
	gtk_menu_shell_append(GTK_MENU_SHELL(game_menu), quit);

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(setting), set_menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(set_menu), preference);

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(help), help_menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), about);
	gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), thank);

	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), game);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), setting);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), help);

	/*绑定事件回调
	 *   ......	
	 */
	g_signal_connect(G_OBJECT(about), "activate", G_CALLBACK(on_menu_about_click), NULL);
	g_signal_connect(G_OBJECT(thank), "activate", G_CALLBACK(on_menu_thank_click), NULL);
	g_signal_connect(G_OBJECT(quit), "activate", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(new)  , "activate", G_CALLBACK(on_menu_new_click), NULL);
	return menubar;
}

void put_label(GtkWidget* fix)
{
	int i;
	gint pos_x = 16, pos_y = 28;
	for(i=0; i<8; i++ )
	{
		label[i] = gtk_label_new("");
		gtk_fixed_put(GTK_FIXED(fix), label[i], pos_x, pos_y);
		pos_y += 25;
	}
}

void put_entry(GtkWidget *fix)
{
	int i;
	gint pos_x = 140, pos_y = 24;
	PangoFontDescription *pfd;
    	pfd = pango_font_description_from_string("华文楷体 45");
    	
	for(i=0; i<4; i++)
	{
		entry[i] = gtk_entry_new();
		gtk_widget_set_size_request(entry[i], 50, 50);
		gtk_fixed_put(GTK_FIXED(fix),entry[i], pos_x, pos_y);
		gtk_widget_modify_font(GTK_WIDGET(entry[i]),pfd);
		g_signal_connect(G_OBJECT(entry[i]), "insert_text", G_CALLBACK(on_entry_insert_text), NULL);
		GTK_WIDGET_SET_FLAGS (entry[i], GTK_CAN_FOCUS); 
		pos_x += 60;
	}
}

void put_button(GtkWidget *fix)
{
	GtkWidget *button_clear = gtk_button_new_with_label("清除");
	gtk_widget_set_size_request(button_clear, 80, 35);

	GtkWidget *button_ok     = gtk_button_new_with_label("确定");
	gtk_widget_set_size_request(button_ok, 80, 35);

	gtk_fixed_put(GTK_FIXED(fix), button_clear, 160, 219);
	gtk_fixed_put(GTK_FIXED(fix), button_ok,     270, 219);

	g_signal_connect(G_OBJECT(button_clear), "clicked", G_CALLBACK(on_button_clear_click), NULL);
	g_signal_connect(G_OBJECT(button_ok), "clicked", G_CALLBACK(on_button_ok_click), NULL);
}

void put_picture(GtkWidget *fix)
{
	image = gtk_image_new();
	gtk_widget_set_size_request(image, 250, 120);
	gtk_fixed_put(GTK_FIXED(fix), image, 130, 91);
	gtk_image_set_from_file(GTK_IMAGE(image), "./icon/test.png");
}

void show_window(int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *menubar;

	GtkWidget *frame_label;
	GtkWidget *frame_entry;
	GtkWidget *fix;

	gtk_init(&argc, &argv);
	load_picture();

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(window), "猜数字");
	gtk_window_set_icon(GTK_WINDOW(window), window_icon_buf);

	frame_label = gtk_frame_new("输出");
	gtk_frame_set_shadow_type(GTK_FRAME(frame_label), GTK_SHADOW_ETCHED_IN);
	gtk_widget_set_size_request(frame_label, 120, 250);

	frame_entry = gtk_frame_new("输入");
	gtk_frame_set_shadow_type(GTK_FRAME(frame_entry), GTK_SHADOW_ETCHED_IN);
	gtk_widget_set_size_request(frame_entry, 250, 80);
	
	fix = gtk_fixed_new();

	vbox = gtk_vbox_new(FALSE, 0);
	menubar = make_menu();

	gtk_container_add(GTK_CONTAINER(window), vbox);
	gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 3);
	gtk_box_pack_start(GTK_BOX(vbox), fix, TRUE, TRUE, 1);
	gtk_fixed_put(GTK_FIXED(fix), frame_label, 4, 4);
	put_label(fix);
	gtk_fixed_put(GTK_FIXED(fix), frame_entry, 130,4);
	put_entry(fix);
	put_button(fix);
	put_picture(fix);
	
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_widget_show_all(window);
	reset_game();
	gtk_main();
}

