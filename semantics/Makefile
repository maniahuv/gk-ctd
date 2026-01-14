# Trình biên dịch
CC = gcc
# Các cờ biên dịch (gồm debug và cảnh báo)
CFLAGS = -g -Wall

# Danh sách các tệp đối tượng (Object files) dựa trên bảng cấu trúc 
OBJS = main.o reader.o charcode.o token.o scanner.o \
       parser.o error.o debug.o symtab.o semantics.o

# Tên chương trình đích
TARGET = kpl

# Quy tắc mặc định: biên dịch chương trình 
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Quy tắc biên dịch các tệp .c thành .o tương ứng 
main.o: main.c reader.h scanner.h parser.h semantics.h error.h debug.h
	$(CC) $(CFLAGS) -c main.c

reader.o: reader.c reader.h
	$(CC) $(CFLAGS) -c reader.c

charcode.o: charcode.c charcode.h
	$(CC) $(CFLAGS) -c charcode.c

token.o: token.c token.h
	$(CC) $(CFLAGS) -c token.c

scanner.o: scanner.c scanner.h reader.h charcode.h token.h
	$(CC) $(CFLAGS) -c scanner.c

parser.o: parser.c parser.h scanner.h semantics.h error.h debug.h
	$(CC) $(CFLAGS) -c parser.c

error.o: error.c error.h
	$(CC) $(CFLAGS) -c error.c

debug.o: debug.c debug.h
	$(CC) $(CFLAGS) -c debug.c

symtab.o: symtab.c symtab.h
	$(CC) $(CFLAGS) -c symtab.c

semantics.o: semantics.c semantics.h symtab.h error.h
	$(CC) $(CFLAGS) -c semantics.c

# Quy tắc dọn dẹp các tệp tạm thời
clean:
	rm -f *.o $(TARGET)