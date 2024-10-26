import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from numpy.polynomial.polynomial import Polynomial

# Загрузка данных из файла txt
data = pd.read_csv('графики\data.txt', sep=",", header=None, names=['sortType', 'arrayType', 'size', 'time'])

# Получение уникальных типов сортировки
sort_types = data['sortType'].unique()

# Функция для построения регрессии
def plot_regression(x, y, degree, label):
    # Выполнение полиномиальной регрессии
    coefs = np.polyfit(x, y, degree)
    poly = np.poly1d(coefs)
    y_fit = poly(x)
    
    # Построение кривой регрессии
    plt.plot(x, y_fit, label=f'{label} (степень {degree})')

# Построение графиков для каждого типа сортировки
for sort_type in sort_types:
    # Фильтрация данных по текущему типу сортировки
    sort_data = data[data['sortType'] == sort_type]
    
    # Группировка данных по типу массива
    sorted_data = sort_data[sort_data['arrayType'] == 'Отсортированный']
    nearly_sorted_data = sort_data[sort_data['arrayType'] == 'Почти отсортированный (90/10)']
    random_data = sort_data[sort_data['arrayType'] == 'Случайный']
    reverse_sorted_data = sort_data[sort_data['arrayType'] == 'Отсортированный в обратном порядке']

    # Построение графиков
    plt.figure(figsize=(10, 6))
    plt.plot(sorted_data['size'], sorted_data['time'], 'o-', label='Отсортированный')
    plt.plot(nearly_sorted_data['size'], nearly_sorted_data['time'], 'o-', label='Почти отсортированный (90/10)')
    plt.plot(random_data['size'], random_data['time'], 'o-', label='Случайный')
    plt.plot(reverse_sorted_data['size'], reverse_sorted_data['time'], 'o-', label='Отсортированный в обратном порядке')

    # Построение регрессионных кривых для случайного массива
    if not random_data.empty:
        plot_regression(random_data['size'], random_data['time'], 2, 'Регрессия n^2')
        plot_regression(random_data['size'], random_data['time'], 1, 'Регрессия n')
        plot_regression(random_data['size'], random_data['time'], 3, 'Регрессия n^3')
    
    # Настройка графика
    plt.title(f'{sort_type} - Время сортировки')
    plt.xlabel('Размер массива')
    plt.ylabel('Время (секунды)')
    plt.legend()
    plt.grid(True)
    
    # Сохранение графика в файл
    plt.savefig(f'{sort_type}_regressionsorting.png')
    plt.show()
