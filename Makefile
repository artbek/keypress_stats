SOURCE = kbdlg.c
OUTPUT = kbdlg.out

main: $(SOURCE)
	gcc $(SOURCE) -o $(OUTPUT)

clean:
	rm scancodes.log kbdlg.out

install:
	chown root $(OUTPUT); chmod 4775 $(OUTPUT);

