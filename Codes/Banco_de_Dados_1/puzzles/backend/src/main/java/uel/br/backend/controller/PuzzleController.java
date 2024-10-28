package uel.br.backend.controller;

import java.sql.SQLException;
import java.util.List;
import java.util.Map;
import java.util.logging.Level;
import java.util.logging.Logger;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import uel.br.backend.model.Marca;
import uel.br.backend.model.Piraminx;
import uel.br.backend.model.Puzzle;
import uel.br.backend.jdbc.ConnectionHandler;

@RestController
@RequestMapping("/puzzles")
public class PuzzleController {

    @Autowired
    ConnectionHandler connectionHandler;

    @GetMapping("/{id}")
    public Puzzle read(@PathVariable String id) throws SQLException {
        return connectionHandler.getPuzzleDAO().read(id);
    }

    @PutMapping("/{nome_antigo}")
    public void update(@PathVariable String nome_antigo, @RequestBody Puzzle puzzle) throws SQLException {
        connectionHandler.getPuzzleDAO().update(nome_antigo, puzzle);
    }

    @DeleteMapping("/{id}")
    public void delete(@PathVariable String id) throws SQLException {
        connectionHandler.getPuzzleDAO().delete(id);
    }

    @GetMapping
    public List<Puzzle> all() throws SQLException {
        return connectionHandler.getPuzzleDAO().all();
    }

}