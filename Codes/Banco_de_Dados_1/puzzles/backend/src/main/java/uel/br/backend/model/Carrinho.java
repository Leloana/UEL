package uel.br.backend.model;

import java.io.Serializable;

import jakarta.persistence.Entity;
import jakarta.persistence.Id;
import jakarta.persistence.Table;

@Entity
@Table(name = "carrinho", schema = "loja")
public class Carrinho implements Serializable {
    @Id
    protected Integer id;

    public Carrinho() {
        this.id = 0;
    }

    public Carrinho(int id) {
        this.id = id;
    }

    public Integer getId() {
        return this.id;
    }

    public void setId(int id) {
        this.id = id;
    }
}
