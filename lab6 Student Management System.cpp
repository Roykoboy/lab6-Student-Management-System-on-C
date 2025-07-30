#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale>

#define MAX_STUDENTS 100

typedef struct {
    char name[50];
    char surname[50];
    int group;
    int grades[5];
} STUDENT;

void printStudent(STUDENT student) {
    printf("Имя: %s\n", student.name);
    printf("Фамилия: %s\n", student.surname);
    printf("Номер группы: %d\n", student.group);
    printf("Оценки: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", student.grades[i]);
    }
    printf("\n\n");
}

void printStudentsWithHighGrades(STUDENT university[], int size) {
    int found = 0;
    for (int i = 0; i < size; i++) {
        int highGrades = 0;
        for (int j = 0; j < 5; j++) {
            if (university[i].grades[j] >= 4) {
                highGrades = 1;
                break;
            }
        }
        if (highGrades) {
            printf("Фамилия: %s\n", university[i].surname);
            printf("Номер группы: %d\n\n", university[i].group);
            found = 1;
        }
    }
    if (!found) {
        printf("Нет студентов с оценками 4 и 5.\n\n");
    }
}

void addStudent(STUDENT university[], int* size) {
    if (*size >= MAX_STUDENTS) {
        printf("Достигнуто максимальное количество студентов.\n");
        return;
    }
    printf("Введите данные нового студента:\n");
    printf("Имя: ");
    scanf("%49s", university[*size].name);  // Ограничение 49 символов
    while (getchar() != '\n');  // Очистка буфера

    printf("Фамилия: ");
    scanf("%49s", university[*size].surname);
    while (getchar() != '\n');

    printf("Номер группы: ");
    while (scanf("%d", &university[*size].group) != 1) {
        printf("Ошибка: введите число!\n");
        while (getchar() != '\n');  // Очистка ошибочного ввода
    }
    while (getchar() != '\n');  // Очистка буфера

    printf("Оценки (5 чисел через пробел): ");
    for (int i = 0; i < 5; i++) {
        while (scanf("%d", &university[*size].grades[i]) != 1 ||
            university[*size].grades[i] < 2 ||
            university[*size].grades[i] > 5) {
            printf("Ошибка: введите оценку от 2 до 5!\n");
            while (getchar() != '\n');
        }
    }
    while (getchar() != '\n');

    (*size)++;
    printf("Студент успешно добавлен.\n\n");
}

void printStudentsByGroup(STUDENT university[], int size, int group) {
    int found = 0;
    for (int i = 0; i < size; i++) {
        if (university[i].group == group) {
            printStudent(university[i]);
            found = 1;
        }
    }
    if (!found) {
        printf("Студентов в группе %d нет.\n\n", group);
    }
}

void searchStudent(STUDENT university[], int size, char surname[50] ) {

    // Отладочный вывод
    printf("Отладка: ищем '%s' (длина %zu)\n", surname, strlen(surname));

    int found = 0;
    for (int i = 0; i < size; i++) {
        if (strcmp(university[i].surname, surname) == 0) {
            printStudent(university[i]);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Студент с фамилией %s не найден.\n\n", surname);
    }
}

int main() {
    setlocale(0, "Rus");
    STUDENT university[MAX_STUDENTS];
    int size = 0;
    int choice;

    do {
        printf("1. Вывести фамилии и номера групп студентов с оценками 4 и 5\n");
        printf("2. Добавить студента\n");
        printf("3. Вывести студентов по номеру группы\n");
        printf("4. Найти студента по фамилии\n");
        printf("0. Выход\n");
        printf("Введите выбранный пункт: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            printf("Студенты с оценками 4 и 5:\n");
            printStudentsWithHighGrades(university, size);
            break;
        case 2:
            addStudent(university, &size);
            break;
        case 3:
            printf("Введите номер группы: ");
            int group;
            scanf_s("%d", &group);
            printf("Студенты в группе %d:\n", group);
            printStudentsByGroup(university, size, group);
            break;
        case 4:
            printf("Введите фамилию студента: ");
            char surname[50];
            scanf_s("%49s", surname, (unsigned)_countof(surname));
            printf("Результат поиска:\n");
            searchStudent(university, size, surname);
            break;
        case 0:
            printf("Выход\n");
            break;
        default:
            printf("Неверный выбор\n");
            break;
        }

    } while (choice != 0);

    return 0;
}
