package uel.br.backend.model;

import java.sql.Date;
import jakarta.persistence.Entity;
import jakarta.persistence.Id;
import jakarta.persistence.Table;

@Entity
@Table(name = "carrinho_comprado", schema = "loja")
public class CarrinhoComprado {
    @Id
    private Integer id_carrinho;
    private Date data_compra;
    private Integer id_cliente;

    public CarrinhoComprado() {
        this.id_carrinho = 0;
        this.data_compra = new Date(0);
        this.id_cliente = 0;
    }

    public CarrinhoComprado(Integer id_carrinho, Date data_compra, Integer id_cliente) {
        this.id_carrinho = id_carrinho;
        this.data_compra = data_compra;
        this.id_cliente = id_cliente;
    }

    public Integer getId_carrinho() {
        return id_carrinho;
    }

    public void setId_carrinho(Integer id_carrinho) {
        this.id_carrinho = id_carrinho;
    }

    public Date getData_compra() {
        return data_compra;
    }

    public void setData_compra(Date data_compra) {
        this.data_compra = data_compra;
    }

    public Integer getId_cliente() {
        return id_cliente;
    }

    public void setId_cliente(Integer id_cliente) {
        this.id_cliente = id_cliente;
    }

}
