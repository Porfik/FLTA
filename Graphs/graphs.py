import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# Путь к файлу с результатами
filename = 'results.csv'

# Чтение данных из файла
try:
    df = pd.read_csv(filename, sep='\t', header=0)
except FileNotFoundError:
    print(f"Файл '{filename}' не найден. Убедитесь, что он существует.")
    exit()

# Переименование столбцов
df.columns = ['Size', 'HeapSort', 'BubbleSort']

# Преобразуем данные в numpy-массивы
sizes = df['Size'].values
heap_times = df['HeapSort'].values
bubble_times = df['BubbleSort'].values

# Теоретические функции
def theor_heap(n):
    return n * np.log(n)

def theor_bubble(n):
    return n ** 2

# Функция для нормализации теоретической кривой
def normalize_theory(exp_times, theor_func):
    k = exp_times[-1] / theor_func(sizes[-1])
    return k * theor_func(sizes)

# Нормализованные теоретические кривые
norm_theor_heap = normalize_theory(heap_times, theor_heap)
norm_theor_bubble = normalize_theory(bubble_times, theor_bubble)

# Построение графика сравнения зависимости скорости сортировок
plt.figure(figsize=(12, 5))

# График для пирамидальной сортировки
plt.plot(sizes, heap_times, label='Пирамидальная сортировка', color='blue')

# График для пузырьковой сортировки
plt.plot(sizes, bubble_times, label='Пузырьковая сортировка', color='red')

# Настройка графика
plt.title('Сравнение зависимости скорости сортировок')
plt.xlabel('Количество элементов в массиве')
plt.ylabel('Время выполнения (секунды)')
plt.grid(True)
plt.legend()

# Сохранение графика в файл
plt.savefig('img/sort_comparison.png', dpi=300, bbox_inches='tight')

# График для пирамидальной сортировки
plt.figure(figsize=(12, 6))
plt.plot(sizes, heap_times, label='Полученная зависимость', color='blue', marker='', linestyle='-', markersize=1)
plt.plot(sizes, norm_theor_heap, label='Теоритическая зависимость O(n log n)', color='green', linestyle='--')
plt.title('Зависимость времени выполнения пирамидальной сортировки')
plt.xlabel('Количество элементов в массиве')
plt.ylabel('Время выполнения (секунды)')
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.savefig('img/heapsort_comparison.png', dpi=300, bbox_inches='tight')
plt.close()

# График для пузырьковой сортировки
plt.figure(figsize=(12, 6))
plt.plot(sizes, bubble_times, label='Полученная зависимость', color='red', marker='', linestyle='-', markersize=1)
plt.plot(sizes, norm_theor_bubble, label='Теоритическая зависимость O(n²)', color='green', linestyle='--')
plt.title('Зависимость времени выполнения пузырьковой сортировки')
plt.xlabel('Количество элементов в массиве')
plt.ylabel('Время выполнения (секунды)')
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.savefig('img/bubblesort_comparison.png', dpi=300, bbox_inches='tight')
plt.close()

print("Графики построены")