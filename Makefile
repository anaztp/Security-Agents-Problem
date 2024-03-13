run: 
	cc -o main main.c
	./main

debug:
	cc -o main main.c -ggdb
	gdb --tui --quiet --eval-command="b main" --eval-command="tui layout src" --eval-command="winheight src -7" ./main
