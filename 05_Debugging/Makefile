output=

range: main.c
	gcc -O0 -g main.c -o $@
test:
	mkdir tmp
	gdb < scripts/debug1 --args ./range 2>/dev/null | grep @@@ > tmp/test1
	gdb < scripts/debug2 --args ./range 2>/dev/null | grep @@@ > tmp/test2
	
	cmp tmp/test1 examples/test1
	cmp tmp/test2 examples/test2

	make clean

	echo "Both tests passed"
clean:
	rm tmp/*
	rmdir tmp
