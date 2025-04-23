# Компілятор C
CC = gcc

# Прапорці компілятора: -g для відладки, -Wall для всіх попереджень, -Wextra для додаткових попереджень, -pedantic для суворого дотримання стандарту, -std=c99 для стандарту C99
CFLAGS = -g -Wall -Wextra -pedantic -std=c99

# Прапорці лінкера
LDFLAGS =

# Заголовкові файли
HEADERS = BST.h item.h LLRB.h LLRB_ops.h node.h

# --- Визначення файлів для BST Test ---
BST_TEST_TARGET = bst_test
BST_TEST_SRCS = lecture_8.c BST.c node.c
BST_TEST_OBJS = $(BST_TEST_SRCS:.c=.o)

# --- Визначення файлів для LLRB Test ---
LLRB_TEST_TARGET = llrb_test
# Додаємо BST.c до вихідних файлів, оскільки LLRB тести використовують функції з BST.c
LLRB_TEST_SRCS = LLRB_tests.c LLRB.c LLRB_ops.c node.c BST.c
LLRB_TEST_OBJS = $(LLRB_TEST_SRCS:.c=.o)

# Ціль за замовчуванням: зібрати обидва тести
all: $(BST_TEST_TARGET) $(LLRB_TEST_TARGET)

# Правило для лінкування BST тесту
# $^ представляє всі залежності (всі .o файли з BST_TEST_OBJS)
$(BST_TEST_TARGET): $(BST_TEST_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "Скомпільовано виконуваний файл: $@"

# Правило для лінкування LLRB тесту
# $^ представляє всі залежності (всі .o файли з LLRB_TEST_OBJS, включаючи BST.o)
$(LLRB_TEST_TARGET): $(LLRB_TEST_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "Скомпільовано виконуваний файл: $@"

# Загальне правило для компіляції .c файлів в .o файли
# $< - ім'я першої залежності (.c файл)
# $@ - ім'я цілі (.o файл)
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Очищення: видалення об'єктних файлів та виконуваних файлів
clean:
	rm -f $(BST_TEST_TARGET) $(LLRB_TEST_TARGET) *.o *~ core.* lecture_8
	@echo "Очищено робочу директорію."

# Оголошення цілей, які не є файлами
.PHONY: all clean



