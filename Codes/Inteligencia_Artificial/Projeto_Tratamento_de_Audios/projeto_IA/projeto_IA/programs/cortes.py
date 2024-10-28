from pydub import AudioSegment
import os

def split_audio(input_file, output_dir, segment_length_ms):
    # Carregar o arquivo de áudio
    audio = AudioSegment.from_wav(input_file)
    
    # Obter o comprimento do áudio em milissegundos
    audio_length_ms = len(audio)
    
    # Criar o diretório de saída se não existir
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)
    
    # Recortar o áudio em partes iguais
    segment_number = 1
    for start_time in range(0, audio_length_ms, segment_length_ms):
        end_time = min(start_time + segment_length_ms, audio_length_ms)
        segment = audio[start_time:end_time]
        
        # Criar o nome do arquivo de saída
        output_file = os.path.join(output_dir, f"{segment_number}.wav")
        
        # Exportar o segmento para o arquivo WAV
        segment.export(output_file, format="wav")
        
        print(f"Segmento {segment_number} salvo como {output_file}")
        
        segment_number += 1

# Definir o caminho do arquivo de entrada e do diretório de saída
input_file = ""  # Substitua pelo caminho do seu arquivo de áudio
output_dir = ""
segment_length_s = 6
segment_length_ms = segment_length_s * 1000

# Chamar a função para recortar o áudio
split_audio(input_file, output_dir, segment_length_ms)
