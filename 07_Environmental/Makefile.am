AM_CFLAGS = -std=c99

bin_PROGRAMS=rhasher
rhasher_SOURCES=rhasher.c

testing:
	cat test1 | sha1sum | awk '{print $$1;}'  > sha_f_test
	echo -e "SHA1 test1" | ./rhasher | sed -n 2p  > sha_f_out
	diff sha_f_out sha_f_test

	(cat test1 | md5sum | awk '{print $$1;}') > md5_f_test
	echo -e "MD5 test1" | ./rhasher | sed -n 2p  > md5_f_out
	diff md5_f_out md5_f_test