import os
import torch
import torch.optim as optim
from torch.utils.data import DataLoader
from torchvision import transforms
from torch.cuda.amp import GradScaler, autocast  # Para FP16
import logging

# Configurar logging
logging.basicConfig(filename='training.log', level=logging.INFO)

def train(output_directory, checkpoint_path, warm_start, n_gpus, rank, hparams, Model, Dataset):
    # Configuração do dispositivo
    device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
    if hparams.distributed_run:
        torch.distributed.init_process_group(backend='nccl', rank=rank, world_size=n_gpus)
    
    # Inicialize o modelo
    model = Model  # Substitua pelo seu modelo
    model.to(device)
    
    # Configuração do FP16 se necessário
    scaler = GradScaler() if hparams.fp16_run else None

    # Definição da função de perda e otimizador
    criterion = torch.nn.CrossEntropyLoss()  # Substitua pela sua função de perda
    optimizer = optim.Adam(model.parameters(), lr=hparams.A_)  # Ajuste conforme necessário
    
    # Carregamento dos dados
    train_dataset = Dataset
    train_loader = DataLoader(train_dataset, batch_size=hparams.batch_size, shuffle=True, num_workers=4)

    # Se houver um checkpoint, carregar o modelo
    if warm_start and os.path.isfile(checkpoint_path):
        checkpoint = torch.load(checkpoint_path)
        model.load_state_dict(checkpoint['model_state_dict'])
        optimizer.load_state_dict(checkpoint['optimizer_state_dict'])
        start_epoch = checkpoint['epoch']
        logging.info(f"Resuming from epoch {start_epoch}")
    else:
        start_epoch = 0

    # Loop de treinamento
    for epoch in range(start_epoch, hparams.epochs):
        model.train()
        running_loss = 0.0
        
        for i, (inputs, labels) in enumerate(train_loader):
            inputs, labels = inputs.to(device), labels.to(device)
            
            optimizer.zero_grad()
            
            with autocast() if hparams.fp16_run else torch.no_grad():
                outputs = model(inputs)
                loss = criterion(outputs, labels)
            
            if hparams.fp16_run:
                scaler.scale(loss).backward()
                scaler.step(optimizer)
                scaler.update()
            else:
                loss.backward()
                optimizer.step()
            
            running_loss += loss.item()
            
            if i % 10 == 0:  # Log a summary every 10 batches
                logging.info(f"Epoch [{epoch + 1}/{hparams.epochs}], Batch [{i + 1}/{len(train_loader)}], Loss: {loss.item()}")

        # Salvar checkpoint
        if (epoch + 1) % 10 == 0:  # Salvar checkpoints a cada 10 épocas
            torch.save({
                'epoch': epoch + 1,
                'model_state_dict': model.state_dict(),
                'optimizer_state_dict': optimizer.state_dict(),
                'loss': running_loss / len(train_loader),
            }, checkpoint_path)

        logging.info(f"Epoch [{epoch + 1}/{hparams.epochs}], Loss: {running_loss / len(train_loader)}")

    # Salvar o modelo final
    torch.save({
        'epoch': hparams.epochs,
        'model_state_dict': model.state_dict(),
        'optimizer_state_dict': optimizer.state_dict(),
    }, checkpoint_path)
    output_directory = ""
    logging.info("Treinamento concluído")

# Inicialize hparams e outros parâmetros
hparams = HParams()

# Começar o treinamento
train("\programs\output", log_directory, checkpoint_path,
      warm_start, n_gpus, rank, group_name, hparams, log_directory2)
