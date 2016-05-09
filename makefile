preflags = -Wall -g 
flag_comp  = `pkg-config --cflags gtk+-2.0`
flag_link  = `pkg-config --libs gtk+-2.0`

guess_dep = guess.c guess.h
text_play_dep = text_play.c guess.h
callback_dep = callback.c callback.h gui_play.h gui.h
gui_dep = gui.c callback.h gui_play.h gui.h
gui_play_dep = gui_play.c gui_play.h gui.h
main_dep = main.c gui_play.h text_play.h

cc = gcc

final_out = guess
final_dep = guess.o text_play.o callback.o gui.o gui_play.o main.o

$(final_out):$(final_dep)
	$(cc) $(preflags) $(final_dep) -o $(final_out) $(flag_link)

guess.o:$(guess_dep)
	$(cc) -c $(guess_dep)

text_paly.o:$(text_play_dep)
	$(cc) -c $(text_play_dep)

callback.o:$(callback_dep)
	$(cc)  -c $(callback_dep) $(flag_comp)

gui.o:$(gui_dep)
	$(cc) -c $(gui_dep) $(flag_comp)

gui_play.o:$(gui_play_dep)
	$(cc) -c $(gui_play_dep) $(flag_comp)

main.o:$(main_dep)
	$(cc) -c $(main_dep) $(flag_comp)


clear:
	rm -f *.gch
