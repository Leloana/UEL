package uel.br.backend.dao;

import java.sql.SQLException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

import uel.br.backend.mapper.TableMapper;
import uel.br.backend.model.Clock;

public class ClockDAO implements DAO<Clock, String> {

    private final Connection connection;
    private final TableMapper<Clock> mapper;

    private static final String CREATE_QUERY = "INSERT INTO loja.clock(nome_puzzle) "
            + "VALUES(?);";

    private static final String ALL_QUERY = "SELECT * " +
            "FROM loja.clock;";

    private static final String READ_QUERY = "SELECT * " +
            "FROM loja.clock " +
            "WHERE nome_puzzle = ?;";

    private static final String UPDATE_QUERY = "UPDATE loja.clock " +
            "SET nome_puzzle = ? " +
            "WHERE nome_puzzle = ?;";

    private static final String DELETE_QUERY = "DELETE FROM loja.clock " +
            "WHERE nome_puzzle = ?;";

    public ClockDAO(Connection connection) {
        this.connection = connection;
        this.mapper = new TableMapper<>(Clock.class);
    }

    @Override
    public String create(Clock clock) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(CREATE_QUERY)) {
            statement.setString(1, clock.getNome_puzzle());
            statement.executeUpdate();
            return clock.getNome_puzzle();
        } catch (SQLException ex) {
            Logger.getLogger(ClockDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().contains("not-null")) {
                throw new SQLException("Erro ao inserir clock: campo está em branco.");
            } else {
                throw new SQLException("Erro ao inserir clock.");
            }
        }
    }

    @Override
    public Clock read(String nome) throws SQLException {

        try (PreparedStatement statement = connection.prepareStatement(READ_QUERY)) {
            statement.setString(1, nome);
            try (ResultSet result = statement.executeQuery()) {
                if (result.next()) {
                    return this.mapper.mapRow(result, 1);
                } else {
                    throw new SQLException("Erro ao selecionar clock: não encontrado");
                }
            }
        } catch (SQLException ex) {
            Logger.getLogger(ClockDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().equals("Erro ao selecionar clock: não encontrado")) {
                throw ex;
            } else {
                throw new SQLException("Erro ao selecionar clock.");
            }
        }

    }

    @Override
    public void update(String nome, Clock clock) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(UPDATE_QUERY)) {
            statement.setString(1, clock.getNome_puzzle());
            statement.setString(2, nome);
            if (statement.executeUpdate() < 1) {
                throw new SQLException("Erro ao atualizar clock: não encontrado.");
            }
        } catch (SQLException ex) {
            Logger.getLogger(ClockDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().equals("Erro ao atualizar clock: não encontrado.")) {
                throw ex;
            } else if (ex.getMessage().contains("not-null")) {
                throw new SQLException("Erro ao atualizar clock: um campo está nulo.");
            } else {
                throw new SQLException("Erro ao atualizar clock");
            }
        }
    }

    @Override
    public void delete(String nome) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(DELETE_QUERY)) {
            statement.setString(1, nome);
            if (statement.executeUpdate() < 1) {
                throw new SQLException("Erro ao excluir clock:  não encontrado.");
            }
        } catch (SQLException ex) {
            Logger.getLogger(ClockDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().equals("Erro ao excluir clock: não encontrado.")) {
                throw ex;
            } else {
                throw new SQLException("Erro ao excluir clock");
            }
        }
    }

    @Override
    public List<Clock> all() throws SQLException {
        List<Clock> puzzles = new ArrayList<>();

        try (PreparedStatement statement = connection.prepareStatement(ALL_QUERY);
                ResultSet result = statement.executeQuery()) {
            while (result.next()) {
                puzzles.add(this.mapper.mapRow(result, 0));
            }
        } catch (SQLException ex) {
            Logger.getLogger(ClockDAO.class.getName()).log(Level.SEVERE, "DAO", ex);
            throw new SQLException("Erro ao listar puzzles");
        }

        return puzzles;
    }

}
