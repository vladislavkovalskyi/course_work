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
#ifdef _WIN32
  system("cls");
#elif __linux__
  system("clear");
#else
  printf(ERROR_TEXT
         "Ви скомпілювали код на невідомій ОС. Очищення терміналу неможливе\n");
#endif
}

// DEV: Функция для добавления поезда
void add_train(struct train** head, struct train new_train) {
  struct train* new_node = (struct train*)malloc(sizeof(struct train));

  *new_node = new_train;
  new_node->next = *head;
  *head = new_node;
}

void print_train(struct train one_train, int number) {
  fflush(stdin);
  printf(
      "• (#%d) Інформація про розклад\n"
      "Місце признач.:\t%s\n"
      "Номер потягу:\t%d\n"
      "Час відправки:\t%s\n"
      "Час прибуття:\t%s\n"
      "Ціна білету:\t%.2f\n\n",
      number, one_train.destination, one_train.train_number,
      one_train.departure_time, one_train.arrival_time, one_train.ticket_price);
}

// Функция для записи данных из стека в файл
void save_to_file(struct train* head, const char* filename) {
  FILE* fp = fopen(filename, "w");
  if (fp == NULL) {
    printf("Не удалось открыть файл для записи\n");
    return;
  }
  while (head != NULL) {
    fprintf(fp, "%s %d %s %s %.2f\n", head->destination, head->train_number,
            head->departure_time, head->arrival_time, head->ticket_price);
    head = head->next;
  }
  fclose(fp);
}
////////////////////////////////////////////////////

// Функция для считывания данных из файла и записи их в стек
struct train* load_from_file(const char* filename) {
  FILE* fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Не удалось открыть файл для чтения\n");
    return NULL;
  }
  struct train* head = NULL;
  struct train* tail = NULL;
  char dest[50];
  int number;
  char dep_time[10];
  char arr_time[10];
  double price;

  while (fscanf(fp, "%s %d %s %s %lf", dest, &number, dep_time, arr_time,
                &price) == 5) {
    struct train* new_train = (struct train*)malloc(sizeof(struct train));
    strcpy(new_train->destination, dest);
    new_train->train_number = number;
    strcpy(new_train->departure_time, dep_time);
    strcpy(new_train->arrival_time, arr_time);
    new_train->ticket_price = price;
    new_train->next = NULL;
    if (head == NULL) {
      head = new_train;
      tail = new_train;
    } else {
      tail->next = new_train;
      tail = new_train;
    }
  }
  fclose(fp);
  printf("Данные загружены из файла %s\n", filename);
  return head;
}

void add_new_train(struct train** head) {
  struct train new_train;
  while (getchar() != '\n')
    ;  // Считываем и удаляем все символы из входного буфера
  printf("Введіть інформацію про новий поїзд:\n");
  printf("• Місце призначення: ");
  scanf("%s", new_train.destination);
  printf("• Номер поїзду: ");
  scanf("%d", &new_train.train_number);
  printf("• Час відправлення: ");
  scanf("%s", new_train.departure_time);
  printf("• Час прибуття: ");
  scanf("%s", new_train.arrival_time);
  printf("• Ціна білету: ");
  scanf("%lf", &new_train.ticket_price);

  add_train(head, new_train);
  clear_terminal();
  // save_to_file(*head, TRAINS_PATH);
  printf("• Новий рейс був успішно доданий та збережений в файл %s\n",
         TRAINS_PATH);
}

// Удаление рейса
void delete_train(struct train** head) {
  struct train* current = *head;
  struct train* previous = NULL;
  int i = 1;
  int number = 0;
  printf("• Вкажіть номер розкладу: ");
  scanf("%d", &number);

  if (number == 1) {  // Если удаляем первый элемент
    *head = current->next;
    free(current);
    return;
  }

  while (i < number && current != NULL) {  // Поиск элемента по номеру
    previous = current;
    current = current->next;
    i++;
  }

  if (current == NULL) {  // Если элемент не найден
    printf("Element with number %d not found.\n", number);
    return;
  }

  previous->next = current->next;  // Удаление элемента
  // save_to_file(*head, TRAINS_PATH);
  free(current);
}

// Редактирование рейса
void edit_element_by_number(struct train* head) {
  struct train* current = head;
  int i = 1;

  int number = 0;
  printf("• Вкажіть номер розкладу: ");
  scanf("%d", &number);

  while (i < number && current != NULL) {  // Поиск элемента по номеру
    current = current->next;
    i++;
  }

  if (current == NULL) {  // Если элемент не найден
    printf("• Розкладу з номером #%d не знайдено.\n", number);
    return;
  }

  // Редактирование элемента
  printf("• Місце призначення: ");
  scanf("%s", current->destination);
  printf("• Номер поїзду: ");
  scanf("%d", &current->train_number);
  printf("• Час відправлення: ");
  scanf("%s", current->departure_time);
  printf("• Час прибуття: ");
  scanf("%s", current->arrival_time);
  printf("• Ціна білету: ");
  scanf("%lf", &current->ticket_price);
}

void print_all_trains(struct train* head) {
  struct train* current = head;
  int number = 0;
  while (current != NULL) {
    number++;
    print_train(*current, number);
    current = current->next;
  }
}

void show_train_by_destination(struct train* head) {
  struct train* current = head;
  char destination[50];
  int found = 0;
  printf("• Вкажіть напрямок: ");
  scanf("%49s", destination);

  while (current != NULL) {
    if (strcmp(current->destination, destination) == 0) {
      printf("Місце признач.:\t%s\n", current->destination);
      printf("Номер потягу:\t%d\n", current->train_number);
      printf("Час відправки:\t%s\n", current->departure_time);
      printf("Час прибуття:\t%s\n", current->arrival_time);
      printf("Ціна білету:\t%.2lf\n\n", current->ticket_price);
      found = 1;
    }
    current = current->next;
  }
  if (!found) {
    printf("Напрямку \"%s\" не знайдено.\n",
           destination);  // Если направление не найдено
  }
}

void show_train_by_number_and_destination(struct train* head) {
  struct train* current = head;
  int train_number;
  char destination[50];
  printf("• Введіть номер потягу: ");
  scanf("%d", &train_number);
  printf("• Введіть станцію призначення: ");
  scanf("%49s", destination);
  int train_found = 0;

  while (current != NULL) {
    if (current->train_number == train_number &&
        strcmp(current->destination, destination) == 0) {
      printf("• Час прибуття:\t%s\n", current->arrival_time);
      train_found = 1;
    }
    current = current->next;
  }

  if (!train_found) {
    printf("Потяг з номером %d та напрямком \"%s\" не знайдено.\n",
           train_number, destination);
  }
}

void show_train_info(struct train* head) {
  int train_number;
  printf("• Вкажіть номер потягу: ");
  scanf("%d", &train_number);
  int found = 0;
  struct train* current = head;
  while (current != NULL) {
    if (current->train_number == train_number) {
      printf("• Час відправ.:\t%s\n", current->departure_time);
      printf("• Ціна білету:\t%.2lf грн\n\n", current->ticket_price);
      found = 1;
    }
    current = current->next;
  }
  if (!found) {
    printf("Потяг з номером %d не знайдено.\n", train_number);
  }
}

void delete_trains_by_destination(struct train** head) {
  char destination[50];
  printf("• Вкажіть напрямок: ");
  scanf("%49s", destination);

  struct train* current = *head;
  struct train* prev = NULL;

  // Перебираем все элементы списка
  while (current != NULL) {
    // Если направление совпадает, удаляем поезд
    if (strcmp(current->destination, destination) == 0) {
      // Если удаляемый элемент первый в списке
      if (prev == NULL) {
        *head = current->next;
      } else {
        prev->next = current->next;
      }
      struct train* temp = current;
      current = current->next;
      free(temp);  // Освобождаем память удаленного элемента
    } else {
      prev = current;
      current = current->next;
    }
  }
  printf("• Всі рейси за напрямком \"%s\" видалені.\n", destination);
}

// Предметна область – залізничний вокзал.
// Реалізувати динамічну структуру даних (стек), що містить інформацію про
// розклад руху поїздів по певній станції: станція призначення; номер поїзда;
// час відправлення; час прибуття на станцію призначення; вартість проїзду.
// Програма повинна забезпечувати:
// – додавання елемента; +
// – видалення елемента; +
// – можливість коригування даних; +
// – виведення всіх даних; +
// – видачу довідки про всі поїзди зазначеного напрямку;. +
// – видачу довідки про час прибуття кожного з поїздів зазначеного напрямку на
// станцію призначення; +
// – видачу довідки про час відправлення поїзда з заданим
// номером; +
// – видалення з бази записів про потяги зазначеного напрямку; +
// – сортування за часом відправлення
int main() {
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  struct train* trains = load_from_file(TRAINS_PATH);
  int choice = 0;

  while (1) {
    fflush(stdin);

    printf(
        "• Меню залізничного вокзалу:\n"
        "1. Додати новий рейс\n"
        "2. Видалити рейс\n"
        "3. Редагувати рейс\n"
        "4. Вивести всі рейси\n"
        "5. Вивести рейси за напрямком\n"
        "6. Вивести час прибуття за потягом та місцем призначення\n"
        "7. Вивести інфо. за номером потягу\n"
        "8. Видалити рейси за напрямком\n"
        "9. Вихід\n"
        "• Введіть номер дії: ");
    scanf("%d", &choice);
    switch (choice) {
      case 1:
        add_new_train(&trains);
        break;
      case 2:
        delete_train(&trains);
        break;
      case 3:
        edit_element_by_number(trains);
        break;
      case 4:
        print_all_trains(trains);
        break;
      case 5:
        show_train_by_destination(trains);
        break;
      case 6:
        show_train_by_number_and_destination(trains);
        break;
      case 7:
        show_train_info(trains);
        break;
      case 8:
        delete_trains_by_destination(&trains);
        break;
      case 9:
        printf("• До побачення!\n");
        exit(0);
        break;
      default:
        printf("• Ви ввели невідому дію.\n");
        break;
    }
    save_to_file(trains, TRAINS_PATH);
  }

  return 0;
}