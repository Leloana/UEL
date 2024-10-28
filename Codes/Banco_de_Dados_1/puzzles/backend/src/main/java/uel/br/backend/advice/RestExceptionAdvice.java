package uel.br.backend.advice;

import java.sql.SQLException;

import org.springframework.http.HttpStatus;
import org.springframework.http.HttpStatusCode;
import org.springframework.http.ProblemDetail;
import org.springframework.web.ErrorResponse;
import org.springframework.web.ErrorResponseException;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.RestControllerAdvice;

@RestControllerAdvice
public class RestExceptionAdvice {

    @ExceptionHandler(SQLException.class)
    public ErrorResponse handleSQLException(SQLException exception) {
        HttpStatusCode status = HttpStatus.INTERNAL_SERVER_ERROR;
        if (exception.getMessage().contains("não encontrado")) {
            status = HttpStatus.NOT_FOUND;
        }
        ProblemDetail detail = ProblemDetail.forStatusAndDetail(status, exception.getMessage());
        return new ErrorResponseException(status, detail, exception);
    }

}
