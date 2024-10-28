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
import uel.br.backend.model.ChavePalavraChave;
import uel.br.backend.model.PalavraChave;

public class PalavraChaveDAO implements DAO<PalavraChave, ChavePalavraChave> {
    private final Connection connection;
    private final TableMapper<PalavraChave> mapper;

    private static final String CREATE_QUERY = "INSERT INTO loja.palavra_chave(palavra,nome_puzzle) "
            + "VALUES(?,?);";

    private static final String ALL_QUERY = "SELECT * " +
            "FROM loja.palavra_chave; ";

    private static final String READ_QUERY = "SELECT * " +
            "FROM loja.palavra_chave " +
            "WHERE palavra = ? AND nome_puzzle = ?;";

    private static final String UPDATE_QUERY = "UPDATE loja.palavra_chave " +
            "SET palavra = ?, nome_puzzle = ?" +
            "WHERE palavra = ? AND nome_puzzle = ?;";

    private static final String DELETE_QUERY = "DELETE FROM loja.palavra_chave " +
            "WHERE palavra = ? AND nome_puzzle = ?;";

    public PalavraChaveDAO(Connection connection) {
        this.connection = connection;
        this.mapper = new TableMapper<>(PalavraChave.class);
    }

    @Override
    public ChavePalavraChave create(PalavraChave palavra_chave) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(CREATE_QUERY)) {
            statement.setString(1, palavra_chave.getPalavra());
            statement.setString(2, palavra_chave.getNome_puzzle());
            statement.executeUpdate();
            return new ChavePalavraChave(palavra_chave.getPalavra(), palavra_chave.getNome_puzzle());
        } catch (SQLException ex) {
            Logger.getLogger(PalavraChaveDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().contains("not-null")) {
                throw new SQLException("Erro ao inserir palavra_chave: campo está em branco.");
            } else {
                throw new SQLException("Erro ao inserir palavra_chave.");
            }
        }
    }

    @Override
    public PalavraChave read(ChavePalavraChave chave) throws SQLException {

        try (PreparedStatement statement = connection.prepareStatement(READ_QUERY)) {
            statement.setString(1, chave.palavra());
            statement.setString(2, chave.nome_puzzle());
            try (ResultSet result = statement.executeQuery()) {

                if (result.next()) {
                    return this.mapper.mapRow(result, 1);
                } else {
                    throw new SQLException("Erro ao selecionar palavra_chave: não encontrado");
                }
            }
        } catch (SQLException ex) {
            Logger.getLogger(PalavraChaveDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().equals("Erro ao selecionar palavra_chave: não encontrado")) {
                throw ex;
            } else {
                throw new SQLException("Erro ao selecionar palavra_chave.");
            }
        }

    }

    @Override
    public void update(ChavePalavraChave chave_antiga, PalavraChave palavra_chave) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(UPDATE_QUERY)) {
            statement.setString(1, palavra_chave.getPalavra());
            statement.setString(2, palavra_chave.getNome_puzzle());
            statement.setString(3, chave_antiga.palavra());
            statement.setString(4, chave_antiga.nome_puzzle());
            if (statement.executeUpdate() < 1) {
                throw new SQLException("Erro ao atualizar palavra_chave: não encontrado.");
            }
        } catch (SQLException ex) {
            Logger.getLogger(PalavraChaveDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().equals("Erro ao atualizar palavra_chave: não encontrado.")) {
                throw ex;
            } else if (ex.getMessage().contains("not-null")) {
                throw new SQLException("Erro ao atualizar palavra_chave: um campo está nulo.");
            } else {
                throw new SQLException("Erro ao atualizar palavra_chave");
            }
        }
    }

    @Override
    public void delete(ChavePalavraChave chave) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(DELETE_QUERY)) {
            statement.setString(1, chave.palavra());
            statement.setString(2, chave.nome_puzzle());
            if (statement.executeUpdate() < 1) {
                throw new SQLException("Erro ao excluir palavra_chave:  não encontrado.");
            }
        } catch (SQLException ex) {
            Logger.getLogger(PalavraChaveDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().equals("Erro ao excluir palavra_chave: não encontrado.")) {
                throw ex;
            } else {
                throw new SQLException("Erro ao excluir palavra_chave");
            }
        }
    }

    @Override
    public List<PalavraChave> all() throws SQLException {
        List<PalavraChave> palavra_chaves = new ArrayList<>();

        try (PreparedStatement statement = connection.prepareStatement(ALL_QUERY);
                ResultSet result = statement.executeQuery()) {
            while (result.next()) {
                palavra_chaves.add(this.mapper.mapRow(result, 0));
            }
        } catch (SQLException ex) {
            Logger.getLogger(PalavraChaveDAO.class.getName()).log(Level.SEVERE, "DAO", ex);
            throw new SQLException("Erro ao listar palavra_chaves");
        }

        return palavra_chaves;
    }
}
