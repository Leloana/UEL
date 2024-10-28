package uel.br.backend.mapper;

import java.lang.reflect.Field;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.logging.Level;
import java.util.logging.Logger;

import org.springframework.jdbc.core.RowMapper;

import jakarta.persistence.Table;
import uel.br.backend.annotation.Password;

public class TableMapper<T> implements RowMapper<T> {
    private final Class<T> classe;

    public TableMapper(Class<T> classe) {
        this.classe = classe;
    }

    @Override
    public T mapRow(ResultSet rs, int rowNum) throws SQLException {
        if (!classe.isAnnotationPresent(Table.class)) {
            throw new SQLException(classe.getName() + " is not a table.");
        }

        try {
            T obj = classe.getDeclaredConstructor().newInstance();
            for (Field field : classe.getDeclaredFields()) {
                if (field.isAnnotationPresent(Password.class)) {
                    continue;
                }
                field.setAccessible(true);
                field.set(obj, rs.getObject(field.getName()));
            }
            return obj;
        } catch (Exception e) {
            Logger.getLogger(TableMapper.class.getName()).log(Level.SEVERE, "mapRow", e);
            throw new SQLException(e);
        }

    }

}
