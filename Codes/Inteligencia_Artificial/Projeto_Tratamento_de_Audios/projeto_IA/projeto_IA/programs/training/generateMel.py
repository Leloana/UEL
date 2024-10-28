import re
import num2words
import os
from train import create_hparams
from train import create_mels


# Caminhos dos arquivos
list_file_path = 'tacotron2/filelists/list.txt'
temp_list_file_path = 'tacotron2/filelists/list1.txt'

# Ler e processar o arquivo de lista
with open(list_file_path, 'r') as f_input:
    text = f_input.readlines()

text2 = len(text)
textmacaca = ""

for number in range(0, text2):
    macaca = number
    if f"{macaca}.wav" in text[number]:
        pass
    else:
        textmacaca = text[number]
        textmacaca2 = textmacaca.split("|")
        textmacaca2[1] = re.sub(r"(\d+)", lambda x: num2words.num2words(int(x.group(0)), lang='pt_BR'), textmacaca2[1])
        text[number] = f"{textmacaca2[0]}|{textmacaca2[1].lower()}"

textfinal = "".join(text).replace('[', '').replace("',", '').replace("'", '').replace(']', '').replace('\\n', '\n').replace(' wavs', 'wavs')
with open(temp_list_file_path, "w") as f_output:
    f_output.write(textfinal)

# Substituir o arquivo original pelo modificado
os.remove(list_file_path)
os.rename(temp_list_file_path, list_file_path)

print("Gerando mels")
if generate_mels:
    create_mels()

print("Checando por arquivos faltando")

# ---- Replace .wav with .npy in filelists ----
with open(hparams.training_files, 'r') as file:
    content = file.read()
content = content.replace('.wav|', '.npy|')
with open(hparams.training_files, 'w') as file:
    file.write(content)

with open(hparams.validation_files, 'r') as file:
    content = file.read()
content = content.replace('.wav|', '.npy|')
with open(hparams.validation_files, 'w') as file:
    file.write(content)

check_dataset(hparams)
