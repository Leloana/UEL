package uel.br.backend.model;

import java.math.BigDecimal;

import jakarta.persistence.Entity;
import jakarta.persistence.Id;
import jakarta.persistence.IdClass;
import jakarta.persistence.Table;

@IdClass(ChaveCarrinhoPuzzle.class)
@Entity
@Table(name = "carrinho_contem_puzzle", schema = "loja")
public class CarrinhoContemPuzzle {
    @Id
    private Integer id_carrinho;
    @Id
    private String nome_puzzle;

    private Integer quantidade;
    private BigDecimal preco;

    public CarrinhoContemPuzzle() {
        this.quantidade = 0;
        this.preco = new BigDecimal(0);
        this.id_carrinho = 0;
        this.nome_puzzle = "";
    }

    public CarrinhoContemPuzzle(Integer id_carrinho, String nome_puzzle, Integer quantidade, BigDecimal preco) {
        this.quantidade = quantidade;
        this.preco = preco;
        this.id_carrinho = id_carrinho;
        this.nome_puzzle = nome_puzzle;
    }

    public void add() {
        this.quantidade += 1;
    }

    public void add(int quantidade) {
        this.quantidade += quantidade;
    }

    public void sub() {
        this.quantidade -= 1;
    }

    public void sub(int quantidade) {
        this.quantidade -= quantidade;
    }

    public Integer getId_carrinho() {
        return id_carrinho;
    }

    public void setId_carrinho(Integer id_carrinho) {
        this.id_carrinho = id_carrinho;
    }

    public String getNome_puzzle() {
        return nome_puzzle;
    }

    public void setNome_puzzle(String nome_puzzle) {
        this.nome_puzzle = nome_puzzle;
    }

    public Integer getQuantidade() {
        return quantidade;
    }

    public void setQuantidade(Integer quantidade) {
        this.quantidade = quantidade;
    }

    public BigDecimal getPreco() {
        return preco;
    }

    public void setPreco(BigDecimal preco) {
        this.preco = preco;
    }

}
