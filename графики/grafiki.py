import pandas as pd
import matplotlib.pyplot as plt

# Загрузка данных из файла txt
data = pd.read_csv('графики\data.txt', sep=",", header=None, names=['sortType', 'arrayType', 'size', 'time'])

# Получение уникальных типов сортировки
sort_types = data['sortType'].unique()

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
    plt.plot(sorted_data['size'], sorted_data['time'], label='Отсортированный')
    plt.plot(nearly_sorted_data['size'], nearly_sorted_data['time'], label='Почти отсортированный (90/10)')
    plt.plot(random_data['size'], random_data['time'], label='Случайный')
    plt.plot(reverse_sorted_data['size'], reverse_sorted_data['time'], label='Отсортированный в обратном порядке')

    # Настройка графика
    plt.title(f'{sort_type} - Время сортировки')
    plt.xlabel('Размер массива')
    plt.ylabel('Время (секунды)')
    plt.legend()
    plt.grid(True)
    
    # Сохранение графика в файл
    plt.savefig(f'{sort_type}_sorting.png')
    plt.show()
