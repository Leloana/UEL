import re
import os
import sys
import time
import json
import torch
import numpy as np
import matplotlib.pyplot as plt
import scipy.signal
import resampy
import num2words
from hparams import create_hparams
from model import Tacotron2
from layers import TacotronSTFT
from audio_processing import griffin_lim
from text import text_to_sequence
from env import AttrDict
from meldataset import mel_spectrogram, MAX_WAV_VALUE
from models import Generator
from denoiser import Denoiser

# Configurações
TACOTRON2_ID = "/training/modelo-teste-final"
HIFIGAN_ID = "hifigan_model"
MAX_WAV_VALUE = 32768.0
superres_strength = 0.0
show_graphs = True
pronounciation_dictionary = False
max_duration = 25
stop_threshold = 0.5

# Funções auxiliares
def plot_data(data):
    fig, axes = plt.subplots(1, len(data), figsize=(9, 3.6))
    for i in range(len(data)):
        axes[i].imshow(data[i], aspect='auto', origin='lower', interpolation='none', cmap='inferno')
    plt.show()

def end_to_end_infer(text, pronounciation_dictionary, show_graphs):
    for i in [x for x in text.split("\n") if len(x)]:
        if not pronounciation_dictionary:
            if i[-1] != ";": i=i+";"
        else: i = ARPA(i)
        with torch.no_grad():
            sequence = np.array(text_to_sequence(i, ['basic_cleaners']))[None, :]
            sequence = torch.autograd.Variable(torch.from_numpy(sequence)).cuda().long()
            mel_outputs, mel_outputs_postnet, _, alignments = model.inference(sequence)
            if show_graphs:
                plot_data((mel_outputs_postnet.float().data.cpu().numpy()[0], alignments.float().data.cpu().numpy()[0].T))
            y_g_hat = hifigan(mel_outputs_postnet.float())
            audio = y_g_hat.squeeze()
            audio = audio * MAX_WAV_VALUE
            audio_denoised = denoiser(audio.view(1, -1), strength=35)[:, 0]

            audio_denoised = audio_denoised.cpu().numpy().reshape(-1)
            normalize = (MAX_WAV_VALUE / np.max(np.abs(audio_denoised))) ** 0.9
            audio_denoised = audio_denoised * normalize
            wave = resampy.resample(audio_denoised, h.sampling_rate, h2.sampling_rate, filter="sinc_window", window=scipy.signal.windows.hann, num_zeros=8)
            wave_out = wave.astype(np.int16)

            wave = wave / MAX_WAV_VALUE
            wave = torch.FloatTensor(wave).to(torch.device("cuda"))
            new_mel = mel_spectrogram(wave.unsqueeze(0), h2.n_fft, h2.num_mels, h2.sampling_rate, h2.hop_size, h2.win_size, h2.fmin, h2.fmax)
            y_g_hat2 = hifigan_sr(new_mel)
            audio2 = y_g_hat2.squeeze()
            audio2 = audio2 * MAX_WAV_VALUE
            audio2_denoised = denoiser(audio2.view(1, -1), strength=35)[:, 0]

            audio2_denoised = audio2_denoised.cpu().numpy().reshape(-1)
            b = scipy.signal.firwin(101, cutoff=10500, fs=h2.sampling_rate, pass_zero=False)
            y = scipy.signal.lfilter(b, [1.0], audio2_denoised)
            y *= superres_strength
            y_out = y.astype(np.int16)
            y_padded = np.zeros(wave_out.shape)
            y_padded[: y_out.shape[0]] = y_out
            sr_mix = wave_out + y_padded
            sr_mix = sr_mix / normalize

            print("")
            ipd.display(ipd.Audio(sr_mix.astype(np.int16), rate=h2.sampling_rate))

def ARPA(text, punctuation=r"!?,.;", EOS_Token=True):
    out = ''
    for word_ in text.split(" "):
        word=word_; end_chars = ''
        while any(elem in word for elem in punctuation) and len(word) > 1:
            if word[-1] in punctuation: end_chars = word[-1] + end_chars; word = word[:-1]
            else: break
        try:
            word_arpa = thisdict[word.upper()]
            word = "{" + str(word_arpa) + "}"
        except KeyError: pass
        out = (out + " " + word + end_chars).strip()
    if EOS_Token and out[-1] != ";": out += ";"
    return out

def get_hifigan(MODEL_ID, conf_name):
    hifigan_pretrained_model = 'hifimodel_' + conf_name
    if MODEL_ID == 1:
        os.system(f"wget 'https://github.com/johnpaulbin/tacotron2/releases/download/Main/Superres_Twilight_33000' -O {hifigan_pretrained_model}")
    elif MODEL_ID == "universal":
        os.system(f"wget 'https://github.com/johnpaulbin/tacotron2/releases/download/Main/g_02500000' -O {hifigan_pretrained_model}")
    else:
        gdown.download(d+MODEL_ID, hifigan_pretrained_model, quiet=False)

    if not os.path.exists(hifigan_pretrained_model):
        raise Exception("Falha ao baixar o modelo hifigan, tente outro!")

    conf = os.path.join("hifi-gan", conf_name + ".json")
    with open(conf) as f:
        json_config = json.loads(f.read())
    h = AttrDict(json_config)
    torch.manual_seed(h.seed)
    hifigan = Generator(h).to(torch.device("cuda"))
    state_dict_g = torch.load(hifigan_pretrained_model, map_location=torch.device("cuda"))
    hifigan.load_state_dict(state_dict_g["generator"])
    hifigan.eval()
    hifigan.remove_weight_norm()
    denoiser = Denoiser(hifigan, mode="normal")
    return hifigan, h, denoiser

def get_Tactron2(MODEL_PATH):
    # Carregar Tacotron2 e Config
    hparams = create_hparams()
    hparams.sampling_rate = 22050
    hparams.max_decoder_steps = 3000  # Max Duration
    hparams.gate_threshold = 0.25     # Model must be 25% sure the clip is over before ending generation
    model = Tacotron2(hparams)
    state_dict = torch.load(MODEL_PATH)['state_dict']
    model.load_state_dict(state_dict)
    _ = model.cuda().eval().half()
    return model, hparams
