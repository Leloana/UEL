package uel.br.backend.controller;

import java.sql.Date;
import java.sql.SQLException;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.servlet.ModelAndView;
import org.springframework.web.servlet.view.RedirectView;

import uel.br.backend.dao.CarrinhoAtualDAO;
import uel.br.backend.dao.CarrinhoCompradoDAO;
import uel.br.backend.dao.CarrinhoDAO;
import uel.br.backend.dao.ClienteDAO;
import uel.br.backend.jdbc.ConnectionHandler;
import uel.br.backend.model.Carrinho;
import uel.br.backend.model.CarrinhoAtual;
import uel.br.backend.model.CarrinhoComprado;
import uel.br.backend.model.Cliente;

@RestController
@RequestMapping("/clientes")
public class ClienteController {

    @Autowired
    ConnectionHandler connectionHandler;

    @PostMapping
    public Cliente create(@RequestBody Cliente cliente) throws SQLException {
        connectionHandler.beginTransaction();

        try {
            Integer id_carrinho = connectionHandler.getCarrinhoDAO().create(new Carrinho());
            connectionHandler.getCarrinhoAtualDAO().create(new CarrinhoAtual(id_carrinho));
            cliente.setId_carrinho_atual(id_carrinho);
            cliente.setData_criacao(new Date(System.currentTimeMillis()));
            Integer id_cliente = connectionHandler.getClienteDAO().create(cliente);
            cliente.setId(id_cliente);
            cliente.setSenha("");
            connectionHandler.commitTransaction();
            connectionHandler.endTransaction();
            return cliente;
        } catch (SQLException e) {
            connectionHandler.rollbackTransaction();
            connectionHandler.endTransaction();
            throw e;
        }

    }

    @GetMapping("/autenticacao")
    public Cliente authenticate(@RequestBody Cliente cliente) throws SQLException {

        Cliente autenticado = connectionHandler.getClienteDAO().authenticate(cliente.getLogin(),
                cliente.getSenha());
        return autenticado;

    }

    @GetMapping("/{id}")
    public Cliente read(@PathVariable Integer id) throws SQLException {
        return connectionHandler.getClienteDAO().read(id);
    }

    @PutMapping("/{id_antigo}")
    public void update(@PathVariable Integer id_antigo, @RequestBody Cliente cliente) throws SQLException {
        connectionHandler.getClienteDAO().update(id_antigo, cliente);
    }

    @DeleteMapping("/{id}")
    public void delete(@PathVariable Integer id) throws SQLException {
        connectionHandler.getClienteDAO().delete(id);
    }

    @GetMapping
    public List<Cliente> all() throws SQLException {
        return connectionHandler.getClienteDAO().all();
    }

    @PutMapping("/compra/{id}")
    public ModelAndView finalizarCompra(@PathVariable Integer id, @RequestBody Date date) throws SQLException {
        connectionHandler.beginTransaction();

        try {
            ClienteDAO clienteDAO = connectionHandler.getClienteDAO();
            CarrinhoDAO carrinhoDAO = connectionHandler.getCarrinhoDAO();
            CarrinhoAtualDAO carrinhoAtualDAO = connectionHandler.getCarrinhoAtualDAO();
            CarrinhoCompradoDAO carrinhoCompradoDAO = connectionHandler.getCarrinhoCompradoDAO();

            Cliente cliente = clienteDAO.read(id);
            CarrinhoAtual carrinhoAtual = carrinhoAtualDAO.read(cliente.getId_carrinho_atual());

            CarrinhoComprado carrinhoComprado = new CarrinhoComprado(carrinhoAtual.getId_carrinho(),
                    date == null ? new Date(System.currentTimeMillis()) : date,
                    cliente.getId());

            carrinhoCompradoDAO.create(carrinhoComprado);
            Integer novoCarrinho = carrinhoDAO.create(new Carrinho());

            carrinhoAtualDAO.update(carrinhoAtual.getId_carrinho(), new CarrinhoAtual(novoCarrinho));
            connectionHandler.commitTransaction();
            connectionHandler.endTransaction();

            return new ModelAndView("redirect:/carrinhos/comprados/nota-fiscal/" + carrinhoComprado.getId_carrinho());
        } catch (SQLException e) {
            Logger.getLogger(ClienteController.class.getName()).log(Level.SEVERE, "Controller", e);
            connectionHandler.rollbackTransaction();
            connectionHandler.endTransaction();
            throw e;
        }

    }

}
