#include <stdio.h>
#include <windows.h>

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

void print_train(struct train one_train) {
  fflush(stdin);
  printf(
      "• Інформація про розклад\n"
      "Місце призначення: %s\n"
      "Номер поїзду: %d\n"
      "Час відправлення: %s\n"
      "Час прибуття: %s\n"
      "Ціна білету: %.2f\n",
      one_train.destination, one_train.train_number, one_train.departure_time,
      one_train.arrival_time, one_train.ticket_price);
}
////////////////////////////////////////////////////

void add_new_train(struct train** head) {
  struct train new_train;
  while (getchar() != '\n'); // Считываем и удаляем все символы из входного буфера
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
  printf("• Новий рейс був успішно доданий.\n");
}


void print_all_trains(struct train* head) {
  struct train* current = head;
  while (current != NULL) {
    print_train(*current);
    current = current->next;
  }
}

int main() {
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  struct train* trains = NULL;
  int choice = 0;
  while (1) {
    fflush(stdin);

    printf(
        "• Меню залізничного вокзалу:\n"
        "1. Додати новий рейс\n"
        "3. Вивести всі рейси\n"
        "• Введіть номер дії: ");
    scanf("%d", &choice);
    switch (choice) {
      case 1:
        add_new_train(&trains);
        break;
      case 3:
        print_all_trains(trains);
        break;
      default:
        printf("• Ви ввели невідому дію.\n");
        break;
    }
  }

  return 0;
}