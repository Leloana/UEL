package br.uel.Prova1ConsumidorMarceloFerreira;

import jakarta.persistence.*;

import java.io.Serializable;
@Entity
@Table (name ="item_cardapio")
public class ItemCardapio implements Serializable {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;
    private String nome;
    private String descricao;
    private double preco;
    @ManyToOne
    @JoinColumn(name="id_restaurante", nullable=false)
    private Restaurante restaurante;

    public int getId() {return id;}
    public void setId(int id) {this.id = id;}
    public String getNome() {return nome;}
    public void setNome(String nome) {this.nome = nome;}
    public String getDescricao() {return descricao;}
    public void setDescricao(String descricao) {this.descricao = descricao;}
    public double getPreco() {return preco;}
    public void setPreco(double preco) {this.preco = preco;}
    public Restaurante getRestaurante() {return restaurante;}
    public void setRestaurante(Restaurante restaurante) {this.restaurante = restaurante;}
}
