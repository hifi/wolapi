CC=i586-mingw32msvc-gcc
CFLAGS=-pedantic -std=c99 -Wall -Werror -g -O2 -I./inc/ -D_DEBUG
LDFLAGS=-Wl,--enable-stdcall-fixup
LIBS=-luuid
OBJS=src/wolapi.o src/Chat.o src/IChat.o src/NetUtil.o src/INetUtil.o src/IConnectionPointContainer.o src/IWOLConnectionPoint.o

all: wolapi.dll

src/%.o: src/%.c inc/%.h inc/wolapi.h
	$(CC) $(CFLAGS) -c -o $@ $<

wolapi.dll: $(OBJS)
	$(CC) $(LDFLAGS) -shared -o wolapi.dll $(OBJS) res/wolapi.def $(LIBS)

clean:
	rm -rf wolapi.dll src/*.o