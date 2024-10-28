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
import uel.br.backend.model.Cubo2;

public class Cubo2DAO implements DAO<Cubo2, String> {
    private final Connection connection;
    private final TableMapper<Cubo2> mapper;

    private static final String CREATE_QUERY = "INSERT INTO loja.cubo2(nome_puzzle, com_adesivo) "
            + "VALUES(?,?);";

    private static final String ALL_QUERY = "SELECT * " +
            "FROM loja.cubo2";

    private static final String READ_QUERY = "SELECT * " +
            "FROM loja.cubo2 " +
            "WHERE nome_puzzle = ?;";

    private static final String UPDATE_QUERY = "UPDATE * loja.cubo2" +
            "SET nome_puzzle = ?, SET com_adesivo = ? " +
            "WHERE nome_puzzle = ?;";

    private static final String DELETE_QUERY = "DELETE FROM loja.cubo2 " +
            "WHERE nome_puzzle = ?;";

    public Cubo2DAO(Connection connection) {
        this.connection = connection;
        this.mapper = new TableMapper<>(Cubo2.class);
    }

    @Override
    public String create(Cubo2 cubo2) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(CREATE_QUERY)) {
            statement.setString(1, cubo2.getNome_puzzle());
            statement.setBoolean(2, cubo2.isCom_adesivo());
            statement.executeUpdate();
            return cubo2.getNome_puzzle();
        } catch (SQLException ex) {
            Logger.getLogger(Cubo2DAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().contains("not-null")) {
                throw new SQLException("Erro ao inserir cubo2: campo está em branco.");
            } else {
                throw new SQLException("Erro ao inserir cubo2.");
            }
        }
    }

    @Override
    public Cubo2 read(String id) throws SQLException {

        try (PreparedStatement statement = connection.prepareStatement(READ_QUERY)) {
            statement.setString(1, id);
            try (ResultSet result = statement.executeQuery()) {
                if (result.next()) {
                    return this.mapper.mapRow(result, 1);
                } else {
                    throw new SQLException("Erro ao selecionar cubo2: não encontrado");
                }
            }
        } catch (SQLException ex) {
            Logger.getLogger(Cubo2DAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().equals("Erro ao selecionar cubo2: não encontrado")) {
                throw ex;
            } else {
                throw new SQLException("Erro ao selecionar cubo2.");
            }
        }

    }

    @Override
    public void update(String id_antigo, Cubo2 cubo2) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(UPDATE_QUERY)) {
            statement.setString(1, cubo2.getNome_puzzle());
            statement.setString(2, id_antigo);
            if (statement.executeUpdate() < 1) {
                throw new SQLException("Erro ao atualizar cubo2: não encontrado.");
            }
        } catch (SQLException ex) {
            Logger.getLogger(PuzzleDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().equals("Erro ao atualizar cubo2: não encontrado.")) {
                throw ex;
            } else if (ex.getMessage().contains("not-null")) {
                throw new SQLException("Erro ao atualizar cubo2: um campo está nulo.");
            } else {
                throw new SQLException("Erro ao atualizar cubo2");
            }
        }
    }

    @Override
    public void delete(String id) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(DELETE_QUERY)) {
            statement.setString(1, id);
            if (statement.executeUpdate() < 1) {
                throw new SQLException("Erro ao excluir cubo2:  não encontrado.");
            }
        } catch (SQLException ex) {
            Logger.getLogger(Cubo2DAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().equals("Erro ao excluir cubo2: não encontrado.")) {
                throw ex;
            } else {
                throw new SQLException("Erro ao excluir cubo2");
            }
        }
    }

    @Override
    public List<Cubo2> all() throws SQLException {
        List<Cubo2> cubo2s = new ArrayList<>();

        try (PreparedStatement statement = connection.prepareStatement(ALL_QUERY);
                ResultSet result = statement.executeQuery()) {
            while (result.next()) {
                cubo2s.add(this.mapper.mapRow(result, 0));
            }
        } catch (SQLException ex) {
            Logger.getLogger(Cubo2DAO.class.getName()).log(Level.SEVERE, "DAO", ex);
            throw new SQLException("Erro ao listar cubo2s");
        }

        return cubo2s;
    }
}
