import os
import torch
import numpy as np
import time
import random
import math
from tqdm import tqdm
from distutils.dir_util import copy_tree
from model import Tacotron2
from data_utils import TextMelLoader, TextMelCollate
from loss_function import Tacotron2Loss
from logger import Tacotron2Logger
from hparams import create_hparams
from utils import load_wav_to_torch, load_filepaths_and_text
from text import text_to_sequence
import matplotlib.pyplot as plt

def create_mels():import re
import num2words
import os

# Função para criar espectrogramas mel (deve ser implementada conforme sua necessidade)
def create_mels():
    print("Generating Mels")
    stft = layers.TacotronSTFT(
                hparams.filter_length, hparams.hop_length, hparams.win_length,
                hparams.n_mel_channels, hparams.sampling_rate, hparams.mel_fmin,
                hparams.mel_fmax)
    def save_mel(filename):
        audio, sampling_rate = load_wav_to_torch(filename)
        if sampling_rate != stft.sampling_rate:
            raise ValueError("{} {} SR doesn't match target {} SR".format(filename, 
                sampling_rate, stft.sampling_rate))
        audio_norm = audio / hparams.max_wav_value
        audio_norm = audio_norm.unsqueeze(0)
        audio_norm = torch.autograd.Variable(audio_norm, requires_grad=False)
        melspec = stft.mel_spectrogram(audio_norm)
        melspec = torch.squeeze(melspec, 0).cpu().numpy()
        np.save(filename.replace('.wav', ''), melspec)

    import glob
    wavs = glob.glob('wavs/*.wav')
    for i in tqdm(wavs):
        save_mel(i)
    pass

# Função para verificar o dataset (deve ser implementada conforme sua necessidade)
def check_dataset(hparams):
    # Implemente a função check_dataset() aqui
    pass

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
print("Generating Mels")
stft = layers.TacotronSTFT(
    hparams.filter_length, hparams.hop_length, hparams.win_length,
    hparams.n_mel_channels, hparams.sampling_rate, hparams.mel_fmin,
    hparams.mel_fmax)
def save_mel(filename):
    audio, sampling_rate = load_wav_to_torch(filename)
    if sampling_rate != stft.sampling_rate:
        raise ValueError(f"{filename} {sampling_rate} SR doesn't match target {stft.sampling_rate} SR")
    audio_norm = audio / hparams.max_wav_value
    audio_norm = audio_norm.unsqueeze(0)
    audio_norm = torch.autograd.Variable(audio_norm, requires_grad=False)
    melspec = stft.mel_spectrogram(audio_norm)
    melspec = torch.squeeze(melspec, 0).cpu().numpy()
    np.save(filename.replace('.wav', ''), melspec)

import glob
wavs = glob.glob('wavs/*.wav')
for i in tqdm(wavs):
    save_mel(i)

def prepare_dataloaders(hparams):
    trainset = TextMelLoader(hparams.training_files, hparams)
    valset = TextMelLoader(hparams.validation_files, hparams)
    collate_fn = TextMelCollate(hparams.n_frames_per_step)

    if hparams.distributed_run:
        train_sampler = DistributedSampler(trainset)
        shuffle = False
    else:
        train_sampler = None
        shuffle = True

    train_loader = DataLoader(trainset, num_workers=1, shuffle=shuffle,
                              sampler=train_sampler,
                              batch_size=hparams.batch_size, pin_memory=False,
                              drop_last=True, collate_fn=collate_fn)
    return train_loader, valset, collate_fn

def prepare_directories_and_logger(output_directory, log_directory, rank):
    if rank == 0:
        if not os.path.isdir(output_directory):
            os.makedirs(output_directory)
            os.chmod(output_directory, 0o775)
        logger = Tacotron2Logger(os.path.join(output_directory, log_directory))
    else:
        logger = None
    return logger

def load_model(hparams):
    model = Tacotron2(hparams).cuda()
    if hparams.fp16_run:
        model.decoder.attention_layer.score_mask_value = finfo('float16').min

    if hparams.distributed_run:
        model = apply_gradient_allreduce(model)

    return model

def warm_start_model(checkpoint_path, model, ignore_layers):
    assert os.path.isfile(checkpoint_path)
    print(f"Warm starting model from checkpoint '{checkpoint_path}'")
    checkpoint_dict = torch.load(checkpoint_path, map_location='cpu')
    model_dict = checkpoint_dict['state_dict']
    if len(ignore_layers) > 0:
        model_dict = {k: v for k, v in model_dict.items() if k not in ignore_layers}
        dummy_dict = model.state_dict()
        dummy_dict.update(model_dict)
        model_dict = dummy_dict
    model.load_state_dict(model_dict)
    return model

def load_checkpoint(checkpoint_path, model, optimizer):
    assert os.path.isfile(checkpoint_path)
    print(f"Loading checkpoint '{checkpoint_path}'")
    checkpoint_dict = torch.load(checkpoint_path, map_location='cpu')
    model.load_state_dict(checkpoint_dict['state_dict'])
    optimizer.load_state_dict(checkpoint_dict['optimizer'])
    learning_rate = checkpoint_dict['learning_rate']
    iteration = checkpoint_dict['iteration']
    print(f"Loaded checkpoint '{checkpoint_path}' from iteration {iteration}")
    return model, optimizer, learning_rate, iteration

def save_checkpoint(model, optimizer, learning_rate, iteration, filepath):
    if random.random() > 0.85:
        print(f"Saving model and optimizer state at iteration {iteration} to {filepath}")
        try:
            torch.save({
                'iteration': iteration,
                'state_dict': model.state_dict(),
                'optimizer': optimizer.state_dict(),
                'learning_rate': learning_rate
            }, filepath)
        except KeyboardInterrupt:
            print("interrupt received while saving, waiting for save to complete.")
            torch.save({
                'iteration': iteration,
                'state_dict': model.state_dict(),
                'optimizer': optimizer.state_dict(),
                'learning_rate': learning_rate
            }, filepath)
        print("Model Saved")

def plot_alignment(alignment, info=None):
    fig, ax = plt.subplots(figsize=(alignment_graph_width / 100, alignment_graph_height / 100))
    im = ax.imshow(alignment, cmap='inferno', aspect='auto', origin='lower', interpolation='none')
    ax.autoscale(enable=True, axis="y", tight=True)
    fig.colorbar(im, ax=ax)
    xlabel = 'Decoder timestep'
    if info is not None:
        xlabel += '\n\n' + info
    plt.xlabel(xlabel)
    plt.ylabel('Encoder timestep')
    plt.tight_layout()
    plt.show()

def validate(model, criterion, valset, iteration, batch_size, n_gpus, collate_fn, logger, distributed_run, rank, epoch, start_epoch, learning_rate):
    model.eval()
    with torch.no_grad():
        val_sampler = DistributedSampler(valset) if distributed_run else None
        val_loader = DataLoader(valset, sampler=val_sampler, num_workers=1,
                                shuffle=False, batch_size=batch_size,
                                pin_memory=False, collate_fn=collate_fn)

        val_loss = 0.0
        for i, batch in enumerate(val_loader):
            x, y = model.parse_batch(batch)
            y_pred = model(x)
            loss = criterion(y_pred, y)
            reduced_val_loss = reduce_tensor(loss.data, n_gpus).item() if distributed_run else loss.item()
            val_loss += reduced_val_loss
        val_loss = val_loss / (i + 1)

    model.train()
    if rank == 0:
        print(f"Epoch: {epoch} Validation loss {iteration}: {val_loss:9f}  Time: {(time.perf_counter() - start_epoch) / 60:.1f}m LR: {learning_rate:.6f}")
        logger.log_validation(val_loss, model, y, y_pred, iteration)
        if hparams.show_alignments:
            _, mel_outputs, gate_outputs, alignments = y_pred
            idx = random.randint(0, alignments.size(0) - 1)
            plot_alignment(alignments[idx].data.cpu().numpy().T)

def train(output_directory, log_directory, checkpoint_path, warm_start, n_gpus, rank, group_name, hparams, log_directory2):
    if hparams.distributed_run:
        init_distributed(hparams, n_gpus, rank, group_name)

    torch.manual_seed(hparams.seed)
    torch.cuda.manual_seed(hparams.seed)

    model = load_model(hparams)
    learning_rate = hparams.learning_rate
    optimizer = torch.optim.Adam(model.parameters(), lr=learning_rate, weight_decay=hparams.weight_decay)

    if hparams.fp16_run:
        from apex import amp
        model, optimizer = amp.initialize(model, optimizer, opt_level='O2')

    if hparams.distributed_run:
        model = apply_gradient_allreduce(model)

    criterion = Tacotron2Loss()

    logger = prepare_directories_and_logger(output_directory, log_directory, rank)

    train_loader, valset, collate_fn = prepare_dataloaders(hparams)

    iteration = 0
    epoch_offset = 0
    if checkpoint_path is not None and os.path.isfile(checkpoint_path):
        if warm_start:
            model = warm_start_model(checkpoint_path, model, hparams.ignore_layers)
        else:
            model, optimizer, _learning_rate, iteration = load_checkpoint(checkpoint_path, model, optimizer)
            if hparams.use_saved_learning_rate:
                learning_rate = _learning_rate
            iteration += 1
            epoch_offset = max(0, iteration // len(train_loader) - 1)

    while True:
        for epoch in range(epoch_offset, hparams.epochs):
            start_epoch = time.perf_counter()
            train_loader.sampler.set_epoch(epoch)
            model.train()
            for i, batch in enumerate(train_loader):
                x, y = model.parse_batch(batch)
                optimizer.zero_grad()
                y_pred = model(x)
                loss = criterion(y_pred, y)
                if hparams.fp16_run:
                    with amp.scale_loss(loss, optimizer) as scaled_loss:
                        scaled_loss.backward()
                else:
                    loss.backward()
                optimizer.step()
                iteration += 1

                if iteration % hparams.checkpoint_interval == 0:
                    save_checkpoint(model, optimizer, learning_rate, iteration, f"{output_directory}/checkpoint_{iteration}.tar")

            validate(model, criterion, valset, iteration, hparams.batch_size, n_gpus, collate_fn, logger, hparams.distributed_run, rank, epoch, start_epoch, learning_rate)

            if epoch % hparams.save_interval == 0:
                save_checkpoint(model, optimizer, learning_rate, iteration, f"{output_directory}/checkpoint_{iteration}.tar")

if __name__ == "__main__":
    hparams = create_hparams()
    output_directory = 'output_directory'
    log_directory = 'log_directory'
    checkpoint_path = 'checkpoint_path'
    warm_start = False
    n_gpus = 1
    rank = 0
    group_name = 'group_name'
    log_directory2 = 'log_directory2'
    train(output_directory, log_directory, checkpoint_path, warm_start, n_gpus, rank, group_name, hparams, log_directory2)
