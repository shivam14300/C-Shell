TARGETS = BansalJi

all: $(TARGETS)

%o: %.c
	gcc -lreadline -g -c -o $@ $<
BansalJi: main.o background.o builtin.o input.o bonus.o ls.o pipeRedirect.o userdefined.o 
	gcc  -o BansalJi main.o background.o builtin.o input.o bonus.o ls.o pipeRedirect.o userdefined.o -lreadline

.PHONY: clean
clean:
	rm -rf $(TARGETS) *.o