package uel.br.backend.model;

import jakarta.persistence.Entity;
import jakarta.persistence.Id;
import jakarta.persistence.Table;

@Entity
@Table(name = "piraminx", schema = "loja")
public class Piraminx {
    @Id
    protected String nome_puzzle;

    public Piraminx() {
        this.nome_puzzle = "";
    }

    public Piraminx(String nome_puzzle) {
        this.nome_puzzle = nome_puzzle;
    }

    public String getNome_puzzle() {
        return nome_puzzle;
    }

    public void setNome_puzzle(String nome_puzzle) {
        this.nome_puzzle = nome_puzzle;
    }
}
