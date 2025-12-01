import numpy as np
import cv2

def cria_filtro(shape, tipo, d0, d1=None, notch_centros=None):
    rows, cols = shape
    crow, ccol = rows // 2, cols // 2
    filtro = np.ones((rows, cols), np.uint8)

    if tipo == "passa-baixa":
        for u in range(rows):
            for v in range(cols):
                if np.sqrt((u - crow) ** 2 + (v - ccol) ** 2) > d0:
                    filtro[u, v] = 0

    elif tipo == "passa-alta":
        for u in range(rows):
            for v in range(cols):
                if np.sqrt((u - crow) ** 2 + (v - ccol) ** 2) < d0:
                    filtro[u, v] = 0

    elif tipo == "passa-faixa" and d1 is not None:
        for u in range(rows):
            for v in range(cols):
                dist = np.sqrt((u - crow) ** 2 + (v - ccol) ** 2)
                if not (d0 <= dist <= d1):
                    filtro[u, v] = 0

    elif tipo == "notch" and notch_centros:
        for center in notch_centros:
            for u in range(rows):
                for v in range(cols):
                    du = np.sqrt((u - (crow + center[0])) ** 2 + (v - (ccol + center[1])) ** 2)
                    dv = np.sqrt((u - (crow - center[0])) ** 2 + (v - (ccol - center[1])) ** 2)
                    if du < d0 or dv < d0:
                        filtro[u, v] = 0

    return filtro
