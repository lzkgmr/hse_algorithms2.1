import matplotlib.pyplot as plt
import numpy as np

# Путь к файлу с координатами
file_path = 'C:\\Users\\lzkgm\\c++\\set3_hse_aisd\\A2\\data\\random.txt'
file_path2 = 'C:\\Users\\lzkgm\\c++\\set3_hse_aisd\\A2\\data\\random100.txt'

# Чтение файла
with open(file_path, 'r', encoding = 'utf-8') as file:
    y_coords = list(map(float, file.readline().strip().split()))

with open(file_path2, 'r', encoding = 'utf-8') as file:
    y_coords2 = list(map(float, file.readline().strip().split()))

# Генерация X-координат
x_coords = np.arange(500, 10000 + 1, 100)


# Построение графика
plt.figure(figsize=(20, 12))
plt.plot(x_coords, y_coords, marker='o', linestyle='-', label='merge sort', color='r')
plt.plot(x_coords, y_coords2, marker='o', linestyle='-', label='merge + insertion sort', color='g')

plt.title("Сравнение на рандомных массивах. threshold = 100")
plt.xlabel('Размер массива')
plt.ylabel('Время в микросекундах')
plt.grid(True)
plt.legend()
plt.savefig('image6_1.jpg')