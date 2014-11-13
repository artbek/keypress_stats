#!/bin/bash

CURRENT_DIR=$(dirname "$0")
LOG_FILE="${CURRENT_DIR}/scancodes.log"

if [ "$#" > 1 ] && [ "$1" = "time" ]; then

	cat "${LOG_FILE}" |
	sort |
	cut -d" " -f 1-1 |
	uniq |
	while read KEY_NAME
	do
		COUNT=$(cat "${LOG_FILE}" | grep "$KEY_NAME" | cut -d" " -f 2-2 | paste -sd+ | bc)
		# usec -> sec
		COUNT=$(echo "$COUNT/1000000" | bc)
		echo "$COUNT: $KEY_NAME"
	done |
	sort -nr

fi


if [ "$#" > 1 ] && [ "$1" = "press" ]; then

	cat "${LOG_FILE}" | cut -d" " -f 1-1 | sort | uniq -c | sort -nr

fi

