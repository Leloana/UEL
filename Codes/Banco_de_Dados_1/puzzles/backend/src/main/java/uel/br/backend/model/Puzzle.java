package uel.br.backend.model;

import java.math.BigDecimal;

import jakarta.persistence.Table;
import jakarta.persistence.Entity;
import jakarta.persistence.Id;

@Entity
@Table(name = "puzzle", schema = "loja")
public class Puzzle {
    @Id
    protected String nome;

    protected String tipo;
    protected BigDecimal preco;
    protected String nome_marca;

    public Puzzle() {
        this.nome = "";
        this.tipo = "";
        this.preco = new BigDecimal(0);
        this.nome_marca = "";
    }

    public Puzzle(String nome, String tipo, BigDecimal preco, int quantidade, String nome_marca) {
        this.nome = nome;
        this.tipo = tipo;
        this.preco = preco;
        this.nome_marca = nome_marca;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getTipo() {
        return tipo;
    }

    public void setTipo(String tipo) {
        this.tipo = tipo;
    }

    public BigDecimal getPreco() {
        return preco;
    }

    public void setPreco(BigDecimal preco) {
        this.preco = preco;
    }

    public String getNome_marca() {
        return nome_marca;
    }

    public void setNome_marca(String nome_marca) {
        this.nome_marca = nome_marca;
    }

}
