AM_CFLAGS = -std=c99

bin_PROGRAMS=esub
esub_SOURCES=main.c

testing:
	make all-am
	
	rm -rf outputs
	mkdir outputs
	./esub '(ab)' 'abcdefab' '123F(\1)' > outputs/o1
	echo 'abcdefab' | sed -E 's/(ab)/123F(\1)/' > outputs/o1_true
	cmp outputs/o1 outputs/o1_true

	./esub '(a.*)(b.*)(c.*)(d.*)' 'abcdefab' '\4\3\2\1' > outputs/o1
	echo 'abcdefab' | sed -E 's/(a.*)(b.*)(c.*)(d.*)/\4\3\2\1/' > outputs/o1_true
	cmp outputs/o1 outputs/o1_true

	./esub '(a.*)(b.*)(c.*)(d.*)' 'asdgojsdgsdsdgbsdfgdsgsdfsdcadsafasdfadsd' '\4\3\2\1' > outputs/o1
	echo 'asdgojsdgsdsdgbsdfgdsgsdfsdcadsafasdfadsd' | sed -E 's/(a.*)(b.*)(c.*)(d.*)/\4\3\2\1/' > outputs/o1_true
	cmp outputs/o1 outputs/o1_true

	rm -rf outputs
	- make clean
	echo "tests passed"

clean:
	rm esub
	rm config.h
	rm main.o
	rm Makefile.in