package uel.br.backend.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

import uel.br.backend.mapper.TableMapper;
import uel.br.backend.model.Carrinho;

public class CarrinhoDAO implements DAO<Carrinho, Integer> {

    private final Connection connection;
    private final TableMapper<Carrinho> mapper;

    private static final String CREATE_QUERY = "INSERT INTO loja.carrinho "
            + "DEFAULT VALUES;";

    private static final String ALL_QUERY = "SELECT * " +
            "FROM loja.carrinho " +
            "ORDER BY id;";

    private static final String READ_QUERY = "SELECT * " +
            "FROM loja.carrinho " +
            "WHERE id = ?;";

    private static final String DELETE_QUERY = "DELETE FROM loja.carrinho " +
            "WHERE id = ?;";

    public CarrinhoDAO(Connection connection) {
        this.connection = connection;
        this.mapper = new TableMapper<>(Carrinho.class);
    }

    @Override
    public Integer create(Carrinho carrinho) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(CREATE_QUERY, Statement.RETURN_GENERATED_KEYS)) {
            statement.executeUpdate();
            try (ResultSet generatedKeys = statement.getGeneratedKeys()) {
                if (generatedKeys.next()) {
                    return generatedKeys.getInt("id");
                } else {
                    throw new SQLException("Erro ao inserir carrinho.");
                }
            }
        } catch (SQLException ex) {
            Logger.getLogger(CarrinhoDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().contains("not-null")) {
                throw new SQLException("Erro ao inserir carrinho: campo está em branco.");
            } else {
                throw new SQLException("Erro ao inserir carrinho.");
            }
        }
    }

    @Override
    public Carrinho read(Integer id) throws SQLException {

        try (PreparedStatement statement = connection.prepareStatement(READ_QUERY)) {
            statement.setInt(1, id);
            try (ResultSet result = statement.executeQuery()) {
                if (result.next()) {
                    return this.mapper.mapRow(result, 1);
                } else {
                    throw new SQLException("Erro ao selecionar carrinho: não encontrado");
                }
            }
        } catch (SQLException ex) {
            Logger.getLogger(CarrinhoDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().equals("Erro ao selecionar carrinho: não encontrado")) {
                throw ex;
            } else {
                throw new SQLException("Erro ao selecionar carrinho.");
            }
        }

    }

    @Override
    public void update(Integer id, Carrinho carrinho) throws SQLException {
        throw new SQLException("Erro ao atualizar carrinho: carrinho não permite atualização.");
    }

    @Override
    public void delete(Integer id) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(DELETE_QUERY)) {
            statement.setInt(1, id);
            if (statement.executeUpdate() < 1) {
                throw new SQLException("Erro ao excluir carrinho:  não encontrado.");
            }
        } catch (SQLException ex) {
            Logger.getLogger(CarrinhoDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().equals("Erro ao excluir carrinho: não encontrado.")) {
                throw ex;
            } else {
                throw new SQLException("Erro ao excluir carrinho");
            }
        }
    }

    @Override
    public List<Carrinho> all() throws SQLException {
        List<Carrinho> carrinhos = new ArrayList<>();

        try (PreparedStatement statement = connection.prepareStatement(ALL_QUERY);
                ResultSet result = statement.executeQuery()) {
            while (result.next()) {
                carrinhos.add(this.mapper.mapRow(result, 0));
            }
        } catch (SQLException ex) {
            Logger.getLogger(CarrinhoDAO.class.getName()).log(Level.SEVERE, "DAO", ex);
            throw new SQLException("Erro ao listar carrinhos");
        }

        return carrinhos;
    }
}
