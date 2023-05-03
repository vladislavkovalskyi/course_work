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

// Функция для добавления поезда
void add_train(struct train** head, struct train new_train) {
  struct train* new_node = (struct train*)malloc(sizeof(struct train));

  *new_node = new_train;
  new_node->next = *head;
  *head = new_node;
}

// Функция для написания поезда
void print_train(struct train one_train, int number) {
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

// Функция добавления нового поезда
void add_new_train(struct train** head) {
  struct train new_train;

  // Для того, чтобы в буфере не оставались знаки переноса строки
  while (getchar() != '\n')
    ;

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

  // Если удаляем первый элемент
  if (number == 1) {
    *head = current->next;
    free(current);
    return;
  }

  // Поиск элемента по номеру
  while (i < number && current != NULL) {
    previous = current;
    current = current->next;
    i++;
  }

  if (current == NULL) {
    printf("• Розкладу з номером #%d не знайдено.\n", number);
    return;
  }

  previous->next = current->next;
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

// Функция написания всех поездов
void print_all_trains(struct train* head) {
  struct train* current = head;
  int number = 0;
  while (current != NULL) {
    number++;
    print_train(*current, number);
    current = current->next;
  }
}

// Функция написания поездов по указанному направлению
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
    printf("Напрямку \"%s\" не знайдено.\n", destination);
  }
}

// Функция, которая печатает поезда по номеру поезда и месту
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

// Показывает инфо о поезде по его номеру
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

// Удаляет поезда по направлению
void delete_trains_by_destination(struct train** head) {
  char destination[50];
  printf("• Вкажіть напрямок: ");
  scanf("%49s", destination);

  struct train* current = *head;
  struct train* prev = NULL;

  while (current != NULL) {
    // Если направление совпадает
    if (strcmp(current->destination, destination) == 0) {
      // Если удаляемый элемент первый в списке
      if (prev == NULL) {
        *head = current->next;
      } else {
        prev->next = current->next;
      }
      struct train* temp = current;
      current = current->next;
      free(temp);
    } else {
      prev = current;
      current = current->next;
    }
  }
  printf("• Всі рейси за напрямком \"%s\" видалені.\n", destination);
}

// Функция для свайпа стеков
void swap_nodes(struct train* node1, struct train* node2) {
  char temp_destination[50];
  int temp_train_number;
  char temp_departure_time[10];
  char temp_arrival_time[10];
  double temp_ticket_price;

  // Сохраняем значения полей первой ноды
  strcpy(temp_destination, node1->destination);
  temp_train_number = node1->train_number;
  strcpy(temp_departure_time, node1->departure_time);
  strcpy(temp_arrival_time, node1->arrival_time);
  temp_ticket_price = node1->ticket_price;

  // Копируем значения полей в первую ноду
  strcpy(node1->destination, node2->destination);
  node1->train_number = node2->train_number;
  strcpy(node1->departure_time, node2->departure_time);
  strcpy(node1->arrival_time, node2->arrival_time);
  node1->ticket_price = node2->ticket_price;

  // Копируем сохраненные значения полей первой ноды во вторую
  strcpy(node2->destination, temp_destination);
  node2->train_number = temp_train_number;
  strcpy(node2->departure_time, temp_departure_time);
  strcpy(node2->arrival_time, temp_arrival_time);
  node2->ticket_price = temp_ticket_price;
}

// Функция, которая сортирует поезда по времени
void sort_trains_by_time(struct train* head) {
  struct train* current;
  struct train* next_node;
  int swapped;

  // Если head пустой или только один элемент
  if (head == NULL || head->next == NULL) {
    return;
  }

  do {
    swapped = 0;
    current = head;

    while (current->next != NULL) {
      next_node = current->next;

      // Если время следующего узла меньше времени текущего узла, меняем их
      // местами
      if (strcmp(current->departure_time, next_node->departure_time) > 0) {
        swap_nodes(current, next_node);
        swapped = 1;
      }

      current = next_node;
    }
  } while (swapped);
  
  printf("• Рейси були відсортовані.\n");
}

int main() {
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);

  // Загрузка данных из файла в стек при запуске
  struct train* trains = load_from_file(TRAINS_PATH);
  int choice = 0;

  while (1) {
    // Очистка буфера stdin (если вдруг остались данные после scanf)
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
        "9. Відсортувати рейси за часом\n"
        "10. Вихід\n"
        "• Введіть номер дії: ");
    scanf("%d", &choice);
    switch (choice) {
      case 1:
        clear_terminal();
        add_new_train(&trains);
        break;
      case 2:
        clear_terminal();
        delete_train(&trains);
        break;
      case 3:
        clear_terminal();
        edit_element_by_number(trains);
        break;
      case 4:
        clear_terminal();
        print_all_trains(trains);
        break;
      case 5:
        clear_terminal();
        show_train_by_destination(trains);
        break;
      case 6:
        clear_terminal();
        show_train_by_number_and_destination(trains);
        break;
      case 7:
        clear_terminal();
        show_train_info(trains);
        break;
      case 8:
        clear_terminal();
        delete_trains_by_destination(&trains);
        break;
      case 9:
        clear_terminal();
        sort_trains_by_time(trains);
        print_all_trains(trains);
        break;
      case 10:
        printf("• До побачення!\n");
        exit(0);
        break;
      default:
        printf("• Ви ввели невідому дію.\n");
        break;
    }
    // Сохранение данных в файлах после каждой команды
    save_to_file(trains, TRAINS_PATH);
  }

  return 0;
}