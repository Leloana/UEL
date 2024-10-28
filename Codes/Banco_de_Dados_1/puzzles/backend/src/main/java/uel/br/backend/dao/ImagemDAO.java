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
import uel.br.backend.model.ChaveImagem;
import uel.br.backend.model.Imagem;

public class ImagemDAO implements DAO<Imagem, ChaveImagem> {
    private final Connection connection;
    private final TableMapper<Imagem> mapper;

    private static final String CREATE_QUERY = "INSERT INTO loja.imagem(imagem,nome_puzzle) "
            + "VALUES(?,?);";

    private static final String ALL_QUERY = "SELECT * " +
            "FROM loja.imagem; ";

    private static final String READ_QUERY = "SELECT * " +
            "FROM loja.imagem " +
            "WHERE imagem = ? AND nome_puzzle = ?;";

    private static final String UPDATE_QUERY = "UPDATE loja.imagem " +
            "SET imagem = ?, nome_puzzle = ?" +
            "WHERE imagem = ? AND nome_puzzle = ?;";

    private static final String DELETE_QUERY = "DELETE FROM loja.imagem " +
            "WHERE imagem = ? AND nome_puzzle = ?;";

    public ImagemDAO(Connection connection) {
        this.connection = connection;
        this.mapper = new TableMapper<>(Imagem.class);
    }

    @Override
    public ChaveImagem create(Imagem imagem) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(CREATE_QUERY)) {
            statement.setString(1, imagem.getImagem());
            statement.setString(2, imagem.getNome_puzzle());
            statement.executeUpdate();
            return new ChaveImagem(imagem.getImagem(), imagem.getNome_puzzle());
        } catch (SQLException ex) {
            Logger.getLogger(ImagemDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().contains("not-null")) {
                throw new SQLException("Erro ao inserir imagem: campo está em branco.");
            } else {
                throw new SQLException("Erro ao inserir imagem.");
            }
        }
    }

    @Override
    public Imagem read(ChaveImagem chave) throws SQLException {

        try (PreparedStatement statement = connection.prepareStatement(READ_QUERY)) {
            statement.setString(1, chave.imagem());
            statement.setString(2, chave.nome_puzzle());
            try (ResultSet result = statement.executeQuery()) {
                if (result.next()) {
                    return this.mapper.mapRow(result, 1);
                } else {
                    throw new SQLException("Erro ao selecionar imagem: não encontrado");
                }
            }
        } catch (SQLException ex) {
            Logger.getLogger(ImagemDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().equals("Erro ao selecionar imagem: não encontrado")) {
                throw ex;
            } else {
                throw new SQLException("Erro ao selecionar imagem.");
            }
        }

    }

    @Override
    public void update(ChaveImagem chave_antiga, Imagem imagem) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(UPDATE_QUERY)) {
            statement.setString(1, imagem.getImagem());
            statement.setString(2, imagem.getNome_puzzle());
            statement.setString(3, chave_antiga.imagem());
            statement.setString(4, chave_antiga.nome_puzzle());
            if (statement.executeUpdate() < 1) {
                throw new SQLException("Erro ao atualizar imagem: não encontrado.");
            }
        } catch (SQLException ex) {
            Logger.getLogger(ImagemDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().equals("Erro ao atualizar imagem: não encontrado.")) {
                throw ex;
            } else if (ex.getMessage().contains("not-null")) {
                throw new SQLException("Erro ao atualizar imagem: um campo está nulo.");
            } else {
                throw new SQLException("Erro ao atualizar imagem");
            }
        }
    }

    @Override
    public void delete(ChaveImagem chave) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(DELETE_QUERY)) {
            statement.setString(1, chave.imagem());
            statement.setString(2, chave.nome_puzzle());
            if (statement.executeUpdate() < 1) {
                throw new SQLException("Erro ao excluir imagem:  não encontrado.");
            }
        } catch (SQLException ex) {
            Logger.getLogger(ImagemDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().equals("Erro ao excluir imagem: não encontrado.")) {
                throw ex;
            } else {
                throw new SQLException("Erro ao excluir imagem");
            }
        }
    }

    @Override
    public List<Imagem> all() throws SQLException {
        List<Imagem> imagems = new ArrayList<>();

        try (PreparedStatement statement = connection.prepareStatement(ALL_QUERY);
                ResultSet result = statement.executeQuery()) {
            while (result.next()) {
                imagems.add(this.mapper.mapRow(result, 0));
            }
        } catch (SQLException ex) {
            Logger.getLogger(ImagemDAO.class.getName()).log(Level.SEVERE, "DAO", ex);
            throw new SQLException("Erro ao listar imagems");
        }

        return imagems;
    }
}
