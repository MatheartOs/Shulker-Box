import numpy as np
import matplotlib.pyplot as plt
from matplotlib.widgets import Slider
from noise import pnoise2  # 安装: pip install noise

# 生成Perlin噪声图的函数
def generate_perlin_noise(width, height, scale=50.0, offset_x=0, offset_y=0, octaves=6, persistence=0.5, lacunarity=2.0):
    """
    生成二维Perlin噪声图
    参数:
        width, height: 图像尺寸
        scale: 噪声缩放比例（值越大，噪声越平滑）
        offset_x, offset_y: 噪声偏移量
        octaves: 噪声层数（增加细节）   
        persistence: 振幅衰减系数（0~1）
        lacunarity: 频率倍增系数（通常为2）
    """
    noise_map = np.zeros((height, width))
    
    for y in range(height):
        for x in range(width):
            # 计算噪声值（范围通常为[-1, 1]）
            nx = offset_x + x / scale
            ny = offset_y + y / scale
            noise_map[y][x] = pnoise2(
                nx, ny,
                octaves=octaves,
                persistence=persistence,
                lacunarity=lacunarity,
                repeatx=1024,
                repeaty=1024
            )
    
    # 将噪声值归一化到[0, 1]
    noise_map = (noise_map - np.min(noise_map)) / (np.max(noise_map) - np.min(noise_map))
    return noise_map

# 初始参数
width, height = 512, 512
scale = 50.0
offset_x, offset_y = 0, 0
octaves = 6
persistence = 0.5
lacunarity = 2.0

# 生成初始噪声图
noise_map = generate_perlin_noise(width, height, scale, offset_x, offset_y, octaves, persistence, lacunarity)

# 绘制图像
fig, ax = plt.subplots(figsize=(8, 8))
plt.subplots_adjust(bottom=0.4)  # 为控件预留空间
img = ax.imshow(noise_map, cmap='viridis', interpolation='bilinear')
plt.colorbar(img, ax=ax, label='Noise Intensity')

# 添加交互式控件
ax_scale = plt.axes([0.2, 0.3, 0.6, 0.03])
ax_offsetx = plt.axes([0.2, 0.25, 0.6, 0.03])
ax_offsety = plt.axes([0.2, 0.2, 0.6, 0.03])
ax_octaves = plt.axes([0.2, 0.15, 0.6, 0.03])
ax_persistence = plt.axes([0.2, 0.1, 0.6, 0.03])

slider_scale = Slider(ax_scale, 'Scale', 1, 100, valinit=scale)
slider_offsetx = Slider(ax_offsetx, 'Offset X', -100, 100, valinit=offset_x)
slider_offsety = Slider(ax_offsety, 'Offset Y', -100, 100, valinit=offset_y)
slider_octaves = Slider(ax_octaves, 'Octaves', 1, 10, valinit=octaves, valstep=1)
slider_persistence = Slider(ax_persistence, 'Persistence', 0.1, 1, valinit=persistence)

# 更新函数
def update(val):
    noise_map = generate_perlin_noise(
        width, height,
        scale=slider_scale.val,
        offset_x=slider_offsetx.val,
        offset_y=slider_offsety.val,
        octaves=int(slider_octaves.val),
        persistence=slider_persistence.val,
        lacunarity=lacunarity
    )
    img.set_array(noise_map)
    fig.canvas.draw_idle()

# 绑定控件事件
slider_scale.on_changed(update)
slider_offsetx.on_changed(update)
slider_offsety.on_changed(update)
slider_octaves.on_changed(update)
slider_persistence.on_changed(update)

plt.show()