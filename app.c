#include <stdio.h>
#include <windows.h>

// ��������� ������ train
struct train {
  char destination[50];     // ����� ����������
  int train_number;         // ����� ������
  char departure_time[10];  // ����� �����������
  char arrival_time[10];    // ����� ��������
  double ticket_price;      // ���� ������
  struct train* next;
};

// ������� ��� ������� ���������
void clear_terminal() {
#ifdef _WIN32
  system("cls");
#elif __linux__
  system("clear");
#else
  printf(ERROR_TEXT
         "�� ����������� ��� �� ������� ��. �������� �������� ���������\n");
#endif
}

// DEV: ������� ��� ���������� ������
void add_train(struct train** head, struct train new_train) {
  struct train* new_node = (struct train*)malloc(sizeof(struct train));

  *new_node = new_train;
  new_node->next = *head;
  *head = new_node;
}

void print_train(struct train one_train) {
  fflush(stdin);
  printf(
      "� ���������� ��� �������\n"
      "̳��� �����������: %s\n"
      "����� �����: %d\n"
      "��� �����������: %s\n"
      "��� ��������: %s\n"
      "ֳ�� �����: %.2f\n",
      one_train.destination, one_train.train_number, one_train.departure_time,
      one_train.arrival_time, one_train.ticket_price);
}
////////////////////////////////////////////////////

void add_new_train(struct train** head) {
  struct train new_train;
  while (getchar() != '\n'); // ��������� � ������� ��� ������� �� �������� ������
  printf("������ ���������� ��� ����� ����:\n");
  printf("� ̳��� �����������: ");
  scanf("%s", new_train.destination);
  printf("� ����� �����: ");
  scanf("%d", &new_train.train_number);
  printf("� ��� �����������: ");
  scanf("%s", new_train.departure_time);
  printf("� ��� ��������: ");
  scanf("%s", new_train.arrival_time);
  printf("� ֳ�� �����: ");
  scanf("%lf", &new_train.ticket_price);
  
  add_train(head, new_train);
  clear_terminal();
  printf("� ����� ���� ��� ������ �������.\n");
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
        "� ���� ����������� �������:\n"
        "1. ������ ����� ����\n"
        "3. ������� �� �����\n"
        "� ������ ����� 䳿: ");
    scanf("%d", &choice);
    switch (choice) {
      case 1:
        add_new_train(&trains);
        break;
      case 3:
        print_all_trains(trains);
        break;
      default:
        printf("� �� ����� ������� ��.\n");
        break;
    }
  }

  return 0;
}