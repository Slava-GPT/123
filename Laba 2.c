#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>


//Здесь был Ярик
#define MAX_SIZE 100
//Github
// Структура для узла односвязного списка
typedef struct Node {
    char data;
    struct Node* next;
} Node;

// Структура для стека на основе массива
typedef struct {
    char items[MAX_SIZE]; 
    int top; 
} ArrayStack;

// Структура для стека на основе списка
typedef struct {
    Node* top; 
} ListStack;

// Функция для инициализации стека на основе массива
void initArrayStack(ArrayStack* s) {
    s->top = 0;
}

// Функция для инициализации стека на основе списка
void initListStack(ListStack* s) {
    s->top = NULL;
}

// Функция для добавления элемента в стек на основе массива
bool pushArray(ArrayStack* s, char data) {
    if (s->top >= MAX_SIZE)
        return false;
    s->items[s->top++] = data;
    return true;
}

// Функция для добавления элемента в стек на основе списка
bool pushList(ListStack* s, char data) {
    //проверка на s
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return false; // Проверка на успешное выделение памяти
    newNode->data = data;
    newNode->next = s->top;
    s->top = newNode;
    return true;
}

// Функция для проверки, пуст ли стек на основе массива
bool isEmptyArray(ArrayStack* s) {
    return s->top == 0;
}

// Функция для проверки, пуст ли стек на основе списка
bool isEmptyList(ListStack* s) {
    return s->top == NULL;
}

// Функция для извлечения элемента из стека на основе массива
char popArray(ArrayStack* s) {
    if (s->top > 0) // проверяем наличие элементов в стеке
        return s->items[--s->top]; // декрементируем вершину и возвращаем элемент с вершины
    return 0; // возвращаем 0, если элементов в стеке нет 
}

// Функция для извлечения элемента из стека на основе списка
char popList(ListStack* s) {
    if (s->top != NULL) { 
        Node* temp = s->top;
        char data = temp->data;
        s->top = s->top->next;
        free(temp);
        return data; 
    }
    return '\0'; 
}

// Функция для проверки, является ли w обратной строке s
int isReverse(const char* s, const char* w, bool useList) {
    // Проверка на пустые строки
    if (s == NULL || w == NULL || strlen(s) == 0 || strlen(w) == 0) {
        return 0; // Возвращаем 0, если одна из строк пустая
    }

    if (useList) {
        ListStack stack;
        initListStack(&stack);

        // Заполняем стек символами из строки s
        for (int i = 0; i < strlen(s); i++) {
            pushList(&stack, s[i]);
        }

        // Сравниваем с символами из строки w
        for (int i = 0; i < strlen(w); i++) {
            if (popList(&stack) != w[i]) {
                return 0; // Возвращаем 0, если не совпадает
            }
        }

        // Если стек пуст и все символы совпали, значит w - обратная строка s
        return isEmptyList(&stack);
    }
    else {
        ArrayStack stack;
        initArrayStack(&stack);

        // Заполняем стек символами из строки s
        for (int i = 0; i < strlen(s); i++) {
            pushArray(&stack, s[i]);
        }

        // Сравниваем с символами из строки w
        for (int i = 0; i < strlen(w); i++) {
            if (popArray(&stack) != w[i]) {
                return 0; // Возвращаем 0, если не совпадает
            }
        }

        // Если стек пуст и все символы совпали, значит w - обратная строка s
        return isEmptyArray(&stack);
    }
}

// Определение числа элементов в стеке на основе списка
int sizeList(ListStack* s) {
    int count = 0;
    Node* current = s->top;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// Функция для вывода строки
void printString(const char* str) {
    printf("%s\n", str);
}

// Очистка стека на основе списка
void clearList(ListStack* s) {
    while (!isEmptyList(s)) {
        popList(s);
    }
}

// Очистка стека на основе массива
void clearArray(ArrayStack* s) {
    s->top = 0; // Просто сбрасываем индекс
}

int main() {
    setlocale(LC_ALL, "Rus");

    char s[MAX_SIZE];
    char w[MAX_SIZE];
    int choice;
    int stackType; // Переменная для выбора типа стека

    // Выбор типа стека
    printf("Выберите тип стека:\n");
    printf("1. Стек на основе массива\n");
    printf("2. Стек на основе списка\n");
    printf("Выберите тип (1-2): ");
    scanf("%d", &stackType);
    getchar(); // Очищаем буфер ввода

    if (stackType != 1 && stackType != 2) {
        printf("Неверный выбор. Завершение программы.\n");
        return 1;
    }

    ArrayStack arrayStack; // Стек на основе массива
    ListStack listStack;   // Стек на основе списка
    if (stackType == 1) {
        initArrayStack(&arrayStack);
    }
    else {
        initListStack(&listStack);
    }

    while (1) {
        // Меню
        printf("Меню:\n");
        printf("1. Ввести строки s и w\n");
        printf("2. Проверить, является ли w обратной строке s\n");
        printf("3. Вывести строки s и w\n");
        printf("4. Определить размер стека\n");
        printf("5. Очистить стек\n");
        printf("6. Показать элемент на вершине стека\n");
        printf("7. Выход\n");
        printf("Выберите действие (1-7): ");
        scanf("%d", &choice);
        getchar(); // Очищаем буфер ввода

        switch (choice) {
        case 1:
            // Ввод строки s
            printf("Введите строку s: ");
            scanf(" %[^\n]", s); 

            // Ввод строки w
            printf("Введите строку w: ");
            scanf(" %[^\n]", w); 
            break;

        case 2:
            if (stackType == 1) {
                if (isReverse(s, w, false)) {
                    printf("Ответ: положительный\n");
                }
                else {
                    printf("Ответ: отрицательный\n");
                }
            }
            else {
                if (isReverse(s, w, true)) {
                    printf("Ответ: положительный\n");
                }
                else {
                    printf("Ответ: отрицательный\n");
                }
            }
            break;

        case 3:
            printf("Вы ввели:\n");
            printf("s: ");
            printString(s);
            printf("w: ");
            printString(w);
            break;

        case 4:
            if (stackType == 1) {
                printf("Размер стека: %d\n", arrayStack.top);
            }
            else {
                printf("Размер стека: %d\n", sizeList(&listStack));
            }
            break;

        case 5:
            if (stackType == 1) {
                clearArray(&arrayStack);
                printf("Стек очищен.\n");
            }
            else {
                clearList(&listStack);
                printf("Стек очищен.\n");
            }
            break;

        case 6:
            if (stackType == 1) {
                if (!isEmptyArray(&arrayStack)) {
                    char topElement = arrayStack.items[arrayStack.top - 1];
                    printf("Элемент на вершине стека: %c\n", topElement);
                }
                else {
                    printf("Стек пуст, нет элемента на вершине.\n");
                }
            }
            else {
                if (!isEmptyList(&listStack)) {
                    char topElement = listStack.top->data;
                    printf("Элемент на вершине стека: %c\n", topElement);
                }
                else {
                    printf("Стек пуст, нет элемента на вершине.\n");
                }
            }
            break;

        case 7:
            printf("Выход из программы.\n");
            // Освобождение памяти для стека на основе списка
            if (stackType == 2) {
                clearList(&listStack);
            }
            exit(0); // Завершение программы

        default:
            printf("Неверный выбор. Пожалуйста, выберите действие от 1 до 7.\n");
        }
    }

    return 0;
}



