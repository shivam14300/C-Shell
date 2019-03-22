TARGETS = BansalJi

all: $(TARGETS)

%o: %.c
	gcc -lreadline -g -c -o $@ $<
BansalJi: shell.o takeInput.o splitCmds.o background.o handler.o remindme.o clock.o pinfo.o getPath.o cmds.o ls.o pwd.o echo.o cd.o
	gcc  -o BansalJi  shell.o takeInput.o splitCmds.o background.o handler.o remindme.o clock.o pinfo.o getPath.o cmds.o ls.o pwd.o echo.o cd.o -lreadline

.PHONY: clean
clean:
	rm -rf $(TARGETS) *.o