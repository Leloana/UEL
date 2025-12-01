import numpy as np
import cv2
import matplotlib.pyplot as plt

def quantizar_imagem(imagem, niveis):
    niveis = max(2, min(niveis, 256))

    intervalo = 256 / niveis

    imagem_quantizada = imagem.copy()
    
    if len(imagem.shape) == 3:  
        for canal in range(3):
            canal_quantizado = ((imagem[:, :, canal] / intervalo).astype(int))
            canal_quantizado = (canal_quantizado * intervalo + intervalo/2).astype(np.uint8)
            imagem_quantizada[:, :, canal] = canal_quantizado
    else: 
        canal_quantizado = ((imagem / intervalo).astype(int))
        canal_quantizado = (canal_quantizado * intervalo + intervalo/2).astype(np.uint8)
        imagem_quantizada = canal_quantizado
    
    return imagem_quantizada

def mostrar_imagens_quantizadas(original, quantizada, niveis):
    plt.figure(figsize=(12, 6))
    
    if len(original.shape) == 3:
        original_display = cv2.cvtColor(original, cv2.COLOR_BGR2RGB)
        quantizada_display = cv2.cvtColor(quantizada, cv2.COLOR_BGR2RGB)
    else:
        original_display = original
        quantizada_display = quantizada
    
    plt.subplot(1, 2, 1)
    plt.imshow(original_display, cmap='gray' if len(original.shape) == 2 else None)
    plt.title(f'Original (256 níveis)')
    plt.axis('off')
    
    plt.subplot(1, 2, 2)
    plt.imshow(quantizada_display, cmap='gray' if len(original.shape) == 2 else None)
    plt.title(f'Quantizada ({niveis} níveis)')
    plt.axis('off')
    
    plt.tight_layout()
    plt.show()

caminho_imagem = 'remi.jpg'
imagem_original = cv2.imread(caminho_imagem, cv2.IMREAD_COLOR) 

if imagem_original is None:
    print("Erro ao carregar a imagem. Verifique o caminho.")
else:
    imagem_cinza = cv2.cvtColor(imagem_original, cv2.COLOR_BGR2GRAY)
    
    niveis_quantizacao = [256, 64, 16, 4, 2]
    
    for niveis in niveis_quantizacao:
        imagem_quant_cinza = quantizar_imagem(imagem_cinza, niveis)

        print(f"\nResultados para {niveis} níveis de intensidade (escala de cinza):")
        mostrar_imagens_quantizadas(imagem_cinza, imagem_quant_cinza, niveis)