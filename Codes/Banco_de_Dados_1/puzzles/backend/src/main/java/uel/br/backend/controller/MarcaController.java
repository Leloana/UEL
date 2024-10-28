package uel.br.backend.controller;

import java.sql.SQLException;
import java.util.List;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.*;
import uel.br.backend.jdbc.ConnectionHandler;

import uel.br.backend.model.Marca;

@RestController
@RequestMapping("/marcas")
public class MarcaController {

    @Autowired
    ConnectionHandler connectionHandler;

    @PostMapping
    public void create(@RequestBody Marca marca) throws SQLException {
        connectionHandler.getMarcaDAO().create(marca);
    }

    @GetMapping("/{nome}")
    public Marca read(@PathVariable String nome) throws SQLException {
        return connectionHandler.getMarcaDAO().read(nome);
    }

    @PutMapping("/{nome_antigo}")
    public void update(@PathVariable String nome_antigo, @RequestBody Marca marca) throws SQLException {
        connectionHandler.getMarcaDAO().update(nome_antigo, marca);
    }

    @DeleteMapping("/{id}")
    public void delete(@PathVariable String nome) throws SQLException {
        connectionHandler.getMarcaDAO().delete(nome);
    }

    @GetMapping
    public List<Marca> all() throws SQLException {
        return connectionHandler.getMarcaDAO().all();
    }
}
