<image src"banner.jpg" alt="Banner">

# Курсова робота
### 💻 • Дисципліна: **Алгоритмізація та програмування**
### 👨‍💻 • Виконавець: **Ковальський Владислав Євгенович**

<br>

## 📃 Про роботу
### • **Курсова робота** була написана мовою програмування **С**.
### • **Тема роботи**: «Програмування динамічною структури даних – стек. Програма для роботи з рейсами.»

<br>

## 📁 Файли
### **Основні**
### • [app.c](app.c) – файл з кодом програми
### • [app.exe](app.exe) – файл з скомпільованою програмою
### • [trains.txt](trains.txt) - файл з інформацією про рейси

<br>

### **Файли репозиторію**
### • [course_work.mp4](course_work.mp4) - файл з відео-обзором програми
### • [.gitignore](.gitignore) - файл, в якому описані файли для ігнорування системою контролю версій

<br>

## 👩‍💻 Код
### Структура даних train
```c
struct train {
  char destination[50];     // Місце призначення
  int train_number;         // Номер поїзда
  char departure_time[10];  // Час відправки
  char arrival_time[10];    // Час прибуття
  double ticket_price;      // Ціна білету
  struct train* next;       // Показчик на наступний елемент
};
```

<br>

### Код програми
```c
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define TRAINS_PATH "trains.txt"

// Структура данных train
struct train {
  char destination[50];     // Место назначения
  int train_number;         // Номер поезда
  char departure_time[10];  // Время отправления
  char arrival_time[10];    // Время прибытия
  double ticket_price;      // Цена билета
  struct train* next;
};

// Функция для очистки терминала
void clear_terminal() {
...
```

Повний код програми можна переглянути [тут](app.c)

<br>
<br>
<br>
<br>

## Link to Github profile: [here](https://github.com/vladislavkovalskyi)
### 2023