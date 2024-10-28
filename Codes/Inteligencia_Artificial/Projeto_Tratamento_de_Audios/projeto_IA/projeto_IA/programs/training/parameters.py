import os
from pathlib import Path

# Configurar os parâmetros do modelo
model_filename = "modelo-teste-final"  # Nome desejado para o modelo
Training_file = "filelists/list.txt"  # Caminho para o arquivo de transcrição
hparams = {}  # Inicialize o dicionário de parâmetros

# Configurações do modelo
hparams['training_files'] = Training_file
hparams['validation_files'] = Training_file
hparams['p_attention_dropout'] = 0.1
hparams['p_decoder_dropout'] = 0.1
hparams['decay_start'] = 15000
hparams['A_'] = 5e-4
hparams['B_'] = 8000
hparams['C_'] = 0
hparams['min_learning_rate'] = 1e-5
hparams['batch_size'] = 18
hparams['load_mel_from_disk'] = True
hparams['epochs'] = 250

# Configuração do diretório de saída e logs
output_directory = 'outdir'  # Diretório local para salvar o modelo
log_directory = 'logs'  # Diretório local para salvar logs
checkpoint_path = os.path.join(output_directory, model_filename)

# Verificar se o modelo base deve ser utilizado
modelo_base = True  # Defina como True ou False conforme necessário
newpath = os.path.join(output_directory)
if not os.path.exists(newpath):
    os.makedirs(newpath)

if modelo_base:
    status_arquivo = os.path.isfile(os.path.join(output_directory, model_filename))
    if status_arquivo:
        print("Já tem um arquivo com esse nome no diretório. Se quiser utilizar o modelo base, terá de apagar/renomear esse arquivo.")
    else:
        # Baixar o modelo base - substitua a URL pelo link adequado
        os.system("wget -O {} https://example.com/path/to/model_base".format(os.path.join(output_directory, model_filename)))

# Inicializar PyTorch (exemplo)
import torch
torch.backends.cudnn.enabled = hparams.get('cudnn_enabled', True)
torch.backends.cudnn.benchmark = hparams.get('cudnn_benchmark', True)
