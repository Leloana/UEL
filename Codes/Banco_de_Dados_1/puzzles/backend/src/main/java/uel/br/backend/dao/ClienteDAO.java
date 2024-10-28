package uel.br.backend.dao;

import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

import uel.br.backend.mapper.TableMapper;
import uel.br.backend.model.Cliente;

public class ClienteDAO implements DAO<Cliente, Integer> {

    private final Connection connection;
    private final TableMapper<Cliente> mapper;

    private static final String AUTHENTICATE_QUERY = "SELECT id, login, data_criacao, id_carrinho_atual " +
            "FROM loja.cliente " +
            "WHERE login = ? AND senha = md5(?);";

    private static final String CREATE_QUERY = "INSERT INTO loja.cliente(login, senha, data_criacao, id_carrinho_atual) "
            + "VALUES(?, md5(?), ?, ?);";

    private static final String ALL_QUERY = "SELECT id, login, data_criacao, id_carrinho_atual " +
            "FROM loja.cliente " +
            "ORDER BY id;";

    private static final String READ_QUERY = "SELECT id, login, data_criacao, id_carrinho_atual " +
            "FROM loja.cliente " +
            "WHERE id = ?;";

    private static final String UPDATE_QUERY = "UPDATE loja.cliente " +
            "SET login = ? " +
            "WHERE id = ?;";

    private static final String UPDATE_WITH_PASSWORD_QUERY = "UPDATE loja.cliente " +
            "SET login = ?, senha = md5(?) " +
            "WHERE id = ?;";

    private static final String DELETE_QUERY = "DELETE FROM loja.cliente " +
            "WHERE id = ?;";

    public ClienteDAO(Connection connection) {
        this.connection = connection;
        this.mapper = new TableMapper<Cliente>(Cliente.class);
    }

    public Cliente authenticate(String login, String senha) throws SQLException, SecurityException {
        try (PreparedStatement statement = connection.prepareStatement(AUTHENTICATE_QUERY)) {
            statement.setString(1, login);
            statement.setString(2, senha);

            try (ResultSet result = statement.executeQuery()) {
                if (result.next()) {
                    return this.mapper.mapRow(result, 1);
                } else {
                    throw new SQLException("Erro ao autenticar cliente: não encontrado");
                }
            }
        } catch (SQLException ex) {
            Logger.getLogger(ClienteDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            throw new SQLException("Erro ao autenticar cliente.");
        }

    }

    @Override
    public Integer create(Cliente cliente) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(CREATE_QUERY, Statement.RETURN_GENERATED_KEYS)) {
            statement.setString(1, cliente.getLogin());
            statement.setString(2, cliente.getSenha());
            statement.setDate(3, cliente.getData_criacao());
            statement.setInt(4, cliente.getId_carrinho_atual());
            statement.executeUpdate();
            try (ResultSet generatedKeys = statement.getGeneratedKeys()) {
                if (generatedKeys.next()) {
                    return generatedKeys.getInt("id");
                } else {
                    throw new SQLException("Erro ao inserir cliente.");
                }
            }
        } catch (SQLException ex) {
            Logger.getLogger(ClienteDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().contains("uq_login_cliente")) {
                throw new SQLException("Erro ao inserir cliente: login já existente.");
            } else if (ex.getMessage().contains("not-null")) {
                throw new SQLException("Erro ao inserir cliente: campo está em branco.");
            } else {
                throw new SQLException("Erro ao inserir cliente.");
            }
        }
    }

    @Override
    public Cliente read(Integer id) throws SQLException {

        try (PreparedStatement statement = connection.prepareStatement(READ_QUERY)) {
            statement.setInt(1, id);
            try (ResultSet result = statement.executeQuery()) {
                if (result.next()) {
                    return this.mapper.mapRow(result, 1);
                } else {
                    throw new SQLException("Erro ao selecionar cliente: não encontrado");
                }
            }
        } catch (SQLException ex) {
            Logger.getLogger(ClienteDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().equals("Erro ao selecionar cliente: não encontrado")) {
                throw ex;
            } else {
                throw new SQLException("Erro ao selecionar cliente.");
            }
        }

    }

    @Override
    public void update(Integer id, Cliente cliente) throws SQLException {
        String query;

        if ((cliente.getSenha() == null) || (cliente.getSenha().isBlank())) {
            query = UPDATE_QUERY;
        } else {
            query = UPDATE_WITH_PASSWORD_QUERY;
        }

        try (PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setString(1, cliente.getLogin());

            if ((cliente.getSenha() == null) || (cliente.getSenha().isBlank())) {
                statement.setInt(2, id);
            } else {
                statement.setString(2, cliente.getSenha());
                statement.setInt(3, id);
            }

            if (statement.executeUpdate() < 1) {
                throw new SQLException("Erro ao atualizar cliente: não encontrado.");
            }
        } catch (SQLException ex) {
            Logger.getLogger(ClienteDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().equals("Erro ao atualizar cliente: não encontrado.")) {
                throw ex;
            } else if (ex.getMessage().contains("uq_login_cliente")) {
                throw new SQLException("Erro ao atualizar cliente: login já existe.");
            } else if (ex.getMessage().contains("not-null")) {
                throw new SQLException("Erro ao atualizar cliente: um campo está nulo.");
            } else {
                throw new SQLException("Erro ao atualizar cliente");
            }
        }
    }

    @Override
    public void delete(Integer id) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(DELETE_QUERY)) {
            statement.setInt(1, id);

            if (statement.executeUpdate() < 1) {
                throw new SQLException("Erro ao excluir cliente: não encontrado.");
            }
        } catch (SQLException ex) {
            Logger.getLogger(ClienteDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            if (ex.getMessage().equals("Erro ao excluir cliente: não encontrado.")) {
                throw ex;
            } else {
                throw new SQLException("Erro ao excluir cliente");
            }
        }
    }

    @Override
    public List<Cliente> all() throws SQLException {
        List<Cliente> clientes = new ArrayList<>();

        try (PreparedStatement statement = connection.prepareStatement(ALL_QUERY);
                ResultSet result = statement.executeQuery()) {
            while (result.next()) {
                clientes.add(this.mapper.mapRow(result, 0));
            }
        } catch (SQLException ex) {
            Logger.getLogger(ClienteDAO.class.getName()).log(Level.SEVERE, "DAO", ex);

            throw new SQLException("Erro ao listar clientes");
        }

        return clientes;
    }
}
