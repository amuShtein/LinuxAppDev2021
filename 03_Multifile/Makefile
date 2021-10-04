OPARAMS= 
LIBSOURCES=fun.o const.o
NAME=
CMDARG1=
CMDARG2=
prog:   const.c fun.c prog.c
	cc const.c fun.c prog.c -o prog
prog-a: prog.o liboutput_static.a
	cc -L. prog.o -loutput_static -o $@

prog-so: prog.o liboutput.so
	cc -L. prog.o -loutput -o $@

%.o: %.c
	cc -c -o $@ $< $(OPARAMS)

liboutput_static.a: fun.o const.o
	ar -rcs  $@ $(LIBSOURCES)

liboutput.so:
	rm $(LIBSOURCES)
	make OPARAMS=-fPIC $(LIBSOURCES)
	cc -shared fun.o const.o -o $@
write:
	LD_LIBRARY_PATH=`pwd` ./$(NAME) $(CMDARG1) $(CMDARG2) > $(NAME).output 
clean-libs:
	rm -f liboutput*
clean-o:
	rm -f *.o
clean:
	rm -f prog prog-a prog-so

SINGLEPARAM=single_param
PAIRPARAM1=pair_param_1
PAIRPARAM2=pair_param2
test-with-param: prog prog-a prog-so
	1> debug make $(PARAM) NAME=prog write
	1> debug make $(PARAM) NAME=prog-a write	
	1> debug make $(PARAM) NAME=prog-so write
	
	cmp prog.output prog-a.output | echo
	cmp prog.output prog-so.output | echo
	cmp prog-a.output prog-so.output | echo
	1> debug rm prog*.output
test:
	make test-with-param
	make PARAM=CMDARG1=$(SINGLEPARAM) test-with-param
	make PARAM='CMDARG1=$(PAIRPARAM1) CMDARG2=$(PAIRPARAM2)' test-with-param
	make clean-o
	make clean-libs
