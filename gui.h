#include<gtk/gtk.h>
#ifndef gui_h

#define gui_h
/*
#define icon_dir "./icon"
#define icon_type ".png"
#define icon_name "window_icon"

#define make_pic_path(dir, name, type)\
dir##name##icon_type

static char *window_icon_path =  make_pic_path(icon_dir, icon_type, icon_type);

static char *picture_path[8]  = {make_pic_path(icon_dir,"1", icon_type),
				 make_pic_path(icon_dir, 2, icon_type),
				 make_pic_path(icon_dir, 3, icon_type),
				 make_pic_path(icon_dir, 4, icon_type),
				 make_pic_path(icon_dir, 5, icon_type),
				 make_pic_path(icon_dir, 6, icon_type),
				 make_pic_path(icon_dir, 7, icon_type),
				 make_pic_path(icon_dir, 8, icon_type)};
*/


 static char *window_icon_path = "./icon/window_icon.png";
 static char *picture_path[8] = {"./icon/chun.png", "./icon/chun2.png", "./icon/xia.png" ,"./icon/xia2.png",\
		       		  "./icon/qiu.png" , "./icon/qiu2.png" , "./icon/dong.png","./icon/dong2.png"};


GdkPixbuf *window_icon_buf;
GdkPixbuf *picture_buf[8];
static int TOTAL_PICTURE = 8; 

GtkWidget *label[8];
GtkWidget *entry[4];
GtkWidget *image;

#endif
