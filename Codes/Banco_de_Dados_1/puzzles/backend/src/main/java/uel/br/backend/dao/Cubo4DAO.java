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
import uel.br.backend.model.Cubo4;

public class Cubo4DAO implements DAO<Cubo4, String> {
    private final Connection connection;
    private final TableMapper<Cubo4> mapper;

    private static final String CREATE_QUERY = "INSERT INTO loja.cubo4(nome_puzzle, com_adesivo) "
            + "VALUES(?,?);";

    private static final String ALL_QUERY = "SELECT * " +
            "FROM loja.cubo4";

    private static final String READ_QUERY = "SELECT * " +
            "FROM loja.cubo4 " +
            "WHERE nome_puzzle = ?;";

    private static final String UPDATE_QUERY = "UPDATE * loja.cubo4" +
            "SET nome_puzzle = ?, SET com_adesivo = ? " +
            "WHERE nome_puzzle = ?;";

    private static final String DELETE_QUERY = "DELETE FROM loja.cubo4 " +
            "WHERE nome_puzzle = ?;";

    public Cubo4DAO(Connection connection) {
        this.connection = connection;
        this.mapper = new TableMapper<>(Cubo4.class);
    }

    @Override
    public String create(Cubo4 cubo4) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(CREATE_QUERY)) {
            statement.setString(1, cubo4.getNome_puzzle());
            statement.setBoolean(2, cubo4.isCom_adesivo());
            statement.executeUpdate();
            return cubo4.getNome_puzzle();
        } catch (SQLException ex) {
            Logger.getLogger(Cubo4DAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().contains("not-null")) {
                throw new SQLException("Erro ao inserir cubo4: campo está em branco.");
            } else {
                throw new SQLException("Erro ao inserir cubo4.");
            }
        }
    }

    @Override
    public Cubo4 read(String id) throws SQLException {

        try (PreparedStatement statement = connection.prepareStatement(READ_QUERY)) {
            statement.setString(1, id);
            try (ResultSet result = statement.executeQuery()) {
                if (result.next()) {
                    return this.mapper.mapRow(result, 1);
                } else {
                    throw new SQLException("Erro ao selecionar cubo4: não encontrado");
                }
            }
        } catch (SQLException ex) {
            Logger.getLogger(Cubo4DAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().equals("Erro ao selecionar cubo4: não encontrado")) {
                throw ex;
            } else {
                throw new SQLException("Erro ao selecionar cubo4.");
            }
        }

    }

    @Override
    public void update(String id_antigo, Cubo4 cubo4) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(UPDATE_QUERY)) {
            statement.setString(1, cubo4.getNome_puzzle());
            statement.setString(2, id_antigo);
            if (statement.executeUpdate() < 1) {
                throw new SQLException("Erro ao atualizar cubo4: não encontrado.");
            }
        } catch (SQLException ex) {
            Logger.getLogger(PuzzleDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().equals("Erro ao atualizar cubo4: não encontrado.")) {
                throw ex;
            } else if (ex.getMessage().contains("not-null")) {
                throw new SQLException("Erro ao atualizar cubo4: um campo está nulo.");
            } else {
                throw new SQLException("Erro ao atualizar cubo4");
            }
        }
    }

    @Override
    public void delete(String id) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(DELETE_QUERY)) {
            statement.setString(1, id);
            if (statement.executeUpdate() < 1) {
                throw new SQLException("Erro ao excluir cubo4:  não encontrado.");
            }
        } catch (SQLException ex) {
            Logger.getLogger(Cubo4DAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().equals("Erro ao excluir cubo4: não encontrado.")) {
                throw ex;
            } else {
                throw new SQLException("Erro ao excluir cubo4");
            }
        }
    }

    @Override
    public List<Cubo4> all() throws SQLException {
        List<Cubo4> cubo4s = new ArrayList<>();

        try (PreparedStatement statement = connection.prepareStatement(ALL_QUERY);
                ResultSet result = statement.executeQuery()) {
            while (result.next()) {
                cubo4s.add(this.mapper.mapRow(result, 0));
            }
        } catch (SQLException ex) {
            Logger.getLogger(Cubo4DAO.class.getName()).log(Level.SEVERE, "DAO", ex);
            throw new SQLException("Erro ao listar cubo4s");
        }

        return cubo4s;
    }
}
