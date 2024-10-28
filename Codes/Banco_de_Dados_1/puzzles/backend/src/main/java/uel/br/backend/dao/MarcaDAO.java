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
import uel.br.backend.model.Marca;

public class MarcaDAO implements DAO<Marca, String> {
    private final Connection connection;
    private final TableMapper<Marca> mapper;

    private static final String CREATE_QUERY = "INSERT INTO loja.marca(nome) "
            + "VALUES(?);";

    private static final String ALL_QUERY = "SELECT * " +
            "FROM loja.marca; ";

    private static final String READ_QUERY = "SELECT * " +
            "FROM loja.marca " +
            "WHERE nome = ?;";

    private static final String UPDATE_QUERY = "UPDATE loja.marca " +
            "SET nome = ? " +
            "WHERE nome = ?;";

    private static final String DELETE_QUERY = "DELETE FROM loja.marca " +
            "WHERE nome = ?;";

    public MarcaDAO(Connection connection) {
        this.connection = connection;
        this.mapper = new TableMapper<>(Marca.class);
    }

    @Override
    public String create(Marca marca) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(CREATE_QUERY)) {
            statement.setString(1, marca.getNome());
            statement.executeUpdate();
            return marca.getNome().toString();
        } catch (SQLException ex) {
            Logger.getLogger(MarcaDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().contains("not-null")) {
                throw new SQLException("Erro ao inserir marca: campo está em branco.");
            } else {
                throw new SQLException("Erro ao inserir marca.");
            }
        }
    }

    @Override
    public Marca read(String nome) throws SQLException {

        try (PreparedStatement statement = connection.prepareStatement(READ_QUERY)) {
            statement.setString(1, nome);
            try (ResultSet result = statement.executeQuery()) {
                if (result.next()) {
                    return this.mapper.mapRow(result, 1);
                } else {
                    throw new SQLException("Erro ao selecionar marca: não encontrado");
                }
            }
        } catch (SQLException ex) {
            Logger.getLogger(MarcaDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().equals("Erro ao selecionar marca: não encontrado")) {
                throw ex;
            } else {
                throw new SQLException("Erro ao selecionar marca.");
            }
        }

    }

    @Override
    public void update(String nome_antigo, Marca marca) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(UPDATE_QUERY)) {
            statement.setString(1, marca.getNome());
            statement.setString(2, nome_antigo);
            if (statement.executeUpdate() < 1) {
                throw new SQLException("Erro ao atualizar marca: não encontrado.");
            }
        } catch (SQLException ex) {
            Logger.getLogger(MarcaDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().equals("Erro ao atualizar marca: não encontrado.")) {
                throw ex;
            } else if (ex.getMessage().contains("not-null")) {
                throw new SQLException("Erro ao atualizar marca: um campo está nulo.");
            } else {
                throw new SQLException("Erro ao atualizar marca");
            }
        }
    }

    @Override
    public void delete(String nome) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(DELETE_QUERY)) {
            statement.setString(1, nome);
            if (statement.executeUpdate() < 1) {
                throw new SQLException("Erro ao excluir marca:  não encontrado.");
            }
        } catch (SQLException ex) {
            Logger.getLogger(MarcaDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().equals("Erro ao excluir marca: não encontrado.")) {
                throw ex;
            } else {
                throw new SQLException("Erro ao excluir marca");
            }
        }
    }

    @Override
    public List<Marca> all() throws SQLException {
        List<Marca> marcas = new ArrayList<>();

        try (PreparedStatement statement = connection.prepareStatement(ALL_QUERY);
                ResultSet result = statement.executeQuery()) {
            while (result.next()) {
                marcas.add(this.mapper.mapRow(result, 0));
            }
        } catch (SQLException ex) {
            Logger.getLogger(MarcaDAO.class.getName()).log(Level.SEVERE, "DAO", ex);
            throw new SQLException("Erro ao listar marcas");
        }

        return marcas;
    }
}
