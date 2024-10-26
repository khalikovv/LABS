import numpy as np
import matplotlib.pyplot as plt

# Данные для построения графиков
n = np.arange(1, 1001)  # Размер массива от 1 до 1000

# Определение временной сложности для каждого алгоритма
def best_case_selection(n):
    return n**2

def avg_case_selection(n):
    return n**2

def worst_case_selection(n):
    return n**2

def best_case_insertion(n):
    return n

def avg_case_insertion(n):
    return n**2

def worst_case_insertion(n):
    return n**2

def best_case_bubble(n):
    return n

def avg_case_bubble(n):
    return n**2

def worst_case_bubble(n):
    return n**2

def best_case_merge(n):
    return n * np.log(n)

def avg_case_merge(n):
    return n * np.log(n)

def worst_case_merge(n):
    return n * np.log(n)

def best_case_shell(n):
    return n * np.log(n)**2

def avg_case_shell(n):
    return n * np.log(n)**2

def worst_case_shell(n):
    return n * np.log(n)**2

def best_case_shell_hibbard(n):
    return n**(3/2)

def avg_case_shell_hibbard(n):
    return n**(5/4)

def worst_case_shell_hibbard(n):
    return n**(3/2)

def best_case_shell_pratt(n):
    return n * np.log(n)**2

def avg_case_shell_pratt(n):
    return n * np.log(n)**2

def worst_case_shell_pratt(n):
    return n**(4/3)

def best_case_quick(n):
    return n * np.log(n)

def avg_case_quick(n):
    return n * np.log(n)

def worst_case_quick(n):
    return n**2

def best_case_heap(n):
    return n * np.log(n)

def avg_case_heap(n):
    return n * np.log(n)

def worst_case_heap(n):
    return n * np.log(n)

# Создание графиков
algorithms = {
    "Сортировка выбором": (best_case_selection, avg_case_selection, worst_case_selection),
    "Сортировка вставками": (best_case_insertion, avg_case_insertion, worst_case_insertion),
    "Сортировка пузырьком": (best_case_bubble, avg_case_bubble, worst_case_bubble),
    "Сортировка слиянием": (best_case_merge, avg_case_merge, worst_case_merge),
    "Сортировка Шелла (Шелл)": (best_case_shell, avg_case_shell, worst_case_shell),
    "Сортировка Шелла (Хиббард)": (best_case_shell_hibbard, avg_case_shell_hibbard, worst_case_shell_hibbard),
    "Сортировка Шелла (Пратт)": (best_case_shell_pratt, avg_case_shell_pratt, worst_case_shell_pratt),
    "Быстрая сортировка": (best_case_quick, avg_case_quick, worst_case_quick),
    "Пирамидальная сортировка": (best_case_heap, avg_case_heap, worst_case_heap),
}

# Настройка графиков
for algo, cases in algorithms.items():
    plt.figure(figsize=(10, 6))
    
    # Лучший случай
    plt.plot(n, cases[0](n), label='Лучший случай', color='green')
    # Средний случай
    plt.plot(n, cases[1](n), label='Средний случай', color='blue')
    # Худший случай
    plt.plot(n, cases[2](n), label='Худший случай', color='red')
    
    plt.title(algo)
    plt.xlabel('Размер массива (n)')
    plt.ylabel('Время (с)')
    plt.yscale('log')  # Логарифмическая шкала для удобства
    plt.legend()
    plt.grid(True)
    plt.show()
