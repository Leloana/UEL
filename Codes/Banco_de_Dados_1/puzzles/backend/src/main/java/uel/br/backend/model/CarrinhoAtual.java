package uel.br.backend.model;

import jakarta.persistence.Entity;
import jakarta.persistence.Id;
import jakarta.persistence.Table;

@Entity
@Table(name = "carrinho_atual", schema = "loja")
public class CarrinhoAtual {
    @Id
    private Integer id_carrinho;

    public CarrinhoAtual() {
        this.id_carrinho = 0;
    }

    public CarrinhoAtual(Integer id_carrinho) {
        this.id_carrinho = id_carrinho;
    }

    public Integer getId_carrinho() {
        return id_carrinho;
    }

    public void setId_carrinho(Integer id_carrinho) {
        this.id_carrinho = id_carrinho;
    }

}
