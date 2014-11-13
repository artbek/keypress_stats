SOURCE = main.c
OUTPUT = keypress_stats.out
CHARACTER_DEVICE_FILE = "/dev/input/event3"
INSTALL_DIR = "./bin"
LOG_FILE = "./scancodes.log"

main: $(SOURCE)
	gcc -DCHARACTER_DEVICE_FILE='$(CHARACTER_DEVICE_FILE)' -DLOG_FILE='$(LOG_FILE)' $(SOURCE) -o $(OUTPUT)

install:
	mkdir $(INSTALL_DIR)
	cp $(OUTPUT) $(INSTALL_DIR)/$(OUTPUT)
	cp print_stats.sh $(INSTALL_DIR)/print_stats.sh
	sed -i -e 's#LOG_FILE_NAME=".*"#LOG_FILE_NAME=$(LOG_FILE)#' $(INSTALL_DIR)/print_stats.sh

