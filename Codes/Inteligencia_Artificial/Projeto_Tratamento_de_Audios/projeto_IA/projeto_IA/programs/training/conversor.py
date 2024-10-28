import os
import subprocess
import glob

# Diretório contendo os arquivos WAV
input_directory = 'wavs'
output_directory = 'wavs'

# Verifica se o diretório de saída existe
if not os.path.exists(output_directory):
    os.makedirs(output_directory)

# Obtém a lista de arquivos WAV
wav_files = glob.glob(os.path.join(input_directory, '*.wav'))

# Processa cada arquivo WAV
for file_path in wav_files:
    # Definindo o caminho do arquivo de saída
    output_path = os.path.join(output_directory, os.path.basename(file_path).replace('.wav', '-prepare.wav'))
    
    # Comando para converter o arquivo WAV
    command = [
        'ffmpeg', '-y', '-loglevel', 'error', 
        '-i', file_path, 
        '-ac', '1', '-acodec', 'pcm_s16le', '-ar', '22050', 
        '-sample_fmt', 's16', '-preset', 'ultrafast', 
        '-threads', '0', 
        output_path
    ]
    
    # Executa o comando
    subprocess.run(command, check=True)
    
    # Remove o arquivo original
    os.remove(file_path)
    
    # Renomeia o arquivo de saída para remover o sufixo '-prepare.wav'
    os.rename(output_path, file_path)

print("Conversão concluída!")
