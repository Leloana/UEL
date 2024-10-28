package uel.br.backend.model;

import jakarta.persistence.Entity;
import jakarta.persistence.Id;
import jakarta.persistence.Table;

@Entity
@Table(name = "cubo4", schema = "loja")
public class Cubo4 {
    @Id
    private String nome_puzzle;
    private boolean com_adesivo;

    public Cubo4() {
        this.nome_puzzle = "";
        this.com_adesivo = false;
    }

    public Cubo4(String nome_puzzle, boolean com_adesivo) {
        this.nome_puzzle = nome_puzzle;
        this.com_adesivo = com_adesivo;
    }

    public String getNome_puzzle() {
        return nome_puzzle;
    }

    public void setNome_puzzle(String nome_puzzle) {
        this.nome_puzzle = nome_puzzle;
    }

    public boolean isCom_adesivo() {
        return com_adesivo;
    }

    public void setCom_adesivo(boolean com_adesivo) {
        this.com_adesivo = com_adesivo;
    }
}
