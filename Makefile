# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
TARGET = squeeze_detector
SOURCES = main.cpp

# Сборка по умолчанию
all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# Запуск программы
run: $(TARGET)
	./$(TARGET)

# Очистка
clean:
	rm -f $(TARGET)

# Отладочная сборка
debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

# Установка (если нужно)
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

.PHONY: all run clean debug install