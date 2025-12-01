import numpy as np
import cv2
import matplotlib.pyplot as plt

def reduzir_resolucao(imagem, intervalo_amostragem):
    altura, largura = imagem.shape[0], imagem.shape[1]
    
    nova_altura = altura // intervalo_amostragem
    nova_largura = largura // intervalo_amostragem
    
    if len(imagem.shape) == 3:
        imagem_reduzida = np.zeros((nova_altura, nova_largura, 3), dtype=imagem.dtype)
    else: 
        imagem_reduzida = np.zeros((nova_altura, nova_largura), dtype=imagem.dtype)
    
    for i in range(nova_altura):
        for j in range(nova_largura):
            original_i = i * intervalo_amostragem
            original_j = j * intervalo_amostragem
            original_i = min(original_i, altura - 1)
            original_j = min(original_j, largura - 1)
            imagem_reduzida[i, j] = imagem[original_i, original_j]
    
    return imagem_reduzida

def mostrar_imagens(original, reduzida, intervalo):
    plt.figure(figsize=(12, 6))

    plt.subplot(1, 2, 1)
    plt.imshow(cv2.cvtColor(original, cv2.COLOR_BGR2RGB))
    plt.title(f'Original ({original.shape[1]}x{original.shape[0]})')
    plt.axis('off')
    
    plt.subplot(1, 2, 2)
    plt.imshow(cv2.cvtColor(reduzida, cv2.COLOR_BGR2RGB))
    plt.title(f'Reduzida (intervalo={intervalo})\n({reduzida.shape[1]}x{reduzida.shape[0]})')
    plt.axis('off')
    
    plt.tight_layout()
    plt.show()

caminho_imagem = 'remi.jpg'
imagem_original = cv2.imread(caminho_imagem)

if imagem_original is None:
    print("Erro ao carregar a imagem. Verifique o caminho.")
else:
    intervalos = [2, 4, 8, 16]
    
    for intervalo in intervalos:
        imagem_red = reduzir_resolucao(imagem_original, intervalo)

        mostrar_imagens(imagem_original, imagem_red, intervalo)