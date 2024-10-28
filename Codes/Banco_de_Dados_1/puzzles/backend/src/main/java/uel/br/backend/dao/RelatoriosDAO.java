package uel.br.backend.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.logging.Level;
import java.util.logging.Logger;

public class RelatoriosDAO {

    private final Connection connection;

    // SQL/relatorios.sql
    private static final String VENDAS_POR_PUZZLE_QUERY = "SELECT nome_puzzle,SUM(quantidade) AS total_vendido,SUM(quantidade * preco) AS valor_total "
            +
            "FROM loja.carrinho_contem_puzzle AS ccp " +
            "JOIN loja.carrinho_comprado AS cc ON ccp.id_carrinho = cc.id_carrinho " +
            "GROUP BY nome_puzzle " +
            "ORDER BY total_vendido DESC,valor_total DESC;";

    private static final String VENDAS_POR_MARCA_QUERY = "SELECT p.nome_marca, SUM(ccp.quantidade) AS total_vendido, SUM(ccp.quantidade * ccp.preco) AS valor_total "
            +
            "FROM loja.carrinho_contem_puzzle AS ccp " +
            "JOIN loja.carrinho_comprado AS cc ON ccp.id_carrinho = cc.id_carrinho " +
            "JOIN loja.puzzle AS p ON ccp.nome_puzzle = p.nome " +
            "GROUP BY p.nome_marca " +
            "ORDER BY total_vendido DESC, valor_total DESC;";

    private static final String VENDAS_POR_FAIXA_PRECO_QUERY = "SELECT " +
            "CASE " +
            "WHEN preco < 50 THEN '0..50' " +
            "WHEN preco BETWEEN 50 AND 100 THEN '50..100' " +
            "WHEN preco BETWEEN 100 AND 200 THEN '100..200' ELSE '200..' " +
            "END AS faixa_preco, SUM(quantidade) AS total_vendido, SUM(quantidade * preco) AS valor_total " +
            "FROM loja.carrinho_contem_puzzle AS ccp " +
            "JOIN loja.carrinho_comprado AS cc ON ccp.id_carrinho = cc.id_carrinho " +
            "GROUP BY faixa_preco " +
            "ORDER BY total_vendido DESC, valor_total DESC;";

    private static final String VENDAS_POR_CATEGORIA_QUERY = "SELECT p.tipo AS categoria, SUM(ccp.quantidade) AS total_vendido, SUM(ccp.quantidade * ccp.preco) AS valor_total "
            +
            "FROM loja.carrinho_contem_puzzle AS ccp " +
            "JOIN loja.carrinho_comprado AS cc ON ccp.id_carrinho = cc.id_carrinho " +
            "JOIN loja.puzzle AS p ON ccp.nome_puzzle = p.nome " +
            "GROUP BY p.tipo " +
            "ORDER BY total_vendido DESC, valor_total DESC;";

    private static final String COMPRAS_POR_USUARIO_QUERY = "SELECT cliente.id, cliente.login, COUNT(DISTINCT cc.id_carrinho) AS total_compras, COALESCE(SUM(ccp.quantidade * ccp.preco), 0) AS valor_total "
            +
            "FROM loja.cliente " +
            "LEFT OUTER JOIN loja.carrinho_comprado AS cc ON cliente.id = cc.id_cliente " +
            "LEFT OUTER JOIN loja.carrinho_contem_puzzle AS ccp ON cc.id_carrinho = ccp.id_carrinho " +
            "GROUP BY cliente.id " +
            "ORDER BY total_compras DESC, valor_total DESC;";

    private static final String TEMPO_PARA_PRIMEIRA_COMPRA_QUERY = "SELECT cliente.id, cliente.login, MIN(cc.data_compra - cliente.data_criacao) AS dias_para_primeira_compra "
            +
            "FROM loja.cliente " +
            "JOIN loja.carrinho_comprado AS cc ON cliente.id = cc.id_cliente " +
            "GROUP BY cliente.id " +
            "ORDER BY dias_para_primeira_compra ASC;";

    private static final String CATEGORIAS_COMPRADAS_POR_USUARIO_QUERY = "SELECT cliente.id, cliente.login, COUNT(DISTINCT p.tipo) AS categorias_compradas "
            +
            "FROM loja.cliente " +
            "JOIN loja.carrinho_comprado AS cc ON cliente.id = cc.id_cliente " +
            "JOIN loja.carrinho_contem_puzzle AS ccp ON cc.id_carrinho = ccp.id_carrinho " +
            "JOIN loja.puzzle AS p ON ccp.nome_puzzle = p.nome " +
            "GROUP BY cliente.id;";

    private static final String TEMPO_MEDIO_ENTRE_COMPRAS_QUERY = "WITH compra_categoria AS ( " +
            "SELECT DISTINCT cliente.login, cliente.id, p.tipo AS categoria, cc.data_compra, cc.id_carrinho " +
            "FROM loja.cliente " +
            "JOIN loja.carrinho_comprado AS cc ON cliente.id = cc.id_cliente " +
            "JOIN loja.carrinho_contem_puzzle AS ccp ON cc.id_carrinho = ccp.id_carrinho " +
            "JOIN loja.puzzle AS p ON ccp.nome_puzzle = p.nome" +
            ")" +
            "SELECT id, login, categoria, AVG(tempo) AS tempo_medio_entre_categoria " +
            "FROM ( " +
            "SELECT id, login, categoria, LEAD(data_compra) OVER (PARTITION BY id, categoria ORDER BY data_compra) - data_compra as tempo FROM compra_categoria"
            +
            ") AS tempo_entre_compras " +
            "GROUP BY id, login, categoria " +
            "ORDER BY id;";

    private static final String PERIODO_QUERY_DIA = "SELECT DATE_TRUNC('day', cc.data_compra) AS periodo, " +
            "SUM(ccp.quantidade) AS total_vendido, " +
            "SUM(ccp.quantidade * ccp.preco) AS valor_total " +
            "FROM loja.carrinho_comprado AS cc " +
            "JOIN loja.carrinho_contem_puzzle AS ccp ON cc.id_carrinho = ccp.id_carrinho " +
            "WHERE DATE_TRUNC('day', cc.data_compra) = TO_DATE(?, 'DD/MM/YY') " +
            "GROUP BY DATE_TRUNC('day', cc.data_compra) " +
            "ORDER BY periodo;";

    private static final String PERIODO_QUERY_MES = "SELECT DATE_TRUNC('month', cc.data_compra) AS periodo, " +
            "SUM(ccp.quantidade) AS total_vendido, " +
            "SUM(ccp.quantidade * ccp.preco) AS valor_total " +
            "FROM loja.carrinho_comprado AS cc " +
            "JOIN loja.carrinho_contem_puzzle AS ccp ON cc.id_carrinho = ccp.id_carrinho " +
            "WHERE TO_CHAR(cc.data_compra, 'MM/YYYY') = ? " +
            "GROUP BY DATE_TRUNC('month', cc.data_compra) " +
            "ORDER BY periodo;";

    private static final String PERIODO_QUERY_ANO = "SELECT DATE_TRUNC('year', cc.data_compra) AS periodo, " +
            "SUM(ccp.quantidade) AS total_vendido, " +
            "SUM(ccp.quantidade * ccp.preco) AS valor_total " +
            "FROM loja.carrinho_comprado AS cc " +
            "JOIN loja.carrinho_contem_puzzle AS ccp ON cc.id_carrinho = ccp.id_carrinho " +
            "WHERE TO_CHAR(cc.data_compra, 'YYYY') = ? " +
            "GROUP BY DATE_TRUNC('year', cc.data_compra) " +
            "ORDER BY periodo;";

    public RelatoriosDAO(Connection connection) {
        this.connection = connection;
    }

    public List<Map<String, Object>> vendasPorPuzzle() throws SQLException {
        return executeQuery(VENDAS_POR_PUZZLE_QUERY);
    }

    public List<Map<String, Object>> vendasPorMarca() throws SQLException {
        return executeQuery(VENDAS_POR_MARCA_QUERY);
    }

    public List<Map<String, Object>> vendasPorFaixaPreco() throws SQLException {
        return executeQuery(VENDAS_POR_FAIXA_PRECO_QUERY);
    }

    public List<Map<String, Object>> vendasPorCategoria() throws SQLException {
        return executeQuery(VENDAS_POR_CATEGORIA_QUERY);
    }

    public List<Map<String, Object>> comprasPorUsuario() throws SQLException {
        return executeQuery(COMPRAS_POR_USUARIO_QUERY);
    }

    public List<Map<String, Object>> tempoParaPrimeiraCompra() throws SQLException {
        return executeQuery(TEMPO_PARA_PRIMEIRA_COMPRA_QUERY);
    }

    public List<Map<String, Object>> categoriasCompradasPorUsuario() throws SQLException {
        return executeQuery(CATEGORIAS_COMPRADAS_POR_USUARIO_QUERY);
    }

    public List<Map<String, Object>> tempoMedioEntreCompras() throws SQLException {
        return executeQuery(TEMPO_MEDIO_ENTRE_COMPRAS_QUERY);
    }

    public List<Map<String, Object>> vendasPorPeriodo(String tipo, String valor) throws SQLException {
        String formattedDate;

        String query = switch (tipo.toLowerCase()) {
            case "dia" -> {
                formattedDate = valor.replace("-", "/"); // Formato esperado: "10-4-21" -> "10/4/21"
                yield PERIODO_QUERY_DIA;
            }
            case "mes" -> {
                formattedDate = valor.replace("-", "/"); // Formato esperado: "11-21" -> "11/21"
                yield PERIODO_QUERY_MES;
            }
            case "ano" -> {
                formattedDate = valor; // Formato esperado: "2021"
                yield PERIODO_QUERY_ANO;
            }
            default -> throw new SQLException("Tipo de período inválido. Use 'dia', 'mes' ou 'ano'.");
        };

        try (PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setString(1, formattedDate);

            try (ResultSet resultSet = statement.executeQuery()) {
                List<Map<String, Object>> results = new ArrayList<>();
                int columnCount = resultSet.getMetaData().getColumnCount();

                while (resultSet.next()) {
                    Map<String, Object> row = new HashMap<>();
                    for (int i = 1; i <= columnCount; i++) {
                        String columnName = resultSet.getMetaData().getColumnName(i);
                        row.put(columnName, resultSet.getObject(i));
                    }
                    results.add(row);
                }

                return results;
            }
        }
    }

    // Método Genérico para Executar Consultas
    private List<Map<String, Object>> executeQuery(String query) throws SQLException {
        List<Map<String, Object>> results = new ArrayList<>();

        try (PreparedStatement statement = connection.prepareStatement(query);
                ResultSet resultSet = statement.executeQuery()) {

            int columnCount = resultSet.getMetaData().getColumnCount();
            while (resultSet.next()) {
                Map<String, Object> row = new HashMap<>();
                for (int i = 1; i <= columnCount; i++) {
                    String columnName = resultSet.getMetaData().getColumnName(i);
                    row.put(columnName, resultSet.getObject(i));
                }
                results.add(row);
            }
        } catch (SQLException ex) {
            Logger.getLogger(RelatoriosDAO.class.getName()).log(Level.SEVERE, "DAO", ex);
            throw new SQLException("Erro ao executar consulta para relatório.");
        }

        return results;
    }

}
