package uel.br.backend.controller;

import java.sql.SQLException;
import java.util.List;
import java.util.Map;
import java.util.logging.Level;
import java.util.logging.Logger;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;

import uel.br.backend.jdbc.ConnectionHandler;

@Controller
@RequestMapping("/relatorios")
public class RelatoriosController {
    @Autowired
    ConnectionHandler connectionHandler;

    @GetMapping("/vendas-por-puzzle")
    @ResponseBody
    public List<Map<String, Object>> vendasPorPuzzle() throws SQLException {
        return connectionHandler.getRelatorioDAO().vendasPorPuzzle();
    }

    @GetMapping("/vendas-por-puzzle.html")
    public String vendasPorPuzzleHtml(Model model) {
        try {
            List<Map<String, Object>> relatorio = connectionHandler.getRelatorioDAO().vendasPorPuzzle();
            model.addAttribute("vendasPorPuzzle", relatorio);
            return "/vendas-por-puzzle"; // Nome da página HTML
        } catch (SQLException e) {
            model.addAttribute("error", "Erro ao buscar dados de vendas por puzzle.");
            return "error";
        }
    }

    @GetMapping("/vendas-por-marca")
    @ResponseBody
    public List<Map<String, Object>> vendasPorMarca() throws SQLException {
        return connectionHandler.getRelatorioDAO().vendasPorMarca();
    }

    @GetMapping("/vendas-por-marca.html")
    public String vendasPorMarcaHtml(Model model) {
        try {
            List<Map<String, Object>> relatorio = connectionHandler.getRelatorioDAO().vendasPorMarca();
            model.addAttribute("vendasPorMarca", relatorio);
            return "/vendas-por-marca"; // Nome da página HTML
        } catch (SQLException e) {
            model.addAttribute("error", "Erro ao buscar dados de vendas por marca.");
            return "error";
        }
    }

    @GetMapping("/vendas-por-preco")
    @ResponseBody
    public List<Map<String, Object>> vendasPorFaixaPreco() throws SQLException {
        return connectionHandler.getRelatorioDAO().vendasPorFaixaPreco();
    }

    @GetMapping("/vendas-por-preco.html")
    public String vendasPorFaixaPrecoHtml(Model model) {
        try {
            List<Map<String, Object>> relatorio = connectionHandler.getRelatorioDAO().vendasPorFaixaPreco();
            model.addAttribute("vendasPorFaixaPreco", relatorio);
            return "/vendas-por-preco"; // Nome da página HTML
        } catch (SQLException e) {
            model.addAttribute("error", "Erro ao buscar dados de vendas por preco.");
            return "error";
        }
    }

    @GetMapping("/vendas-por-categoria")
    @ResponseBody
    public List<Map<String, Object>> vendasPorCategoria() throws SQLException {
        return connectionHandler.getRelatorioDAO().vendasPorCategoria();
    }

    @GetMapping("/vendas-por-categoria.html")
    public String vendasPorCategoriaHtml(Model model) {
        try {
            List<Map<String, Object>> relatorio = connectionHandler.getRelatorioDAO().vendasPorCategoria();
            model.addAttribute("vendasPorCategoria", relatorio);
            return "/vendas-por-categoria"; // Nome da página HTML
        } catch (SQLException e) {
            model.addAttribute("error", "Erro ao buscar dados de vendas por categoria.");
            return "error";
        }
    }

    @GetMapping("/compras-por-usuario")
    @ResponseBody
    public List<Map<String, Object>> comprasPorUsuario() throws SQLException {
        return connectionHandler.getRelatorioDAO().comprasPorUsuario();
    }

    @GetMapping("/compras-por-usuario.html")
    public String comprasPorUsuario(Model model) {
        try {
            List<Map<String, Object>> relatorio = connectionHandler.getRelatorioDAO().comprasPorUsuario();
            model.addAttribute("comprasPorUsuario", relatorio);
            return "/compras-por-usuario"; // Nome da página HTML
        } catch (SQLException e) {
            model.addAttribute("error", "Erro ao buscar dados de compras por usuario.");
            return "error";
        }
    }

    @GetMapping("/tempo-primeira-compra")
    @ResponseBody
    public List<Map<String, Object>> tempoParaPrimeiraCompra() throws SQLException {
        return connectionHandler.getRelatorioDAO().tempoParaPrimeiraCompra();
    }

    @GetMapping("/tempo-primeira-compra.html")
    public String tempoParaPrimeiraCompraHtml(Model model) {
        try {
            List<Map<String, Object>> relatorio = connectionHandler.getRelatorioDAO().tempoParaPrimeiraCompra();
            model.addAttribute("tempoParaPrimeiraCompra", relatorio);
            return "/tempo-primeira-compra"; // Nome da página HTML
        } catch (SQLException e) {
            model.addAttribute("error", "Erro ao buscar dados de tempo para primeira compra.");
            return "error";
        }
    }

    @GetMapping("/categorias-compradas-usuario")
    @ResponseBody
    public List<Map<String, Object>> categoriasCompradasPorUsuario() throws SQLException {
        return connectionHandler.getRelatorioDAO().categoriasCompradasPorUsuario();
    }

    @GetMapping("/categorias-compradas-usuario.html")
    public String categoriasCompradasPorUsuarioHtml(Model model) {
        try {
            List<Map<String, Object>> relatorio = connectionHandler.getRelatorioDAO().categoriasCompradasPorUsuario();
            model.addAttribute("categoriasCompradasPorUsuario", relatorio);
            return "/categorias-compradas-usuario"; // Nome da página HTML
        } catch (SQLException e) {
            model.addAttribute("error", "Erro ao buscar dados de categorias compradas por usuario.");
            return "error";
        }
    }

    @GetMapping("/tempo-medio")
    @ResponseBody
    public List<Map<String, Object>> tempoMedioEntreCompras() throws SQLException {
        return connectionHandler.getRelatorioDAO().tempoMedioEntreCompras();
    }
    @GetMapping("/tempo-medio.html")
    public String tempoMedioEntreCompras(Model model) {
        try {
            List<Map<String, Object>> relatorio = connectionHandler.getRelatorioDAO().tempoMedioEntreCompras(); // Método que executa a query
            model.addAttribute("tempoMedioEntreCompras", relatorio);
            return "tempo-medio-entre-compras";  // Nome da página HTML
        } catch (SQLException e) {
            model.addAttribute("error", "Erro ao buscar dados de tempo médio entre compras por categoria.");
            return "error";
        }
    }

    @GetMapping("/vendas-por-periodo/{tipo}/{valor}")
    @ResponseBody
    public List<Map<String, Object>> vendasPorPeriodo(@PathVariable String tipo, @PathVariable String valor) throws SQLException {
        return connectionHandler.getRelatorioDAO().vendasPorPeriodo(tipo, valor);
    }

    @GetMapping("/analise-por-periodo.html")
    public String analisePorPeriodo() {
        return "analise-por-periodo";  // Nome da página HTML para escolher o período
    }

    @GetMapping("/vendas-por-periodo.html/{tipo}/{valor}")
    public String vendasPorPeriodo(@PathVariable String tipo, @PathVariable String valor, Model model) {
        try {
            // Chama o DAO para buscar os dados de acordo com o tipo e valor fornecidos
            List<Map<String, Object>> relatorio = connectionHandler.getRelatorioDAO().vendasPorPeriodo(tipo, valor);

            // Adiciona os dados ao modelo para serem usados no template Thymeleaf
            model.addAttribute("vendasPorPeriodo", relatorio);
            model.addAttribute("tipo", tipo);
            model.addAttribute("valor", valor);

            return "vendas-por-periodo";  // Nome da página HTML que exibirá o gráfico
        } catch (SQLException e) {
            model.addAttribute("error", "Erro ao buscar dados de vendas por período.");
            return "error";  // Retorna para uma página de erro se houver falha na consulta
        }
    }

}
