CC      := gcc
LD      := ld
CFLAGS  := -fPIC -fno-stack-protector
LIB		:= -luuid
LDFLAGS := -shared 
SOURCE  := $(wildcard src/*.c)
OBJS    := $(patsubst src/%.c,src/%.o,$(SOURCE))
# SOURCE=src/uuid.c
# OBJS= src/uuid.o


TARGET_LIB := libuuidx.so

# lib: src/libuuidx.so

# src/libuuidx.so: $(OBJS)
# 	MACOSX_DEPLOYMENT_TARGET="10.3"; export MACOSX_DEPLOYMENT_TARGET; $(CC) $(LDFLAGS) -o src/libuuidx.so $(OBJS)

all:$(OBJS)
	# @echo $(OBJS)
	$(LD) $(LDFLAGS) $(LIB) -o src/$(TARGET_LIB) $(OBJS) 
	# @rm src/*.o -rf

src/%.o:src/%.c
	$(CC) -c $(CFLAGS)  $< -o src/$*.o
	# @echo Compiling $< ...
	# @$(CC) -c $(CFLAGS)  $< -o src/$*.o

install:src/libuuidx.so
	cp src/libuuidx.so /usr/local/openresty/ldlib/libuuidx.so

.PHONY: clean

clean:
	rm -rf *.so src/*.o 
