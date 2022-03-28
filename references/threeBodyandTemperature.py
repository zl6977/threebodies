'''三体问题求解及可视化,去掉了动图模块'''
'''Coworker：聂嘉颖，张瀚文'''
import numpy as np
from numpy import arange
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from math import sqrt


# 得到太阳对行星夹角的cot值
def sun_height(x0, y0, z0, x1, y1, z1):
    a0 = x1 - x0
    b0 = y1 - y0
    c0 = z1 - z0
    return a0 / sqrt(b0 ** 2 + c0 ** 2)


# 得到两星体间的距离
def distants(x0, y0, z0, x1, y1, z1):
    return sqrt((x0 - x1) ** 2 + (y0 - y1) ** 2 + (z0 - z1) ** 2)


# 计算某一瞬时某一星体对行星的辐射强度
def sun_heat(d, sun_temperature, x0, y0, z0, x1, y1, z1):
    theta = d/distants(x0, y0, z0, x1, y1, z1)
    earth_temperature = 0.5 * sqrt(theta) * sun_temperature
    # print(earth_temperature)
    return earth_temperature

# 定义星体质量
# star_4选定为行星，其余为恒星
star_1_mass = 3e30  # kg
star_2_mass = 2e30  # kg
star_3_mass = 3e30  # kg
star_4_mass = 2e30  # kg

diameter0 = 1.0392e10  # 米
diameter1 = 1.0392e10  # 米
diameter2 = 1.00392e11  # 米

# 定义恒星表面温度
sun_temperature0 = 60.  # K
sun_temperature1 = 600.  # K
sun_temperature2 = 60.  # K

# 引力常数
gravitational_constant = 6.67e-11  # m3 / kg s2

# 行星运动总时长（按地球年计算）
# 每两小时计算一次星体位置
end_time = 16 * 365.26 * 24. * 3600.  # s
end_time = 10 * 365.26 * 24. * 3600.  # s
h = 2. * 3600  # s
num_steps = int(end_time / h)
tpoints = arange(0, end_time, h)


def three_body_problem():
    '''主程序，计算星体位置和表面温度'''
    positions = np.zeros([num_steps + 1, 4, 3])  # m
    velocities = np.zeros([num_steps + 1, 4, 3])  # m / s

    positions[0] = np.array([[1., 3., 2.], [6., -5., 4.], [7., 8., -7.], [7., -2., 9.]]) * 1e11  # m
    velocities[0] = np.array([[-2., 0.5, 5.], [7., 0.5, 2.], [4., -0.5, 3.], [-10., 4., -2.]]) * 1e3  # m/s
    positions[0] = np.array([[1., 3., 2.], [3., -5., 1.], [2., 8., -7.], [-3., -2., 9.]]) * 1e11  # m
    velocities[0] = np.array([[0, 0., 0.], [0., 0., 0.], [0., 0., 0.], [0., 0., 0.]]) * 1e3  # m/s

    def acceleration(positions):
        a = np.zeros([4, 3])
        a[0] = gravitational_constant * star_2_mass / np.linalg.norm(positions[0] - positions[1]) ** 3 * (
            positions[1] - positions[0]) + gravitational_constant * star_3_mass / np.linalg.norm(
            positions[0] - positions[2]) ** 3 * (positions[2] - positions[
            0]) + gravitational_constant * star_4_mass / np.linalg.norm(positions[0] - positions[3]) ** 3 * (
        positions[3] - positions[0])
        a[1] = gravitational_constant * star_1_mass / np.linalg.norm(positions[1] - positions[0]) ** 3 * (
            positions[0] - positions[1]) + gravitational_constant * star_3_mass / np.linalg.norm(
            positions[1] - positions[2]) ** 3 * (positions[2] - positions[
            1]) + gravitational_constant * star_4_mass / np.linalg.norm(positions[1] - positions[3]) ** 3 * (
        positions[3] - positions[1])
        a[2] = gravitational_constant * star_1_mass / np.linalg.norm(positions[2] - positions[0]) ** 3 * (
            positions[0] - positions[2]) + gravitational_constant * star_2_mass / np.linalg.norm(
            positions[2] - positions[1]) ** 3 * (positions[1] - positions[
            2]) + gravitational_constant * star_4_mass / np.linalg.norm(positions[2] - positions[3]) ** 3 * (
        positions[3] - positions[2])
        a[3] = gravitational_constant * star_1_mass / np.linalg.norm(positions[3] - positions[0]) ** 3 * (
        positions[0] - positions[3]) + gravitational_constant * star_2_mass / np.linalg.norm(
            positions[3] - positions[1]) ** 3 * (positions[1] - positions[
            3]) + gravitational_constant * star_3_mass / np.linalg.norm(positions[3] - positions[2]) ** 3 * (
        positions[2] - positions[3])
        return a

    def velocity(p, t, velo):
        v = np.zeros([4, 3])
        v[0] = acceleration(p)[0] * t + velo[0]
        v[1] = acceleration(p)[1] * t + velo[1]
        v[2] = acceleration(p)[2] * t + velo[2]
        v[3] = acceleration(p)[3] * t + velo[3]
        return velocities[step]

    heat_sum, t = [0.1], [0]

    per_0 = 0
    for step in range(num_steps):
        # 四阶龙格库塔法求星体位置
        j1 = h * velocity(positions[step], h, velocities[step])
        j2 = h * velocity(positions[step] + 0.5 * j1, h + 0.5 * h, velocities[step])
        j3 = h * velocity(positions[step] + 0.5 * j2, h + 0.5 * h, velocities[step])
        j4 = h * velocity(positions[step] + j3, h + h, velocities[step])
        positions[step + 1] = positions[step] + (j1 + 2 * j2 + 2 * j3 + j4) / 6
        velocities[step + 1] = velocities[step] + h * acceleration(positions[step + 1])

        # 从 positions 中取出坐标值
        x0, y0, z0 = positions[step, 0, 0], positions[step, 0, 1], positions[step, 0, 2]
        x1, y1, z1 = positions[step, 1, 0], positions[step, 1, 1], positions[step, 1, 2]
        x2, y2, z2 = positions[step, 2, 0], positions[step, 2, 1], positions[step, 2, 2]
        x3, y3, z3 = positions[step, 3, 0], positions[step, 3, 1], positions[step, 3, 2]

        # 计算三个太阳对行星表面的总辐射强度
        heat0 = sun_heat(diameter0, sun_temperature0, x0, y0, z0, x3, y3, z3)
        heat1 = sun_heat(diameter1, sun_temperature1, x1, y1, z1, x3, y3, z3)
        heat2 = sun_heat(diameter2, sun_temperature2, x2, y2, z2, x3, y3, z3)
        heat_sum.append(heat0 + heat1 + heat2)

        per = int(100 * step / num_steps)
        if per > per_0:
            print(per, '%')
            per_0 = per

        t.append(step)

    return positions, t, heat_sum

positions, t, heat_sum = three_body_problem()


empty, extinction_line, frozen_line = [], [], []

for i in range(len(t)):
    empty.append(0)
    extinction_line.append(100)
    frozen_line.append(40)


fig, ax = plt.subplots()
fig.set_tight_layout(True)
plt.plot(t, heat_sum, 'b')
plt.plot(t, empty, 'g')
plt.plot(t, extinction_line, 'r')
plt.plot(t, frozen_line, 'r')

ax.set_xlabel('X')
ax.set_xlim(0, len(t)+10e3)
ax.set_ylabel('Y')
plt.show()

print("\033[1;31;47m---Begin ploting image---\033[0m")

fig = plt.figure()
ax2 = Axes3D(fig)

ax2.plot(positions[:, 0, 0], positions[:, 0, 1], positions[:, 0, 2], color='b')
ax2.plot(positions[:, 1, 0], positions[:, 1, 1], positions[:, 1, 2], color='y')
ax2.plot(positions[:, 2, 0], positions[:, 2, 1], positions[:, 2, 2], color='b')
ax2.plot(positions[:, 3, 0], positions[:, 3, 1], positions[:, 3, 2], color='r')

zoom = 1.2e12
ax2.set_xlabel('X')
# ax2.set_xlim3d(-zoom, zoom + 3.e12)
ax2.set_ylabel('Y')
# ax2.set_ylim3d(-zoom, zoom)
ax2.set_zlabel('Z')
# ax2.set_zlim3d(-zoom, zoom + 2.e12)
print("100 %")

plt.show()