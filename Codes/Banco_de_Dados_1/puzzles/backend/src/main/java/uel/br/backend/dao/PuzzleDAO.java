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
import uel.br.backend.model.Puzzle;

public class PuzzleDAO implements DAO<Puzzle, String> {

    private final Connection connection;
    private final TableMapper<Puzzle> mapper;

    private static final String CREATE_QUERY = "INSERT INTO loja.puzzle(nome, tipo, preco, nome_marca) "
            + "VALUES(?, ?, ?, ?);";

    private static final String ALL_QUERY = "SELECT * " +
            "FROM loja.puzzle; ";

    private static final String READ_QUERY = "SELECT * " +
            "FROM loja.puzzle " +
            "WHERE nome = ?;";

    private static final String UPDATE_QUERY = "UPDATE loja.puzzle " +
            "SET preco = ?, nome = ? " +
            "WHERE nome = ?;";

    private static final String DELETE_QUERY = "DELETE FROM loja.puzzle " +
            "WHERE nome = ?;";

    public PuzzleDAO(Connection connection) {
        this.connection = connection;
        this.mapper = new TableMapper<>(Puzzle.class);
    }

    @Override
    public String create(Puzzle puzzle) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(CREATE_QUERY)) {
            statement.setString(1, puzzle.getNome());
            statement.setString(2, puzzle.getTipo());
            statement.setBigDecimal(3, puzzle.getPreco());
            statement.setString(4, puzzle.getNome_marca());
            statement.executeUpdate();
            return puzzle.getNome();
        } catch (SQLException ex) {
            Logger.getLogger(PuzzleDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().contains("not-null")) {
                throw new SQLException("Erro ao inserir puzzle: campo está em branco.");
            } else {
                throw new SQLException("Erro ao inserir puzzle.");
            }
        }
    }

    @Override
    public Puzzle read(String nome) throws SQLException {

        try (PreparedStatement statement = connection.prepareStatement(READ_QUERY)) {
            statement.setString(1, nome);
            try (ResultSet result = statement.executeQuery()) {
                if (result.next()) {
                    return this.mapper.mapRow(result, 1);
                } else {
                    throw new SQLException("Erro ao selecionar puzzle: não encontrado");
                }
            }
        } catch (SQLException ex) {
            Logger.getLogger(PuzzleDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().equals("Erro ao selecionar puzzle: não encontrado")) {
                throw ex;
            } else {
                throw new SQLException("Erro ao selecionar puzzle.");
            }
        }

    }

    @Override
    public void update(String nome, Puzzle puzzle) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(UPDATE_QUERY)) {
            statement.setBigDecimal(1, puzzle.getPreco());
            statement.setString(2, puzzle.getNome());
            statement.setString(3, nome);
            if (statement.executeUpdate() < 1) {
                throw new SQLException("Erro ao atualizar puzzle: não encontrado.");
            }
        } catch (SQLException ex) {
            Logger.getLogger(PuzzleDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().equals("Erro ao atualizar puzzle: não encontrado.")) {
                throw ex;
            } else if (ex.getMessage().contains("not-null")) {
                throw new SQLException("Erro ao atualizar puzzle: um campo está nulo.");
            } else {
                throw new SQLException("Erro ao atualizar puzzle");
            }
        }
    }

    @Override
    public void delete(String nome) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(DELETE_QUERY)) {
            statement.setString(1, nome);
            if (statement.executeUpdate() < 1) {
                throw new SQLException("Erro ao excluir puzzle:  não encontrado.");
            }
        } catch (SQLException ex) {
            Logger.getLogger(PuzzleDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().equals("Erro ao excluir puzzle: não encontrado.")) {
                throw ex;
            } else {
                throw new SQLException("Erro ao excluir puzzle");
            }
        }
    }

    @Override
    public List<Puzzle> all() throws SQLException {
        List<Puzzle> puzzles = new ArrayList<>();

        try (PreparedStatement statement = connection.prepareStatement(ALL_QUERY);
                ResultSet result = statement.executeQuery()) {
            while (result.next()) {
                puzzles.add(this.mapper.mapRow(result, 0));
            }
        } catch (SQLException ex) {
            Logger.getLogger(PuzzleDAO.class.getName()).log(Level.SEVERE, "DAO", ex);
            throw new SQLException("Erro ao listar puzzles");
        }

        return puzzles;
    }
}
