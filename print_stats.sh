#!/bin/bash

LOG_FILE_NAME="./scancodes.log"
LOG_FILE_PATH="${LOG_FILE_NAME}"

if [ "$#" > 1 ] && [ "$1" = "time" ]; then

	cat "${LOG_FILE_PATH}" |
	sort |
	cut -d" " -f 1-1 |
	uniq |
	while read KEY_NAME
	do
		COUNT=$(cat "${LOG_FILE_PATH}" | grep "$KEY_NAME" | cut -d" " -f 2-2 | paste -sd+ | bc)
		# usec -> sec
		COUNT=$(echo "$COUNT/1000000" | bc)
		echo "$COUNT: $KEY_NAME"
	done |
	sort -nr

fi


if [ "$#" > 1 ] && [ "$1" = "press" ]; then

	cat "${LOG_FILE_PATH}" | cut -d" " -f 1-1 | sort | uniq -c | sort -nr

fi

