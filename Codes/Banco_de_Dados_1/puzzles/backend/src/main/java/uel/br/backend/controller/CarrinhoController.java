package uel.br.backend.controller;

import java.math.BigDecimal;
import java.sql.SQLException;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import uel.br.backend.dao.CarrinhoContemPuzzleDAO;
import uel.br.backend.jdbc.ConnectionHandler;
import uel.br.backend.model.Carrinho;
import uel.br.backend.model.CarrinhoAtual;
import uel.br.backend.model.CarrinhoComprado;
import uel.br.backend.model.CarrinhoContemPuzzle;
import uel.br.backend.model.ChaveCarrinhoPuzzle;
import uel.br.backend.model.Cliente;
import uel.br.backend.model.Puzzle;

@RestController
@RequestMapping("/carrinhos")
public class CarrinhoController {

    @Autowired
    ConnectionHandler connectionHandler;

    @PostMapping
    public void create(@RequestBody Carrinho carrinho) throws SQLException {
        connectionHandler.getCarrinhoDAO().create(carrinho);
    }

    @GetMapping("/{id}")
    public Carrinho read(@PathVariable Integer id) throws SQLException {
        return connectionHandler.getCarrinhoDAO().read(id);
    }

    @DeleteMapping("/{id}")
    public void delete(@PathVariable Integer id) throws SQLException {
        connectionHandler.getCarrinhoDAO().delete(id);
    }

    @GetMapping
    public List<Carrinho> all() throws SQLException {
        return connectionHandler.getCarrinhoDAO().all();
    }

    @GetMapping("/comprados/nota-fiscal/{id}")
    public Map<String, Object> notaFiscal(@PathVariable Integer id) throws SQLException {
        List<CarrinhoContemPuzzle> contemPuzzles = connectionHandler.getCarrinhoContemPuzzleDAO()
                .allByCarrinho(id);
        BigDecimal precoTotal = contemPuzzles.stream()
                .map(p -> p.getPreco().multiply(new BigDecimal(p.getQuantidade())))
                .reduce(new BigDecimal(0), BigDecimal::add);
        CarrinhoComprado carrinhoComprado = connectionHandler.getCarrinhoCompradoDAO().read(id);
        Cliente cliente = connectionHandler.getClienteDAO().read(carrinhoComprado.getId_cliente());

        Map<String, Object> nota = new HashMap<>();

        nota.put("data", carrinhoComprado.getData_compra());
        nota.put("precoTotal", precoTotal);
        nota.put("puzzles", contemPuzzles);
        nota.put("cliente", cliente);

        return nota;
    }

    @GetMapping("/atuais/{id}")
    public List<CarrinhoContemPuzzle> produtoAtual(@PathVariable Integer id) throws SQLException {
        try {
            CarrinhoAtual carrinho = connectionHandler.getCarrinhoAtualDAO().read(id);
            return connectionHandler.getCarrinhoContemPuzzleDAO().allByCarrinho(id);
        } catch (SQLException e) {
            connectionHandler.rollbackTransaction();
            connectionHandler.endTransaction();
            throw e;
        }
    }

    @GetMapping("/comprados")
    public List<CarrinhoComprado> allComprados() throws SQLException {
        return connectionHandler.getCarrinhoCompradoDAO().all();
    }

    @PutMapping("/{id_carrinho}/puzzles/{nome_puzzle}")
    public void adicionarPuzzle(@PathVariable Integer id_carrinho, @PathVariable String nome_puzzle)
            throws SQLException {
        CarrinhoContemPuzzleDAO contemPuzzleDAO = connectionHandler.getCarrinhoContemPuzzleDAO();

        // só é possível alterar quantidades de puzzles em carrinhos atuais
        CarrinhoAtual carrinho = connectionHandler.getCarrinhoAtualDAO().read(id_carrinho);
        Puzzle puzzle = connectionHandler.getPuzzleDAO().read(nome_puzzle);
        ChaveCarrinhoPuzzle chave = new ChaveCarrinhoPuzzle(id_carrinho, nome_puzzle);

        CarrinhoContemPuzzle contemPuzzle;
        try {
            contemPuzzle = contemPuzzleDAO.read(chave);
            if (contemPuzzle.getPreco() != puzzle.getPreco()) {
                contemPuzzle.setPreco(puzzle.getPreco());
            }
            contemPuzzle.add();
            contemPuzzleDAO.update(chave, contemPuzzle);
        } catch (SQLException e) {
            if (e.getMessage().contains("não encontrado")) {
                contemPuzzle = new CarrinhoContemPuzzle(id_carrinho, nome_puzzle, 1, puzzle.getPreco());
                contemPuzzleDAO.create(contemPuzzle);
            } else {
                throw e;
            }
        }
    }

    @DeleteMapping("/{id_carrinho}/puzzles/{nome_puzzle}")
    public void removerPuzzle(@PathVariable Integer id_carrinho, @PathVariable String nome_puzzle) throws SQLException {
        CarrinhoContemPuzzleDAO contemPuzzleDAO = connectionHandler.getCarrinhoContemPuzzleDAO();

        // só é possível alterar quantidades de puzzles em carrinhos atuais
        CarrinhoAtual carrinho = connectionHandler.getCarrinhoAtualDAO().read(id_carrinho);
        Puzzle puzzle = connectionHandler.getPuzzleDAO().read(nome_puzzle);
        ChaveCarrinhoPuzzle chave = new ChaveCarrinhoPuzzle(id_carrinho, nome_puzzle);

        CarrinhoContemPuzzle contemPuzzle = contemPuzzleDAO.read(chave);

        if (contemPuzzle.getQuantidade() == 1) {
            contemPuzzleDAO.delete(chave);
        } else {
            if (contemPuzzle.getPreco() != puzzle.getPreco()) {
                contemPuzzle.setPreco(puzzle.getPreco());
            }
            contemPuzzle.sub();
            contemPuzzleDAO.update(chave, contemPuzzle);
        }
    }
}
