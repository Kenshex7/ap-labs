SHELL    = /bin/bash
CC       = gcc
CFLAGS   = -Wall
LDFLAGS  =
OBJFILES = Firstchallenge.py
TARGET   = main

all: $(TARGET)

$(TARGET) : $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~

include ../../labs/common.mk
