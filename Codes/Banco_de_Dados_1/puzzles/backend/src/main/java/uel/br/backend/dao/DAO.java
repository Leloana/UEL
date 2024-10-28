package uel.br.backend.dao;

import java.sql.SQLException;
import java.util.List;

import org.springframework.stereotype.Component;

@Component
public interface DAO<T, PK> {
    //POST
    public PK create(T t) throws SQLException;
    //GET
    public T read(PK key) throws SQLException;
    //POST
    public void update(PK old_key, T t) throws SQLException;
    //DELETE
    public void delete(PK key) throws SQLException;
    //GET
    public List<T> all() throws SQLException;

}
