AM_CFLAGS = -std=c99

bin_PROGRAMS=rhasher
rhasher_SOURCES=rhasher.c

testing:
	make all-am
	(cat test1 | sha1sum | awk '{print $$1;}')  > sha_f_test
	(echo -e "SHA1 test1" | ./rhasher | sed -n 3p)  > sha_f_out
	diff sha_f_out sha_f_test
	rm sha_f_out sha_f_test

	(cat test1 | md5sum | awk '{print $$1;}') > md5_f_test
	(echo -e "MD5 test1" | ./rhasher | sed -n 3p)  > md5_f_out
	diff md5_f_out md5_f_test
	rm md5_f_out md5_f_test

	(printf "TeStInG_sTrInG" | sha1sum | awk '{print $$1;}')  > sha_f_test
	(printf "SHA1 \"TeStInG_sTrInG" | ./rhasher | sed -n 3p)  > sha_f_out
	diff sha_f_out sha_f_test
	rm sha_f_out sha_f_test

	(printf "TeStInG_sTrInG" | md5sum | awk '{print $$1;}') > md5_f_test
	(printf "MD5 \"TeStInG_sTrInG" | ./rhasher | sed -n 3p)  > md5_f_out
	diff md5_f_out md5_f_test
	rm md5_f_out md5_f_test


	echo "tests passed"

clean:
	rm rhasher
	rm config.h
	rm rhasher.o
	rm Makefile.in
	rm Makefile