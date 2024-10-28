package uel.br.backend.model;

import jakarta.persistence.Entity;
import jakarta.persistence.Id;
import jakarta.persistence.IdClass;
import jakarta.persistence.Table;

//PRECISA ARRUMAR(ADICIONAR CLASSE PARA CHAVE COMPOSTA)
@IdClass(ChaveImagem.class)
@Entity
@Table(name = "imagem", schema = "loja")
public class Imagem {
    @Id
    private String imagem;
    @Id
    private String nome_puzzle;

    public Imagem() {
        this.imagem = "";
        this.nome_puzzle = "";
    }

    public Imagem(String imagem, String nome_puzzle) {
        this.imagem = imagem;
        this.nome_puzzle = nome_puzzle;
    }

    public String getImagem() {
        return imagem;
    }

    public void setImagem(String imagem) {
        this.imagem = imagem;
    }

    public String getNome_puzzle() {
        return nome_puzzle;
    }

    public void setNome_puzzle(String nome_puzzle) {
        this.nome_puzzle = nome_puzzle;
    }

}
