CC := ${CC}
CFLAGS := ${CFLAGS}
LDFLAGS := ${LDFLAGS}
TARGET = FlashApp
FLASH_APP_SRC = FlashApp.c

all: $(TARGET)

$(TARGET): FlashApp.c
	${CC} ${CFLAGS} ${LDFLAGS} -o ${TARGET} ${FLASH_APP_SRC}

install:
	install -d ${D}/usr/bin
	install -m 0755 ${TARGET} ${D}/usr/bin/${TARGET}

clean:
	rm -f ${TARGET}
