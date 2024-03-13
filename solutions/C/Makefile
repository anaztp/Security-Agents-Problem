run: 
	cc -o main.out main.c
	./main

// Uses The GNU Debugger (gdb) for debugging
debug:
	cc -o main main.c -ggdb
	gdb --tui --quiet --eval-command="b main" --eval-command="tui layout src" --eval-command="winheight src -7" ./main
