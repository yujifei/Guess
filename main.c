#include<stdlib.h>
#include "text_play.h"
#include "gui_play.h"

int is_gui_mode(void)
{
	if(getenv("DISPLAY"))
		return 1;
	return 0;
}

int main(int argc, char *argv[])
{
	if(is_gui_mode())
		gui_mode_run(argc, argv);

	else
		text_mode_run();
	return 0;
}
