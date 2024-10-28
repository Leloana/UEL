package uel.br.backend.controller;

import java.sql.SQLException;
import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import uel.br.backend.jdbc.ConnectionHandler;
import uel.br.backend.model.ChavePalavraChave;
import uel.br.backend.model.PalavraChave;

@RestController
@RequestMapping("/palavras-chave")
public class PalavraChaveController {

    @Autowired
    ConnectionHandler connectionHandler;

    @PostMapping
    public void create(@RequestBody PalavraChave palavra_chave) throws SQLException {
        connectionHandler.getPalavraChaveDAO().create(palavra_chave);
    }

    @GetMapping("/{nome_puzzle}/{palavra}")
    public PalavraChave read(@PathVariable String nome_puzzle, @PathVariable String palavra) throws SQLException {
        return connectionHandler.getPalavraChaveDAO().read(new ChavePalavraChave(palavra, nome_puzzle));
    }

    @PutMapping("/{nome_puzzle}/{palavra}")
    public void update(@PathVariable String nome_puzzle, @PathVariable String palavra,
            @RequestBody PalavraChave palavra_chave)
            throws SQLException {
        connectionHandler.getPalavraChaveDAO().update(new ChavePalavraChave(palavra, nome_puzzle), palavra_chave);
    }

    @DeleteMapping("/{nome_puzzle}/{palavra}")
    public void delete(@PathVariable String nome_puzzle, @PathVariable String palavra) throws SQLException {
        connectionHandler.getPalavraChaveDAO().delete(new ChavePalavraChave(palavra, nome_puzzle));
    }

    @GetMapping
    public List<PalavraChave> all() throws SQLException {
        return connectionHandler.getPalavraChaveDAO().all();
    }
}
