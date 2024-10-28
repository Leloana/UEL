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
import uel.br.backend.model.CarrinhoAtual;

public class CarrinhoAtualDAO implements DAO<CarrinhoAtual, Integer> {
    private final Connection connection;
    private final TableMapper<CarrinhoAtual> mapper;

    private static final String CREATE_QUERY = "INSERT INTO loja.carrinho_atual(id_carrinho) "
            + "VALUES(?);";

    private static final String ALL_QUERY = "SELECT * " +
            "FROM loja.carrinho_atual" +
            "ORDER BY id_carrinho;";

    private static final String READ_QUERY = "SELECT * " +
            "FROM loja.carrinho_atual " +
            "WHERE id_carrinho = ?;";

    private static final String UPDATE_QUERY = "UPDATE loja.carrinho_atual " +
            "SET id_carrinho = ? " +
            "WHERE id_carrinho = ?;";

    private static final String DELETE_QUERY = "DELETE FROM loja.carrinho_atual " +
            "WHERE id_carrinho = ?;";

    public CarrinhoAtualDAO(Connection connection) {
        this.connection = connection;
        this.mapper = new TableMapper<>(CarrinhoAtual.class);
    }

    @Override
    public Integer create(CarrinhoAtual carrinho_atual) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(CREATE_QUERY)) {
            statement.setInt(1, carrinho_atual.getId_carrinho());
            statement.executeUpdate();
            return carrinho_atual.getId_carrinho();
        } catch (SQLException ex) {
            Logger.getLogger(CarrinhoAtualDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().contains("not-null")) {
                throw new SQLException("Erro ao inserir carrinho_atual: campo está em branco.");
            } else {
                throw new SQLException("Erro ao inserir carrinho_atual.");
            }
        }
    }

    @Override
    public CarrinhoAtual read(Integer id) throws SQLException {

        try (PreparedStatement statement = connection.prepareStatement(READ_QUERY)) {
            statement.setInt(1, id);
            try (ResultSet result = statement.executeQuery()) {
                if (result.next()) {
                    return this.mapper.mapRow(result, 1);
                } else {
                    throw new SQLException("Erro ao selecionar carrinho_atual: não encontrado");
                }
            }
        } catch (SQLException ex) {
            Logger.getLogger(CarrinhoAtualDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().equals("Erro ao selecionar carrinho_atual: não encontrado")) {
                throw ex;
            } else {
                throw new SQLException("Erro ao selecionar carrinho_atual.");
            }
        }

    }

    @Override
    public void update(Integer old_id, CarrinhoAtual carrinho_atual) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(UPDATE_QUERY)) {
            statement.setInt(1, carrinho_atual.getId_carrinho());
            statement.setInt(2, old_id);
            if (statement.executeUpdate() < 1) {
                throw new SQLException("Erro ao atualizar carrinho_atual: não encontrado.");
            }
        } catch (SQLException ex) {
            Logger.getLogger(PuzzleDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().equals("Erro ao atualizar carrinho_atual: não encontrado.")) {
                throw ex;
            } else if (ex.getMessage().contains("not-null")) {
                throw new SQLException("Erro ao atualizar carrinho_atual: um campo está nulo.");
            } else {
                throw new SQLException("Erro ao atualizar carrinho_atual");
            }
        }
    }

    @Override
    public void delete(Integer id) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(DELETE_QUERY)) {
            statement.setInt(1, id);
            if (statement.executeUpdate() < 1) {
                throw new SQLException("Erro ao excluir carrinho_atual:  não encontrado.");
            }
        } catch (SQLException ex) {
            Logger.getLogger(CarrinhoAtualDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().equals("Erro ao excluir carrinho_atual: não encontrado.")) {
                throw ex;
            } else {
                throw new SQLException("Erro ao excluir carrinho_atual");
            }
        }
    }

    @Override
    public List<CarrinhoAtual> all() throws SQLException {
        List<CarrinhoAtual> carrinho_atuals = new ArrayList<>();

        try (PreparedStatement statement = connection.prepareStatement(ALL_QUERY);
                ResultSet result = statement.executeQuery()) {
            while (result.next()) {
                carrinho_atuals.add(this.mapper.mapRow(result, 0));
            }
        } catch (SQLException ex) {
            Logger.getLogger(CarrinhoAtualDAO.class.getName()).log(Level.SEVERE, "DAO", ex);
            throw new SQLException("Erro ao listar carrinho_atuals");
        }

        return carrinho_atuals;
    }
}
