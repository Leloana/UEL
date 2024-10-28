package uel.br.backend.model;
import jakarta.persistence.Entity;
import jakarta.persistence.Id;
import jakarta.persistence.Table;

@Entity
@Table(name = "marca", schema = "loja")
public class Marca {
    @Id
    private String nome;

    public Marca() {
        this.nome = "";
    }

    public Marca(String nome) {
        this.nome = nome;
    }

    public String getNome() {
        return this.nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }
}
