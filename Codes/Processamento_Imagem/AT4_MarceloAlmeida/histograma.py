import numpy as np
import matplotlib.pyplot as plt
from PIL import Image

# Carrega a imagem colorida e converte para escala de cinza
imagem_colorida = Image.open('remi.webp')
imagem_cinza = imagem_colorida.convert('L')
img_array = np.array(imagem_cinza)

# Histograma original
histograma_original = np.bincount(img_array.flatten(), minlength=256)

# CDF (função de transformação)
cdf = np.cumsum(histograma_original)
cdf_normalizada = cdf * 255 / cdf[-1]
cdf_normalizada = cdf_normalizada.astype('uint8')

# Imagem equalizada
img_equalizada = cdf_normalizada[img_array]

# Histograma equalizado
histograma_equalizado = np.bincount(img_equalizada.flatten(), minlength=256)

# Cria uma grade 3x2 para plotar
fig, axes = plt.subplots(3, 2, figsize=(14, 12))

# Primeira linha: Imagem original e em tons de cinza
axes[0, 0].imshow(imagem_colorida)
axes[0, 0].set_title("Imagem Original (Colorida)")
axes[0, 0].axis('off')

axes[0, 1].imshow(img_array, cmap='gray')
axes[0, 1].set_title("Imagem em Tons de Cinza")
axes[0, 1].axis('off')

# Segunda linha: Imagem equalizada e função de transformação
axes[1, 0].imshow(img_equalizada, cmap='gray')
axes[1, 0].set_title("Imagem Equalizada")
axes[1, 0].axis('off')

axes[1, 1].plot(cdf_normalizada, color='blue')
axes[1, 1].set_title("Função de Transformação (CDF)")
axes[1, 1].set_xlabel("Intensidade Original")
axes[1, 1].set_ylabel("Intensidade Equalizada")

# Terceira linha: Histogramas
axes[2, 0].plot(histograma_original, color='gray')
axes[2, 0].set_title("Histograma Original")
axes[2, 0].set_xlabel("Intensidade")
axes[2, 0].set_ylabel("Frequência")

axes[2, 1].plot(histograma_equalizado, color='black')
axes[2, 1].set_title("Histograma Equalizado")
axes[2, 1].set_xlabel("Intensidade")
axes[2, 1].set_ylabel("Frequência")

# Ajuste fino de layout
plt.tight_layout()
plt.show()
