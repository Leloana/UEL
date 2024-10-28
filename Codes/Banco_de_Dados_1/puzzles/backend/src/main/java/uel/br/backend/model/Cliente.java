package uel.br.backend.model;

import java.io.Serializable;
import java.sql.Date;

import jakarta.persistence.Entity;
import jakarta.persistence.Id;
import jakarta.persistence.Table;
import uel.br.backend.annotation.Password;

@Entity
@Table(name = "cliente", schema = "loja")
public class Cliente implements Serializable {
    @Id
    private Integer id;
    private Date data_criacao;
    private String login;

    @Password
    private String senha;
    private Integer id_carrinho_atual;

    public Cliente() {
        this.id = 0;
        this.data_criacao = new Date(0);
        this.login = "";
        this.senha = "";
        this.id_carrinho_atual = 0;
    }

    public Cliente(int id, Date data_criacao, String login, String senha, int id_carrinho) {
        this.id = id;
        this.data_criacao = data_criacao;
        this.login = login;
        this.senha = senha;
        this.id_carrinho_atual = id_carrinho;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public Date getData_criacao() {
        return data_criacao;
    }

    public void setData_criacao(Date data_criacao) {
        this.data_criacao = data_criacao;
    }

    public String getLogin() {
        return login;
    }

    public void setLogin(String login) {
        this.login = login;
    }

    public String getSenha() {
        return senha;
    }

    public void setSenha(String senha) {
        this.senha = senha;
    }

    public Integer getId_carrinho_atual() {
        return id_carrinho_atual;
    }

    public void setId_carrinho_atual(Integer id_carrinho_atual) {
        this.id_carrinho_atual = id_carrinho_atual;
    }

}
