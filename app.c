#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define TRAINS_PATH "trains.txt"

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

void print_train(struct train one_train, int number) {
  fflush(stdin);
  printf(
      "� (#%d) ���������� ��� �������\n"
      "̳��� �������.:\t%s\n"
      "����� ������:\t%d\n"
      "��� ��������:\t%s\n"
      "��� ��������:\t%s\n"
      "ֳ�� �����:\t%.2f\n\n",
      number, one_train.destination, one_train.train_number,
      one_train.departure_time, one_train.arrival_time, one_train.ticket_price);
}

// ������� ��� ������ ������ �� ����� � ����
void save_to_file(struct train* head, const char* filename) {
  FILE* fp = fopen(filename, "w");
  if (fp == NULL) {
    printf("�� ������� ������� ���� ��� ������\n");
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

// ������� ��� ���������� ������ �� ����� � ������ �� � ����
struct train* load_from_file(const char* filename) {
  FILE* fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("�� ������� ������� ���� ��� ������\n");
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
  printf("������ ��������� �� ����� %s\n", filename);
  return head;
}

void add_new_train(struct train** head) {
  struct train new_train;
  while (getchar() != '\n')
    ;  // ��������� � ������� ��� ������� �� �������� ������
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
  // save_to_file(*head, TRAINS_PATH);
  printf("� ����� ���� ��� ������ ������� �� ���������� � ���� %s\n",
         TRAINS_PATH);
}

// �������� �����
void delete_train(struct train** head) {
  struct train* current = *head;
  struct train* previous = NULL;
  int i = 1;
  int number = 0;
  printf("� ������ ����� ��������: ");
  scanf("%d", &number);

  if (number == 1) {  // ���� ������� ������ �������
    *head = current->next;
    free(current);
    return;
  }

  while (i < number && current != NULL) {  // ����� �������� �� ������
    previous = current;
    current = current->next;
    i++;
  }

  if (current == NULL) {  // ���� ������� �� ������
    printf("Element with number %d not found.\n", number);
    return;
  }

  previous->next = current->next;  // �������� ��������
  // save_to_file(*head, TRAINS_PATH);
  free(current);
}

// �������������� �����
void edit_element_by_number(struct train* head) {
  struct train* current = head;
  int i = 1;

  int number = 0;
  printf("� ������ ����� ��������: ");
  scanf("%d", &number);

  while (i < number && current != NULL) {  // ����� �������� �� ������
    current = current->next;
    i++;
  }

  if (current == NULL) {  // ���� ������� �� ������
    printf("� �������� � ������� #%d �� ��������.\n", number);
    return;
  }

  // �������������� ��������
  printf("� ̳��� �����������: ");
  scanf("%s", current->destination);
  printf("� ����� �����: ");
  scanf("%d", &current->train_number);
  printf("� ��� �����������: ");
  scanf("%s", current->departure_time);
  printf("� ��� ��������: ");
  scanf("%s", current->arrival_time);
  printf("� ֳ�� �����: ");
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
  printf("� ������ ��������: ");
  scanf("%49s", destination);

  while (current != NULL) {
    if (strcmp(current->destination, destination) == 0) {
      printf("̳��� �������.:\t%s\n", current->destination);
      printf("����� ������:\t%d\n", current->train_number);
      printf("��� ��������:\t%s\n", current->departure_time);
      printf("��� ��������:\t%s\n", current->arrival_time);
      printf("ֳ�� �����:\t%.2lf\n\n", current->ticket_price);
      found = 1;
    }
    current = current->next;
  }
  if (!found) {
    printf("�������� \"%s\" �� ��������.\n",
           destination);  // ���� ����������� �� �������
  }
}

void show_train_by_number_and_destination(struct train* head) {
  struct train* current = head;
  int train_number;
  char destination[50];
  printf("� ������ ����� ������: ");
  scanf("%d", &train_number);
  printf("� ������ ������� �����������: ");
  scanf("%49s", destination);
  int train_found = 0;

  while (current != NULL) {
    if (current->train_number == train_number &&
        strcmp(current->destination, destination) == 0) {
      printf("� ��� ��������:\t%s\n", current->arrival_time);
      train_found = 1;
    }
    current = current->next;
  }

  if (!train_found) {
    printf("����� � ������� %d �� ��������� \"%s\" �� ��������.\n",
           train_number, destination);
  }
}

void show_train_info(struct train* head) {
  int train_number;
  printf("� ������ ����� ������: ");
  scanf("%d", &train_number);
  int found = 0;
  struct train* current = head;
  while (current != NULL) {
    if (current->train_number == train_number) {
      printf("� ��� ������.:\t%s\n", current->departure_time);
      printf("� ֳ�� �����:\t%.2lf ���\n\n", current->ticket_price);
      found = 1;
    }
    current = current->next;
  }
  if (!found) {
    printf("����� � ������� %d �� ��������.\n", train_number);
  }
}

void delete_trains_by_destination(struct train** head) {
  char destination[50];
  printf("� ������ ��������: ");
  scanf("%49s", destination);

  struct train* current = *head;
  struct train* prev = NULL;

  // ���������� ��� �������� ������
  while (current != NULL) {
    // ���� ����������� ���������, ������� �����
    if (strcmp(current->destination, destination) == 0) {
      // ���� ��������� ������� ������ � ������
      if (prev == NULL) {
        *head = current->next;
      } else {
        prev->next = current->next;
      }
      struct train* temp = current;
      current = current->next;
      free(temp);  // ����������� ������ ���������� ��������
    } else {
      prev = current;
      current = current->next;
    }
  }
  printf("� �� ����� �� ��������� \"%s\" �������.\n", destination);
}

// ��������� ������� � ���������� ������.
// ���������� �������� ��������� ����� (����), �� ������ ���������� ���
// ������� ���� ����� �� ����� �������: ������� �����������; ����� �����;
// ��� �����������; ��� �������� �� ������� �����������; ������� ������.
// �������� ������� �������������:
// � ��������� ��������; +
// � ��������� ��������; +
// � ��������� ����������� �����; +
// � ��������� ��� �����; +
// � ������ ������ ��� �� ����� ����������� ��������;. +
// � ������ ������ ��� ��� �������� ������� � ����� ����������� �������� ��
// ������� �����������; +
// � ������ ������ ��� ��� ����������� ����� � �������
// �������; +
// � ��������� � ���� ������ ��� ������ ����������� ��������; +
// � ���������� �� ����� �����������
int main() {
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  struct train* trains = load_from_file(TRAINS_PATH);
  int choice = 0;

  while (1) {
    fflush(stdin);

    printf(
        "� ���� ����������� �������:\n"
        "1. ������ ����� ����\n"
        "2. �������� ����\n"
        "3. ���������� ����\n"
        "4. ������� �� �����\n"
        "5. ������� ����� �� ���������\n"
        "6. ������� ��� �������� �� ������� �� ����� �����������\n"
        "7. ������� ����. �� ������� ������\n"
        "8. �������� ����� �� ���������\n"
        "9. �����\n"
        "� ������ ����� 䳿: ");
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
        printf("� �� ���������!\n");
        exit(0);
        break;
      default:
        printf("� �� ����� ������� ��.\n");
        break;
    }
    save_to_file(trains, TRAINS_PATH);
  }

  return 0;
}