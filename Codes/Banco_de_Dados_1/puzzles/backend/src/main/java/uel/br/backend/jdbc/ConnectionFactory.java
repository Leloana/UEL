package uel.br.backend.jdbc;

import java.sql.Connection;
import java.sql.SQLException;

import javax.sql.DataSource;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

@Component
public class ConnectionFactory {
    private static DataSource dataSource = null;
    private static Connection connection = null;

    @Autowired
    public ConnectionFactory(DataSource ds) throws SQLException {
        if (dataSource == null) {
            dataSource = ds;
        }
        if (connection == null) {
            connection = dataSource.getConnection();
        }
    }

    public Connection getConnection() throws SQLException {
        return connection;
    }

}
