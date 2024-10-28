package uel.br.backend.controller;

import java.sql.SQLException;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import uel.br.backend.jdbc.ConnectionHandler;

import uel.br.backend.model.Clock;
import uel.br.backend.model.Puzzle;

@RestController
@RequestMapping("/clock")
public class ClockController {

    @Autowired
    ConnectionHandler connectionHandler;

    @PostMapping
    public void create(@RequestBody Puzzle puzzle) throws SQLException {
        connectionHandler.beginTransaction();
        try {
            puzzle.setTipo("clock");
            String puzzleName = connectionHandler.getPuzzleDAO().create(puzzle);
            Clock clock = new Clock(puzzleName);
            connectionHandler.getClockDAO().create(clock);
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
    public Clock read(@PathVariable String nome) throws SQLException {
        return connectionHandler.getClockDAO().read(nome);
    }

    @PutMapping("/{nome_antigo}")
    public void update(@PathVariable String nome_antigo, @RequestBody Clock clock) throws SQLException {
        connectionHandler.getClockDAO().update(nome_antigo, clock);
    }

    @DeleteMapping("/{nome}")
    public void delete(@PathVariable String nome) throws SQLException {
        connectionHandler.getClockDAO().delete(nome);
    }

    @GetMapping
    public List<Clock> all() throws SQLException {
        return connectionHandler.getClockDAO().all();
    }
}
