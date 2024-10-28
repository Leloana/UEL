package uel.br.backend.jdbc;

import java.sql.SQLException;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import uel.br.backend.dao.ClienteDAO;
import uel.br.backend.dao.ClockDAO;
import uel.br.backend.dao.Cubo2DAO;
import uel.br.backend.dao.Cubo3DAO;
import uel.br.backend.dao.Cubo4DAO;
import uel.br.backend.dao.ImagemDAO;
import uel.br.backend.dao.MarcaDAO;
import uel.br.backend.dao.PalavraChaveDAO;
import uel.br.backend.dao.PiraminxDAO;
import uel.br.backend.dao.PuzzleDAO;
import uel.br.backend.dao.RelatoriosDAO;
import uel.br.backend.dao.CarrinhoAtualDAO;
import uel.br.backend.dao.CarrinhoCompradoDAO;
import uel.br.backend.dao.CarrinhoContemPuzzleDAO;
import uel.br.backend.dao.CarrinhoDAO;

@Component
public class ConnectionHandler {

    private static ConnectionFactory connectionFactory = null;

    @Autowired
    public ConnectionHandler(ConnectionFactory cf) {
        if (connectionFactory == null) {
            connectionFactory = cf;
        }
    }

    public void beginTransaction() throws SQLException {
        try {
            connectionFactory.getConnection().setAutoCommit(false);
        } catch (SQLException ex) {
            System.err.println(ex.getMessage());
            throw new SQLException("Erro ao iniciar transação.");
        }
    }

    public void commitTransaction() throws SQLException {
        try {
            connectionFactory.getConnection().commit();
        } catch (SQLException ex) {
            System.err.println(ex.getMessage());
            throw new SQLException("Erro ao finalizar transação.");
        }
    }

    public void rollbackTransaction() throws SQLException {
        try {
            connectionFactory.getConnection().rollback();
        } catch (SQLException ex) {
            System.err.println(ex.getMessage());
            throw new SQLException("Erro ao executar transação.");
        }
    }

    public void endTransaction() throws SQLException {
        try {
            connectionFactory.getConnection().setAutoCommit(true);
        } catch (SQLException ex) {
            System.err.println(ex.getMessage());
            throw new SQLException("Erro ao finalizar transação.");
        }
    }

    public ClienteDAO getClienteDAO() throws SQLException {
        return new ClienteDAO(connectionFactory.getConnection());
    }

    public PuzzleDAO getPuzzleDAO() throws SQLException {
        return new PuzzleDAO(connectionFactory.getConnection());
    }

    public CarrinhoDAO getCarrinhoDAO() throws SQLException {
        return new CarrinhoDAO(connectionFactory.getConnection());
    }

    public CarrinhoAtualDAO getCarrinhoAtualDAO() throws SQLException {
        return new CarrinhoAtualDAO(connectionFactory.getConnection());
    }

    public CarrinhoCompradoDAO getCarrinhoCompradoDAO() throws SQLException {
        return new CarrinhoCompradoDAO(connectionFactory.getConnection());
    }

    public CarrinhoContemPuzzleDAO getCarrinhoContemPuzzleDAO() throws SQLException {
        return new CarrinhoContemPuzzleDAO(connectionFactory.getConnection());
    }

    public ImagemDAO getImagemDAO() throws SQLException {
        return new ImagemDAO(connectionFactory.getConnection());
    }

    public MarcaDAO getMarcaDAO() throws SQLException {
        return new MarcaDAO(connectionFactory.getConnection());
    }

    public PalavraChaveDAO getPalavraChaveDAO() throws SQLException {
        return new PalavraChaveDAO(connectionFactory.getConnection());
    }

    public Cubo2DAO getCubo2DAO() throws SQLException {
        return new Cubo2DAO(connectionFactory.getConnection());
    }

    public Cubo3DAO getCubo3DAO() throws SQLException {
        return new Cubo3DAO(connectionFactory.getConnection());
    }

    public Cubo4DAO getCubo4DAO() throws SQLException {
        return new Cubo4DAO(connectionFactory.getConnection());
    }

    public PiraminxDAO getPiraminxDAO() throws SQLException {
        return new PiraminxDAO(connectionFactory.getConnection());
    }

    public ClockDAO getClockDAO() throws SQLException {
        return new ClockDAO(connectionFactory.getConnection());
    }

    public RelatoriosDAO getRelatorioDAO() throws SQLException {
        return new RelatoriosDAO(connectionFactory.getConnection());
    }
}
