#!/bin/bash

CURRENT_DIR=$(dirname "$0")
cat "${CURRENT_DIR}/scancodes.log" | sort | uniq -c | sort -nr

