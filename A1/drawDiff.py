import matplotlib.pyplot as plt
import numpy as np

# Путь к файлу с координатами
file_path = "C:\\Users\\lzkgm\\c++\\set3_hse_aisd\\A1\\diffNarrow.txt"
file_path2 = 'C:\\Users\\lzkgm\\c++\\set3_hse_aisd\\A1\\diffWide.txt'

y_coords = []
y_coords2 = []
# Чтение файла
with open(file_path) as file:
    for line in file.readlines():
      line = line.rstrip("\n")
      y_coords.append(float(line.split(", ")[1]))

with open(file_path2) as file:
    for line in file.readlines():
      line = line.rstrip("\n")
      y_coords2.append(float(line.split(", ")[1]))

# Генерация X-координат
x_coords = np.arange(100, 100001, 500)


# Построение графика
plt.figure(figsize=(15, 10))
plt.plot(x_coords, y_coords, marker='o', markersize = 3, linestyle='-', label='Площадь в узкой области', color='r')
plt.plot(x_coords, y_coords2, marker='o', markersize = 3, linestyle='-', label='Площадь в широкой области', color='g')

plt.title("Отклонение приближенной площади от реальной")
plt.xlabel('N - количество сгенерированных точек')
plt.ylabel('S - площадь')
plt.grid(True)
plt.legend()
plt.savefig('diff.jpg')