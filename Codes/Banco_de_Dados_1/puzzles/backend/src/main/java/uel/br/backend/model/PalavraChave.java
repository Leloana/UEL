package uel.br.backend.model;

import jakarta.persistence.Entity;
import jakarta.persistence.Id;
import jakarta.persistence.IdClass;
import jakarta.persistence.Table;

@IdClass(ChavePalavraChave.class)
@Entity
@Table(name = "palavra_chave", schema = "loja")
public class PalavraChave {
    @Id
    private String palavra;
    @Id
    private String nome_puzzle;

    public PalavraChave() {
        this.palavra = "";
        this.nome_puzzle = "";
    }

    public PalavraChave(String palavra, String nome_puzzle) {
        this.palavra = palavra;
        this.nome_puzzle = nome_puzzle;
    }

    public String getPalavra() {
        return palavra;
    }

    public void setPalavra(String palavra) {
        this.palavra = palavra;
    }

    public String getNome_puzzle() {
        return nome_puzzle;
    }

    public void setNome_puzzle(String nome_puzzle) {
        this.nome_puzzle = nome_puzzle;
    }

}
