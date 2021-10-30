move: move.c
	gcc -g move.c -o $@

protect.so: protect.c
	gcc -shared -fPIC protect.c -o protect.so -ldl

test:
	make _test 2> tmp | grep "@@@>"

_test:
	make move
	make protect.so
	-make clean
	cp originals/* source_tests
	echo "bp"

	# successful tests
	./move source_tests/test1 dest_tests/test1
	if cmp dest_tests/test1 originals/test1 ; then \
		echo -n "@@@"; \
		echo "> passed"; \
		else echo "> failed"; \
	fi

	./move source_tests/test2 dest_tests/test2
	if cmp dest_tests/test2 originals/test2 ; then \
		echo -n "@@@"; \
		echo "> passed"; \
		else echo "> failed"; \
	fi

	./move source_tests/test3 dest_tests/test3
	if cmp dest_tests/test3 originals/test3 ; then \
		echo -n "@@@"; \
		echo "> passed"; \
		else echo "> failed"; \
	fi

	./move source_tests/test4 dest_tests/test4
	if cmp dest_tests/test4 originals/test4 ; then \
		echo -n "@@@"; \
		echo "> passed"; \
		else echo "> failed"; \
	fi

	./move source_tests/test5 dest_tests/test5
	if cmp dest_tests/test5 originals/test5 ; then \
		echo -n "@@@"; \
		echo "> passed"; \
		else echo "> failed"; \
	fi

	-make clean
	cp originals/* source_tests

	# file does not exists
	./move source_tests/bad dest_tests/bad || if [ $$? -eq 1 ]; \
		then \
			echo -n "@@@"; \
			echo "> passed"; \
		else \
			echo -n "@@@"; \
			echo "> failed"; \
		fi
	
	# cannot read
	strace -e fault=read:when=5 ./move source_tests/test2 dest_tests/test2 || if [ $$? -eq 4 ] && [ ! -f dest_tests/test2 ]; \
		then \
			echo -n "@@@"; \
			echo "> passed"; \
		else \
			echo -n "@@@"; \
			echo "> failed"; \
		fi

	# cannot write
	strace -e fault=write:when=5 ./move source_tests/test3 dest_tests/test3 || if [ $$? -eq 8 ] && [ ! -f dest_tests/test2 ]; \
		then \
			echo -n "@@@"; \
			echo "> passed"; \
		else \
			echo -n "@@@"; \
			echo "> failed"; \
		fi

	# cannot close
	strace -e fault=close:when=3 ./move source_tests/test4 dest_tests/test4 || if [ $$? -eq 16 ]; \
		then \
			echo -n "@@@"; \
			echo "> passed"; \
		else \
			echo -n "@@@"; \
			echo "> failed"; \
		fi
	strace -e fault=close:when=4 ./move source_tests/test5 dest_tests/test5 || if [ $$? -eq 32 ]; \
		then \
			echo -n "@@@"; \
			echo "> passed"; \
		else \
			echo -n "@@@"; \
			echo "> failed"; \
		fi

	-make clean
	cp originals/* source_tests

	# cannot unlink
	strace -e fault=unlink:when=1 ./move source_tests/test5 dest_tests/test5 || if [ $$? -eq 64 ]; \
		then \
			echo -n "@@@"; \
			echo "> passed"; \
		else \
			echo -n "@@@"; \
			echo "> failed"; \
		fi


	# protected file
 
	LD_PRELOAD=$PWD/protect.so ./move source_tests/test5_PROTECTED dest_tests/test5 || if [ -f source_tests/test5_PROTECTED ]; \
		then \
			echo -n "@@@"; \
			echo "> passed"; \
		else \
			echo -n "@@@"; \
			echo "> failed"; \
		fi

	LD_PRELOAD=$PWD/protect.so ./move source_tests/test1 dest_tests/test1 || if [ ! -f source_tests/test1 ]; \
		then \
			echo -n "@@@"; \
			echo "> passed"; \
		else \
			echo -n "@@@"; \
			echo "> failed"; \
		fi
	-make clean


clean:
	rm source_tests/*
	rm dest_tests/*