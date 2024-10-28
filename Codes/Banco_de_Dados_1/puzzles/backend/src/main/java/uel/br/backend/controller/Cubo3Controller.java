package uel.br.backend.controller;

import java.sql.SQLException;
import java.util.List;
import java.util.Map;
import java.util.logging.Level;
import java.util.logging.Logger;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import com.fasterxml.jackson.databind.ObjectMapper;

import uel.br.backend.jdbc.ConnectionHandler;

import uel.br.backend.model.Cubo3;
import uel.br.backend.model.Puzzle;

@RestController
@RequestMapping("/cubo3")
public class Cubo3Controller {

    @Autowired
    ConnectionHandler connectionHandler;

    @PostMapping
    public void create(@RequestBody Map<String, Object> body) throws SQLException {
        connectionHandler.beginTransaction();

        try {
            if (body.get("puzzle") instanceof Map puzzleMap && body.get("com_adesivo") instanceof Boolean com_adesivo) {
                ObjectMapper objectMapper = new ObjectMapper();
                Puzzle puzzle = objectMapper.convertValue(puzzleMap, Puzzle.class);
                puzzle.setTipo("cubo3");
                String puzzleName = connectionHandler.getPuzzleDAO().create(puzzle);
                Cubo3 cubo3 = new Cubo3(puzzleName, com_adesivo);
                connectionHandler.getCubo3DAO().create(cubo3);
                connectionHandler.commitTransaction();
            }
        } catch (SQLException e) {
            Logger.getLogger(PuzzleController.class.getName()).log(Level.SEVERE, "Controller", e);
            connectionHandler.rollbackTransaction();
            throw e;
        } finally {
            connectionHandler.endTransaction();
        }
    }

    @GetMapping("/{nome}")
    public Cubo3 read(@PathVariable String nome) throws SQLException {
        return connectionHandler.getCubo3DAO().read(nome);
    }

    @PutMapping("/{nome_antigo}")
    public void update(@PathVariable String nome_antigo, @RequestBody Cubo3 cubo3) throws SQLException {
        connectionHandler.getCubo3DAO().update(nome_antigo, cubo3);
    }

    @DeleteMapping("/{nome}")
    public void delete(@PathVariable String nome) throws SQLException {
        connectionHandler.getCubo3DAO().delete(nome);
    }

    @GetMapping
    public List<Cubo3> all() throws SQLException {
        return connectionHandler.getCubo3DAO().all();
    }
}
