package uel.br.backend.controller;

import java.sql.SQLException;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import uel.br.backend.jdbc.ConnectionHandler;

import uel.br.backend.model.Piraminx;
import uel.br.backend.model.Puzzle;

@RestController
@RequestMapping("/piraminx")
public class PiraminxController {

    @Autowired
    ConnectionHandler connectionHandler;

    @PostMapping
    public void create(@RequestBody Puzzle puzzle) throws SQLException {
        connectionHandler.beginTransaction();
        try {
            puzzle.setTipo("piraminx");
            String puzzleName = connectionHandler.getPuzzleDAO().create(puzzle);
            Piraminx piraminx = new Piraminx(puzzleName);
            connectionHandler.getPiraminxDAO().create(piraminx);
            connectionHandler.commitTransaction();
        } catch (SQLException e) {
            Logger.getLogger(PuzzleController.class.getName()).log(Level.SEVERE, "Controller", e);
            connectionHandler.rollbackTransaction();
            throw e;
        } finally {
            connectionHandler.endTransaction();
        }
    }

    @GetMapping("/{nome}")
    public Piraminx read(@PathVariable String nome) throws SQLException {
        return connectionHandler.getPiraminxDAO().read(nome);
    }

    @PutMapping("/{nome_antigo}")
    public void update(@PathVariable String nome_antigo, @RequestBody Piraminx piraminx) throws SQLException {
        connectionHandler.getPiraminxDAO().update(nome_antigo, piraminx);
    }

    @DeleteMapping("/{nome}")
    public void delete(@PathVariable String nome) throws SQLException {
        connectionHandler.getPiraminxDAO().delete(nome);
    }

    @GetMapping
    public List<Piraminx> all() throws SQLException {
        return connectionHandler.getPiraminxDAO().all();
    }
}
