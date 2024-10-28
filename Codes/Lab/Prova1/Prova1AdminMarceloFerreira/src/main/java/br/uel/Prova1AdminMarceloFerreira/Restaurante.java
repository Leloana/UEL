package br.uel.Prova1AdminMarceloFerreira;


import jakarta.persistence.*;
import jakarta.validation.constraints.NotBlank;

import java.util.ArrayList;
import java.util.List;


@Entity
@Table (name ="restaurante")
public class Restaurante {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;
    @NotBlank(message = "O nome é obrigatório")
    private String nome;

    @OneToMany(mappedBy="restaurante", cascade = CascadeType.ALL, orphanRemoval = true)
    private List<ItemCardapio> itensCardapio;
    public int getId() {return id;}
    public void setId(int id) {this.id = id;}
    public String getNome() {return nome;}
    public void setNome(String nome) {this.nome = nome;}
    public List<ItemCardapio> getItensCardapio() {return itensCardapio;}
    public void setItensCardapio(List<ItemCardapio> itemCardapio) {this.itensCardapio = itemCardapio;}
}