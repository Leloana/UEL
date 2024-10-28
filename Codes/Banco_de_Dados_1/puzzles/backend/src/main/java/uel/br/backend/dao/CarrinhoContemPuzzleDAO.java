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
import uel.br.backend.model.ChaveCarrinhoPuzzle;
import uel.br.backend.model.CarrinhoContemPuzzle;

public class CarrinhoContemPuzzleDAO implements DAO<CarrinhoContemPuzzle, ChaveCarrinhoPuzzle> {
    private final Connection connection;
    private final TableMapper<CarrinhoContemPuzzle> mapper;

    private static final String CREATE_QUERY = "INSERT INTO loja.carrinho_contem_puzzle(id_carrinho,nome_puzzle,quantidade,preco) "
            + "VALUES(?,?,?,?);";

    private static final String ALL_QUERY = "SELECT * " +
            "FROM loja.carrinho_contem_puzzle; ";

    private static final String READ_QUERY = "SELECT * " +
            "FROM loja.carrinho_contem_puzzle " +
            "WHERE id_carrinho = ? AND nome_puzzle = ?;";

    private static final String UPDATE_QUERY = "UPDATE loja.carrinho_contem_puzzle " +
            "SET id_carrinho = ?, nome_puzzle = ?, quantidade = ?, preco = ?" +
            "WHERE id_carrinho = ? AND nome_puzzle = ?;";

    private static final String DELETE_QUERY = "DELETE FROM loja.carrinho_contem_puzzle " +
            "WHERE id_carrinho = ? AND nome_puzzle = ?;";

    private static final String ALL_BY_CARRINHO_QUERY = "SELECT * FROM loja.carrinho_contem_puzzle "
            + "WHERE id_carrinho = ?;";

    public CarrinhoContemPuzzleDAO(Connection connection) {
        this.connection = connection;
        this.mapper = new TableMapper<>(CarrinhoContemPuzzle.class);
    }

    @Override
    public ChaveCarrinhoPuzzle create(CarrinhoContemPuzzle carrinho_contem_puzzle) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(CREATE_QUERY)) {
            statement.setInt(1, carrinho_contem_puzzle.getId_carrinho());
            statement.setString(2, carrinho_contem_puzzle.getNome_puzzle());
            statement.setInt(3, carrinho_contem_puzzle.getQuantidade());
            statement.setBigDecimal(4, carrinho_contem_puzzle.getPreco());
            statement.executeUpdate();
            return new ChaveCarrinhoPuzzle(carrinho_contem_puzzle.getId_carrinho(),
                    carrinho_contem_puzzle.getNome_puzzle());
        } catch (SQLException ex) {
            Logger.getLogger(CarrinhoContemPuzzleDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().contains("not-null")) {
                throw new SQLException("Erro ao inserir carrinho_contem_puzzle: campo está em branco.");
            } else {
                throw new SQLException("Erro ao inserir carrinho_contem_puzzle.");
            }
        }
    }

    @Override
    public CarrinhoContemPuzzle read(ChaveCarrinhoPuzzle chave) throws SQLException {

        try (PreparedStatement statement = connection.prepareStatement(READ_QUERY)) {
            statement.setInt(1, chave.id_carrinho());
            statement.setString(2, chave.nome_puzzle());
            try (ResultSet result = statement.executeQuery()) {
                if (result.next()) {
                    return this.mapper.mapRow(result, 1);
                } else {
                    throw new SQLException("Erro ao selecionar carrinho_contem_puzzle: não encontrado");
                }
            }
        } catch (SQLException ex) {
            Logger.getLogger(CarrinhoContemPuzzleDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().equals("Erro ao selecionar carrinho_contem_puzzle: não encontrado")) {
                throw ex;
            } else {
                throw new SQLException("Erro ao selecionar carrinho_contem_puzzle.");
            }
        }

    }

    @Override
    public void update(ChaveCarrinhoPuzzle chave_antiga, CarrinhoContemPuzzle carrinho_contem_puzzle)
            throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(UPDATE_QUERY)) {
            statement.setInt(1, carrinho_contem_puzzle.getId_carrinho());
            statement.setString(2, carrinho_contem_puzzle.getNome_puzzle());
            statement.setInt(3, carrinho_contem_puzzle.getQuantidade());
            statement.setBigDecimal(4, carrinho_contem_puzzle.getPreco());
            statement.setInt(5, chave_antiga.id_carrinho());
            statement.setString(6, chave_antiga.nome_puzzle());
            if (statement.executeUpdate() < 1) {
                throw new SQLException("Erro ao atualizar carrinho_contem_puzzle: não encontrado.");
            }
        } catch (SQLException ex) {
            Logger.getLogger(CarrinhoContemPuzzleDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().equals("Erro ao atualizar carrinho_contem_puzzle: não encontrado.")) {
                throw ex;
            } else if (ex.getMessage().contains("not-null")) {
                throw new SQLException("Erro ao atualizar carrinho_contem_puzzle: um campo está nulo.");
            } else {
                throw new SQLException("Erro ao atualizar carrinho_contem_puzzle");
            }
        }
    }

    @Override
    public void delete(ChaveCarrinhoPuzzle chave) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(DELETE_QUERY)) {
            statement.setInt(1, chave.id_carrinho());
            statement.setString(2, chave.nome_puzzle());
            if (statement.executeUpdate() < 1) {
                throw new SQLException("Erro ao excluir carrinho_contem_puzzle:  não encontrado.");
            }
        } catch (SQLException ex) {
            Logger.getLogger(CarrinhoContemPuzzleDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().equals("Erro ao excluir carrinho_contem_puzzle: não encontrado.")) {
                throw ex;
            } else {
                throw new SQLException("Erro ao excluir carrinho_contem_puzzle");
            }
        }
    }

    @Override
    public List<CarrinhoContemPuzzle> all() throws SQLException {
        List<CarrinhoContemPuzzle> carrinho_contem_puzzles = new ArrayList<>();

        try (PreparedStatement statement = connection.prepareStatement(ALL_QUERY);
                ResultSet result = statement.executeQuery()) {
            while (result.next()) {
                carrinho_contem_puzzles.add(this.mapper.mapRow(result, 0));
            }
        } catch (SQLException ex) {
            Logger.getLogger(CarrinhoContemPuzzleDAO.class.getName()).log(Level.SEVERE, "DAO", ex);
            throw new SQLException("Erro ao listar carrinho_contem_puzzles");
        }

        return carrinho_contem_puzzles;
    }

    public List<CarrinhoContemPuzzle> allByCarrinho(Integer id_carrinho) throws SQLException {
        List<CarrinhoContemPuzzle> carrinho_contem_puzzles = new ArrayList<>();

        try (PreparedStatement statement = connection.prepareStatement(ALL_BY_CARRINHO_QUERY)) {
            statement.setInt(1, id_carrinho);
            try (ResultSet result = statement.executeQuery()) {
                while (result.next()) {
                    carrinho_contem_puzzles.add(this.mapper.mapRow(result, 0));
                }
            }
        } catch (SQLException ex) {
            Logger.getLogger(CarrinhoContemPuzzleDAO.class.getName()).log(Level.SEVERE, "DAO", ex);
            throw new SQLException("Erro ao listar carrinho_contem_puzzles por carrinho");
        }

        return carrinho_contem_puzzles;
    }
}
