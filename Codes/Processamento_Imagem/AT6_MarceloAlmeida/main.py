import cv2
import numpy as np
import matplotlib.pyplot as plt
from filtros import cria_filtro
import os

def aplica_dft(img):
    dft = cv2.dft(np.float32(img), flags=cv2.DFT_COMPLEX_OUTPUT)
    return np.fft.fftshift(dft)

def calcula_magnitude(dft_shifted):
    magnitude = 20 * np.log(cv2.magnitude(dft_shifted[:, :, 0], dft_shifted[:, :, 1]) + 1)
    return magnitude

def aplica_filtro(dft_shifted, filtro):
    return dft_shifted * filtro[:, :, np.newaxis]

def reconstruir(dft_filtrado):
    f_ishift = np.fft.ifftshift(dft_filtrado)
    img_back = cv2.idft(f_ishift)
    img_back = cv2.magnitude(img_back[:, :, 0], img_back[:, :, 1])
    return cv2.normalize(img_back, None, 0, 255, cv2.NORM_MINMAX).astype(np.uint8)

def processar_imagem(nome_arquivo, filtro_tipo, d0, d1=None, notch_centros=None):
    img = cv2.imread(f'imagens/{nome_arquivo}', cv2.IMREAD_GRAYSCALE)
    dft = aplica_dft(img)
    mag = calcula_magnitude(dft)

    filtro = cria_filtro(img.shape, filtro_tipo, d0, d1, notch_centros)
    dft_filtrado = aplica_filtro(dft, filtro)
    mag_filtrado = calcula_magnitude(dft_filtrado)
    img_recon = reconstruir(dft_filtrado)

    mostrar_resultados(img, mag, mag_filtrado, img_recon, nome_arquivo)

def mostrar_resultados(original, espectro, espectro_filtrado, reconstruida, titulo):
    fig, axs = plt.subplots(1, 4, figsize=(16, 4))
    axs[0].imshow(original, cmap='gray')
    axs[0].set_title('Original')
    axs[1].imshow(espectro, cmap='gray')
    axs[1].set_title('Espectro')
    axs[2].imshow(espectro_filtrado, cmap='gray')
    axs[2].set_title('Espectro Filtrado')
    axs[3].imshow(reconstruida, cmap='gray')
    axs[3].set_title('Reconstruída')
    for ax in axs:
        ax.axis('off')
    plt.suptitle(titulo)
    plt.tight_layout()
    plt.show()


processar_imagem("figura1.tif", filtro_tipo="passa-baixa", d0=80)
processar_imagem("figura2.tif", filtro_tipo="passa-baixa", d0=40)
processar_imagem("figura3.tif", filtro_tipo="passa-baixa", d0=100) 
processar_imagem("figura4.tif", filtro_tipo="passa-baixa", d0=20) 
processar_imagem("figura5.tif", filtro_tipo="notch", d0=10, notch_centros=[(0, 50), (0, -50)])
processar_imagem("figura6.tif", filtro_tipo="passa-baixa", d0=40)
processar_imagem("figura7.tif", filtro_tipo="passa-baixa", d0=20) 
processar_imagem("figura8.tif", filtro_tipo="notch", d0=15, notch_centros=[(25, 25), (-25, -25), (30, 30), (-30, -30)])


def adicionar_ruido_sintetico(dft_shifted, intensidade=500):
    noise = np.random.rand(*dft_shifted.shape[:2]) * intensidade
    dft_shifted[:, :, 0] += noise
    dft_shifted[:, :, 1] += noise
    return dft_shifted

# Exemplo
img = cv2.imread("imagens/figura1.tif", cv2.IMREAD_GRAYSCALE)
dft = aplica_dft(img)
dft_ruidoso = adicionar_ruido_sintetico(dft.copy(), intensidade=200)
img_ruidosa = reconstruir(dft_ruidoso)
plt.imshow(img_ruidosa, cmap='gray')
plt.title("Imagem com ruído no espectro")
plt.axis('off')
plt.show()
