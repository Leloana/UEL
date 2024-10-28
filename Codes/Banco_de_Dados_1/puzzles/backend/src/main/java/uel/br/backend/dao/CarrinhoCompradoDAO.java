package uel.br.backend.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

import uel.br.backend.mapper.TableMapper;
import uel.br.backend.model.CarrinhoComprado;

public class CarrinhoCompradoDAO implements DAO<CarrinhoComprado, Integer> {
    private final Connection connection;
    private final TableMapper<CarrinhoComprado> mapper;

    private static final String CREATE_QUERY = "INSERT INTO loja.carrinho_comprado(id_carrinho,data_compra,id_cliente) "
            + "VALUES(?,?,?);";

    private static final String ALL_QUERY = "SELECT * " +
            "FROM loja.carrinho_comprado";

    private static final String READ_QUERY = "SELECT * " +
            "FROM loja.carrinho_comprado " +
            "WHERE id_carrinho = ?;";

    private static final String DELETE_QUERY = "DELETE FROM loja.carrinho_comprado " +
            "WHERE id_carrinho = ?;";

    public CarrinhoCompradoDAO(Connection connection) {
        this.connection = connection;
        this.mapper = new TableMapper<>(CarrinhoComprado.class);
    }

    @Override
    public Integer create(CarrinhoComprado carrinho_comprado) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(CREATE_QUERY)) {
            statement.setInt(1, carrinho_comprado.getId_carrinho());
            statement.setDate(2, carrinho_comprado.getData_compra());
            statement.setInt(3, carrinho_comprado.getId_cliente());
            statement.executeUpdate();
            return carrinho_comprado.getId_carrinho();
        } catch (SQLException ex) {
            Logger.getLogger(CarrinhoCompradoDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().contains("not-null")) {
                throw new SQLException("Erro ao inserir carrinho_comprado: campo está em branco.");
            } else {
                throw new SQLException("Erro ao inserir carrinho_comprado.");
            }
        }
    }

    @Override
    public CarrinhoComprado read(Integer id) throws SQLException {

        try (PreparedStatement statement = connection.prepareStatement(READ_QUERY)) {
            statement.setInt(1, id);
            try (ResultSet result = statement.executeQuery()) {
                if (result.next()) {
                    return this.mapper.mapRow(result, 1);
                } else {
                    throw new SQLException("Erro ao selecionar carrinho_comprado: não encontrado");
                }
            }
        } catch (SQLException ex) {
            Logger.getLogger(CarrinhoCompradoDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().equals("Erro ao selecionar carrinho_comprado: não encontrado")) {
                throw ex;
            } else {
                throw new SQLException("Erro ao selecionar carrinho_comprado.");
            }
        }

    }

    @Override
    public void update(Integer id, CarrinhoComprado carrinho_comprado) throws SQLException {
        throw new SQLException("Erro ao atualizar carrinho_comprado: carrinho_comprado não permite atualização.");
    }

    @Override
    public void delete(Integer id) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(DELETE_QUERY)) {
            statement.setInt(1, id);
            if (statement.executeUpdate() < 1) {
                throw new SQLException("Erro ao excluir carrinho_comprado:  não encontrado.");
            }
        } catch (SQLException ex) {
            Logger.getLogger(CarrinhoCompradoDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().equals("Erro ao excluir carrinho comprado: não encontrado.")) {
                throw ex;
            } else {
                throw new SQLException("Erro ao excluir carrinho comprado");
            }
        }
    }

    @Override
    public List<CarrinhoComprado> all() throws SQLException {
        List<CarrinhoComprado> carrinho_comprados = new ArrayList<>();

        try (PreparedStatement statement = connection.prepareStatement(ALL_QUERY);
                ResultSet result = statement.executeQuery()) {
            while (result.next()) {
                carrinho_comprados.add(this.mapper.mapRow(result, 0));
            }
        } catch (SQLException ex) {
            Logger.getLogger(CarrinhoCompradoDAO.class.getName()).log(Level.SEVERE, "DAO", ex);
            throw new SQLException("Erro ao listar carrinhos comprados");
        }

        return carrinho_comprados;
    }
}
