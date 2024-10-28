package uel.br.backend.controller;

import java.sql.SQLException;
import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import uel.br.backend.jdbc.ConnectionHandler;

import uel.br.backend.model.ChaveImagem;
import uel.br.backend.model.Imagem;

@RestController
@RequestMapping("/imagens")
public class ImagemController {

    @Autowired
    ConnectionHandler connectionHandler;

    @PostMapping
    public void create(@RequestBody Imagem imagem) throws SQLException {
        connectionHandler.getImagemDAO().create(imagem);
    }

    @GetMapping("/{nome_puzzle}/{imagem}")
    public Imagem read(@PathVariable String nome_puzzle, @PathVariable String imagem) throws SQLException {
        return connectionHandler.getImagemDAO().read(new ChaveImagem(imagem, nome_puzzle));
    }

    @PutMapping("/{nome_puzzle}/{imagem}")
    public void update(@PathVariable String nome_puzzle, @PathVariable String imagem, @RequestBody Imagem novaImagem)
            throws SQLException {
        connectionHandler.getImagemDAO().update(new ChaveImagem(imagem, nome_puzzle), novaImagem);
    }

    @DeleteMapping("/{nome_puzzle}/{imagem}")
    public void delete(@PathVariable String nome_puzzle, @PathVariable String imagem) throws SQLException {
        connectionHandler.getImagemDAO().delete(new ChaveImagem(imagem, nome_puzzle));
    }

    @GetMapping
    public List<Imagem> all() throws SQLException {
        return connectionHandler.getImagemDAO().all();
    }
}
