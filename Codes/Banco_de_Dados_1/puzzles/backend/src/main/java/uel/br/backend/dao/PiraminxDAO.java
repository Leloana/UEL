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
import uel.br.backend.model.Piraminx;

public class PiraminxDAO implements DAO<Piraminx, String> {

    private final Connection connection;
    private final TableMapper<Piraminx> mapper;

    private static final String CREATE_QUERY = "INSERT INTO loja.piraminx(nome_puzzle) "
            + "VALUES(?);";

    private static final String ALL_QUERY = "SELECT * " +
            "FROM loja.piraminx;";

    private static final String READ_QUERY = "SELECT * " +
            "FROM loja.piraminx " +
            "WHERE nome_puzzle = ?;";

    private static final String UPDATE_QUERY = "UPDATE loja.piraminx " +
            "SET nome_puzzle = ? " +
            "WHERE nome_puzzle = ?;";

    private static final String DELETE_QUERY = "DELETE FROM loja.piraminx " +
            "WHERE nome_puzzle = ?;";

    public PiraminxDAO(Connection connection) {
        this.connection = connection;
        this.mapper = new TableMapper<>(Piraminx.class);
    }

    @Override
    public String create(Piraminx piraminx) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(CREATE_QUERY)) {
            statement.setString(1, piraminx.getNome_puzzle());
            statement.executeUpdate();
            return piraminx.getNome_puzzle();
        } catch (SQLException ex) {
            Logger.getLogger(PiraminxDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().contains("not-null")) {
                throw new SQLException("Erro ao inserir piraminx: campo está em branco.");
            } else {
                throw new SQLException("Erro ao inserir piraminx.");
            }
        }
    }

    @Override
    public Piraminx read(String nome) throws SQLException {

        try (PreparedStatement statement = connection.prepareStatement(READ_QUERY)) {
            statement.setString(1, nome);
            try (ResultSet result = statement.executeQuery()) {
                if (result.next()) {
                    return this.mapper.mapRow(result, 1);
                } else {
                    throw new SQLException("Erro ao selecionar piraminx: não encontrado");
                }
            }
        } catch (SQLException ex) {
            Logger.getLogger(PiraminxDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().equals("Erro ao selecionar piraminx: não encontrado")) {
                throw ex;
            } else {
                throw new SQLException("Erro ao selecionar piraminx.");
            }
        }

    }

    @Override
    public void update(String nome, Piraminx piraminx) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(UPDATE_QUERY)) {
            statement.setString(1, piraminx.getNome_puzzle());
            statement.setString(2, nome);
            if (statement.executeUpdate() < 1) {
                throw new SQLException("Erro ao atualizar piraminx: não encontrado.");
            }
        } catch (SQLException ex) {
            Logger.getLogger(PiraminxDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().equals("Erro ao atualizar piraminx: não encontrado.")) {
                throw ex;
            } else if (ex.getMessage().contains("not-null")) {
                throw new SQLException("Erro ao atualizar piraminx: um campo está nulo.");
            } else {
                throw new SQLException("Erro ao atualizar piraminx");
            }
        }
    }

    @Override
    public void delete(String nome) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(DELETE_QUERY)) {
            statement.setString(1, nome);
            if (statement.executeUpdate() < 1) {
                throw new SQLException("Erro ao excluir piraminx:  não encontrado.");
            }
        } catch (SQLException ex) {
            Logger.getLogger(PiraminxDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().equals("Erro ao excluir piraminx: não encontrado.")) {
                throw ex;
            } else {
                throw new SQLException("Erro ao excluir piraminx");
            }
        }
    }

    @Override
    public List<Piraminx> all() throws SQLException {
        List<Piraminx> puzzles = new ArrayList<>();

        try (PreparedStatement statement = connection.prepareStatement(ALL_QUERY);
                ResultSet result = statement.executeQuery()) {
            while (result.next()) {
                puzzles.add(this.mapper.mapRow(result, 0));
            }
        } catch (SQLException ex) {
            Logger.getLogger(PiraminxDAO.class.getName()).log(Level.SEVERE, "DAO", ex);
            throw new SQLException("Erro ao listar puzzles");
        }

        return puzzles;
    }

}
