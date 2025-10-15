import numpy as np
import matplotlib.pyplot as plt
from noise import pnoise2  # pip install noise

def generate_terrain(width, height_range, scale=100.0, offset_x=0, offset_y=0, far_lands_effect=False):
    terrain = np.zeros(width)  # 存储每个x坐标的高度
    
    for x in range(width):
        nx = offset_x + x / scale
        
        if far_lands_effect and x > width // 2:
            nx *= 1e10  # 输入超大数值，模拟Far Lands
        
        noise_value = pnoise2(nx, offset_y, octaves=6, persistence=0.5, lacunarity=2.0)
        terrain[x] = int((noise_value + 1) * (height_range / 2))  # 映射到 [0, height_range]
    
    return terrain

# 生成地形
width = 500
height_range = 64  # 地形高度范围（类似MC的0~64）
terrain_normal = generate_terrain(width, height_range, scale=50, far_lands_effect=False)
terrain_far_lands = generate_terrain(width, height_range, scale=50, far_lands_effect=True)

# 绘制地形
plt.figure(figsize=(12, 6))

plt.subplot(1, 2, 1)
plt.plot(terrain_normal, color="green")
plt.title("Normal Minecraft Terrain")
plt.xlabel("X Coordinate")
plt.ylabel("Height")
plt.ylim(0, height_range)

plt.subplot(1, 2, 2)
plt.plot(terrain_far_lands, color="red")
plt.title("Far Lands (Glitched Terrain)")
plt.xlabel("X Coordinate")
plt.ylabel("Height")
plt.ylim(0, height_range)

plt.tight_layout()
plt.show()