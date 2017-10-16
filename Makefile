.SUFFIXES: .o .m

CC=cc
TARGET=bmp.exe

CFLAGS=-g
LFLAGS=
LIBS=-lXm -lXt
OBJDIR=build

SRCS=main.c
O1=$(SRCS:%.c=%.o)
OBJS=$(O1:%=$(OBJDIR)/%)


all:$(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c  $< -o $@


$(OBJS): $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	- rm -f $(OBJS)
	- rm -f $(TARGET)
	- rm -f *.bak
	- rm -f *.BAK

