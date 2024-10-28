package uel.br.backend.model;

import jakarta.persistence.Entity;
import jakarta.persistence.Id;
import jakarta.persistence.Table;

@Entity
@Table(name = "clock", schema = "loja")
public class Clock {
    @Id
    protected String nome_puzzle;

    public Clock() {
        this.nome_puzzle = "";
    }

    public Clock(String nome_puzzle) {
        this.nome_puzzle = nome_puzzle;
    }

    public String getNome_puzzle() {
        return nome_puzzle;
    }

    public void setNome_puzzle(String nome_puzzle) {
        this.nome_puzzle = nome_puzzle;
    }
}