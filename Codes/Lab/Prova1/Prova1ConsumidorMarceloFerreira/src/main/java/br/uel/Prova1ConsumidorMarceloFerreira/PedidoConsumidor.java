package br.uel.Prova1ConsumidorMarceloFerreira;

import java.io.Serializable;
public class PedidoConsumidor implements Serializable {
    private int id;
    private ItemCardapio item;
    private int quantidade;

    public int getId() {return id;}
    public void setId(int id) {this.id = id;}
    public int getQuantidade() {return quantidade;}
    public void setQuantidade(int quantidade) {this.quantidade = quantidade;}
    public ItemCardapio getItem() {return item;}
    public void setItem(ItemCardapio item) {this.item = item;}
}
