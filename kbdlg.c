#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
//#include <include/linux/input.h>

struct input_event {
	struct timeval time;
	unsigned short type;
	unsigned short code;
	unsigned int value;
};

char keycodes[255][15];

void init()
{
	strcpy(keycodes[1], "KEY_ESC");
	strcpy(keycodes[2], "KEY_1");
	strcpy(keycodes[3], "KEY_2");
	strcpy(keycodes[4], "KEY_3");
	strcpy(keycodes[5], "KEY_4");
	strcpy(keycodes[6], "KEY_5");
	strcpy(keycodes[7], "KEY_6");
	strcpy(keycodes[8], "KEY_7");
	strcpy(keycodes[9], "KEY_8");
	strcpy(keycodes[10], "KEY_9");
	strcpy(keycodes[11], "KEY_0");
	strcpy(keycodes[12], "KEY_MINUS");
	strcpy(keycodes[13], "KEY_EQUAL");
	strcpy(keycodes[14], "KEY_BACKSPACE");
	strcpy(keycodes[15], "KEY_TAB");
	strcpy(keycodes[16], "KEY_Q");
	strcpy(keycodes[17], "KEY_W");
	strcpy(keycodes[18], "KEY_E");
	strcpy(keycodes[19], "KEY_R");
	strcpy(keycodes[20], "KEY_T");
	strcpy(keycodes[21], "KEY_Y");
	strcpy(keycodes[22], "KEY_U");
	strcpy(keycodes[23], "KEY_I");
	strcpy(keycodes[24], "KEY_O");
	strcpy(keycodes[25], "KEY_P");
	strcpy(keycodes[26], "KEY_LEFTBRACE");
	strcpy(keycodes[27], "KEY_RIGHTBRACE");
	strcpy(keycodes[28], "KEY_ENTER");
	strcpy(keycodes[29], "KEY_LEFTCTRL");
	strcpy(keycodes[30], "KEY_A");
	strcpy(keycodes[31], "KEY_S");
	strcpy(keycodes[32], "KEY_D");
	strcpy(keycodes[33], "KEY_F");
	strcpy(keycodes[34], "KEY_G");
	strcpy(keycodes[35], "KEY_H");
	strcpy(keycodes[36], "KEY_J");
	strcpy(keycodes[37], "KEY_K");
	strcpy(keycodes[38], "KEY_L");
	strcpy(keycodes[39], "KEY_SEMICOLON");
	strcpy(keycodes[40], "KEY_APOSTROPHE");
	strcpy(keycodes[41], "KEY_GRAVE");
	strcpy(keycodes[42], "KEY_LEFTSHIFT");
	strcpy(keycodes[43], "KEY_BACKSLASH");
	strcpy(keycodes[44], "KEY_Z");
	strcpy(keycodes[45], "KEY_X");
	strcpy(keycodes[46], "KEY_C");
	strcpy(keycodes[47], "KEY_V");
	strcpy(keycodes[48], "KEY_B");
	strcpy(keycodes[49], "KEY_N");
	strcpy(keycodes[50], "KEY_M");
	strcpy(keycodes[51], "KEY_COMMA");
	strcpy(keycodes[52], "KEY_DOT");
	strcpy(keycodes[53], "KEY_SLASH");
	strcpy(keycodes[54], "KEY_RIGHTSHIFT");
	strcpy(keycodes[55], "KEY_KPASTERISK");
	strcpy(keycodes[56], "KEY_LEFTALT");
	strcpy(keycodes[57], "KEY_SPACE");
	strcpy(keycodes[58], "KEY_CAPSLOCK");
	strcpy(keycodes[59], "KEY_F1");
	strcpy(keycodes[60], "KEY_F2");
	strcpy(keycodes[61], "KEY_F3");
	strcpy(keycodes[62], "KEY_F4");
	strcpy(keycodes[63], "KEY_F5");
	strcpy(keycodes[64], "KEY_F6");
	strcpy(keycodes[65], "KEY_F7");
	strcpy(keycodes[66], "KEY_F8");
	strcpy(keycodes[67], "KEY_F9");
	strcpy(keycodes[68], "KEY_F10");

	strcpy(keycodes[86], "KEY_BSLASH");
	strcpy(keycodes[87], "KEY_F11");
	strcpy(keycodes[88], "KEY_F12");

	strcpy(keycodes[97], "KEY_RIGHTCTRL");

	strcpy(keycodes[100], "KEY_RIGHTALT");
	strcpy(keycodes[101], "KEY_LINEFEED");
	strcpy(keycodes[102], "KEY_HOME");
	strcpy(keycodes[103], "KEY_UP");
	strcpy(keycodes[104], "KEY_PAGEUP");
	strcpy(keycodes[105], "KEY_LEFT");
	strcpy(keycodes[106], "KEY_RIGHT");
	strcpy(keycodes[107], "KEY_END");
	strcpy(keycodes[108], "KEY_DOWN");
	strcpy(keycodes[109], "KEY_PAGEDOWN");
	strcpy(keycodes[110], "KEY_INSERT");
	strcpy(keycodes[111], "KEY_DELETE");
	strcpy(keycodes[112], "KEY_MACRO");
	strcpy(keycodes[113], "KEY_MUTE");

	strcpy(keycodes[125], "KEY_WIN");
	strcpy(keycodes[127], "KEY_MENU");
}


int main()
{
	init();

	int scancodes_fd = open("./scancodes.log", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (scancodes_fd < 0) printf("open scancodes_fd: %s\n", strerror(errno));
	else printf("scancodes_fd = %d\n", scancodes_fd);

	int fd = open("/dev/input/event3", O_RDONLY);
	if (fd < 0) printf("open /dev/input/event3: %s\n", strerror(errno));
	else printf("fd = %d\n", fd);
	
	unsigned char characters_to_write;
	struct input_event buffer;

	int bytes_read = 0;
	while (1) {
	 	bytes_read = read(fd, &buffer, sizeof(struct input_event));

		// EV_KEY (include/uapi/linux/input.h)
		if (buffer.type == 0x01) {
			if (buffer.value == 0) { // release
				lseek(scancodes_fd, 0, SEEK_END); // append

				char str[16];
				sprintf(str, "%s\n", keycodes[buffer.code]);
				characters_to_write = (int)strlen(keycodes[buffer.code]) + 1;
				int bytes_written = write(scancodes_fd, str, characters_to_write);

				if (bytes_written < 0) printf("write scancodes_fd: %s\n", strerror(errno));
			}
		}

		if (bytes_read < 0) {
			printf("%s\n", strerror(errno));
			break;
		}
	}


	return 0;
}
