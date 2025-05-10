#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void heapsort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        int current = i;

        while (1) {
            int largest = current;
            int left = 2 * current + 1;
            int right = 2 * current + 2;

            if (left < n && arr[left] > arr[largest]) largest = left;
            if (right < n && arr[right] > arr[largest]) largest = right;

            if (largest != current) {
                int temp = arr[current];
                arr[current] = arr[largest];
                arr[largest] = temp;
                current = largest;
            } else {
                break;
            }
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        int temp = arr[0];
        int current = 0;
        arr[0] = arr[i];
        arr[i] = temp;

        while (1) {
            int largest = current;
            int left = 2 * current + 1;
            int right = 2 * current + 2;

            if (left < i && arr[left] > arr[largest]) largest = left;
            if (right < i && arr[right] > arr[largest]) largest = right;

            if (largest != current) {
                int temp = arr[current];
                arr[current] = arr[largest];
                arr[largest] = temp;
                current = largest;
            } else {
                break;
            }
        }
    }
}

void bubblesort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;

        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
}

int main() {
    // Инициализация генератора случайных чисел текущим временем
    // Это гарантирует разные последовательности случайных чисел при каждом запуске программы
    srand((unsigned int)time(NULL));

    // Вывод заголовка таблицы результатов
    // Столбцы: размер массива, время сортировки HeapSort, время сортировки BubbleSort
    printf("Размер\tHeapSort\tBubbleSort\n");

    // Цикл для тестирования сортировок на массивах разного размера
    // i меняется от 1 до 300, что соответствует размерам от 100 до 30000 элементов
    for (int i = 1; i <= 300; i++) {
        // Расчет текущего размера массива (умножение на 100)
        int size = i * 100;

        // Выделение памяти для исходного массива
        int *arr = (int*)malloc(size * sizeof(int));

        // Проверка успешности выделения памяти
        if (!arr) {
            fprintf(stderr, "Ошибка выделения памяти для размера %d\n", size);
            return 1;
        }

        // Заполнение массива случайными числами из диапазона 0...RAND_MAX
        for (int j = 0; j < size; j++) {
            arr[j] = rand();
        }

        // Создание копии массива для HeapSort
        int *arr_heap = (int*)malloc(size * sizeof(int));
        memcpy(arr_heap, arr, size * sizeof(int)); // Копирование данных

        // Создание копии массива для BubbleSort
        int *arr_bubble = (int*)malloc(size * sizeof(int));
        memcpy(arr_bubble, arr, size * sizeof(int)); // Копирование данных

        // Замер времени выполнения HeapSort
        clock_t start_heap = clock(); // Начало отсчета
        heapsort(arr_heap, size);     // Вызов алгоритма
        clock_t end_heap = clock();   // Конец отсчета

        // Замер времени выполнения BubbleSort
        clock_t start_bubble = clock();
        bubblesort(arr_bubble, size);
        clock_t end_bubble = clock();

        // Вычисление времени выполнения в секундах
        // Разница тиков делится на CLOCKS_PER_SEC (частота таймера)
        double time_heap = (double)(end_heap - start_heap) / CLOCKS_PER_SEC;
        double time_bubble = (double)(end_bubble - start_bubble) / CLOCKS_PER_SEC;

        // Вывод результатов в табличном формате
        // %.6f - форматирование с 6 знаками после запятой
        printf("%d\t%.6f\t%.6f\n", size, time_heap, time_bubble);

        // Освобождение всей выделенной памяти перед следующей итерацией
        free(arr);
        free(arr_heap);
        free(arr_bubble);
    }

    return 0; // Завершение программы
}