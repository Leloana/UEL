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
import uel.br.backend.model.Cubo3;

public class Cubo3DAO implements DAO<Cubo3, String> {
    private final Connection connection;
    private final TableMapper<Cubo3> mapper;

    private static final String CREATE_QUERY = "INSERT INTO loja.cubo3(nome_puzzle, com_adesivo) "
            + "VALUES(?,?);";

    private static final String ALL_QUERY = "SELECT * " +
            "FROM loja.cubo3";

    private static final String READ_QUERY = "SELECT * " +
            "FROM loja.cubo3 " +
            "WHERE nome_puzzle = ?;";

    private static final String UPDATE_QUERY = "UPDATE * loja.cubo3" +
            "SET nome_puzzle = ?, SET com_adesivo = ? " +
            "WHERE nome_puzzle = ?;";

    private static final String DELETE_QUERY = "DELETE FROM loja.cubo3 " +
            "WHERE nome_puzzle = ?;";

    public Cubo3DAO(Connection connection) {
        this.connection = connection;
        this.mapper = new TableMapper<>(Cubo3.class);
    }

    @Override
    public String create(Cubo3 cubo3) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(CREATE_QUERY)) {
            statement.setString(1, cubo3.getNome_puzzle());
            statement.setBoolean(2, cubo3.isCom_adesivo());
            statement.executeUpdate();
            return cubo3.getNome_puzzle();
        } catch (SQLException ex) {
            Logger.getLogger(Cubo3DAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().contains("not-null")) {
                throw new SQLException("Erro ao inserir cubo3: campo está em branco.");
            } else {
                throw new SQLException("Erro ao inserir cubo3.");
            }
        }
    }

    @Override
    public Cubo3 read(String id) throws SQLException {

        try (PreparedStatement statement = connection.prepareStatement(READ_QUERY)) {
            statement.setString(1, id);
            try (ResultSet result = statement.executeQuery()) {
                if (result.next()) {
                    return this.mapper.mapRow(result, 1);
                } else {
                    throw new SQLException("Erro ao selecionar cubo3: não encontrado");
                }
            }
        } catch (SQLException ex) {
            Logger.getLogger(Cubo3DAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().equals("Erro ao selecionar cubo3: não encontrado")) {
                throw ex;
            } else {
                throw new SQLException("Erro ao selecionar cubo3.");
            }
        }

    }

    @Override
    public void update(String id_antigo, Cubo3 cubo3) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(UPDATE_QUERY)) {
            statement.setString(1, cubo3.getNome_puzzle());
            statement.setString(2, id_antigo);
            if (statement.executeUpdate() < 1) {
                throw new SQLException("Erro ao atualizar cubo3: não encontrado.");
            }
        } catch (SQLException ex) {
            Logger.getLogger(PuzzleDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().equals("Erro ao atualizar cubo3: não encontrado.")) {
                throw ex;
            } else if (ex.getMessage().contains("not-null")) {
                throw new SQLException("Erro ao atualizar cubo3: um campo está nulo.");
            } else {
                throw new SQLException("Erro ao atualizar cubo3");
            }
        }
    }

    @Override
    public void delete(String id) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(DELETE_QUERY)) {
            statement.setString(1, id);
            if (statement.executeUpdate() < 1) {
                throw new SQLException("Erro ao excluir cubo3:  não encontrado.");
            }
        } catch (SQLException ex) {
            Logger.getLogger(Cubo3DAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().equals("Erro ao excluir cubo3: não encontrado.")) {
                throw ex;
            } else {
                throw new SQLException("Erro ao excluir cubo3");
            }
        }
    }

    @Override
    public List<Cubo3> all() throws SQLException {
        List<Cubo3> cubo3s = new ArrayList<>();

        try (PreparedStatement statement = connection.prepareStatement(ALL_QUERY);
                ResultSet result = statement.executeQuery()) {
            while (result.next()) {
                cubo3s.add(this.mapper.mapRow(result, 0));
            }
        } catch (SQLException ex) {
            Logger.getLogger(Cubo3DAO.class.getName()).log(Level.SEVERE, "DAO", ex);
            throw new SQLException("Erro ao listar cubo3s");
        }

        return cubo3s;
    }
}
