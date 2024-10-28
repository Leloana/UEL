package com.example.aula2;

import java.io.*;

import jakarta.servlet.http.*;
import jakarta.servlet.annotation.*;

@WebServlet(name = "helloServlet", value = "/hello-servlet")
public class HelloServlet extends HttpServlet {
    private String message;

    public void init() {
        message = "Hello World!";
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setContentType("text/html");
        String numero = request.getParameter("num");

        Integer Fib = calcularFibonacci(Integer.parseInt(numero));

        // Hello
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h1>" + Fib + "</h1>");
        out.println("</body></html>");
    }

    public static int calcularFibonacci(int n) {
        if (n <= 1) {
            return n;
        } else {
            int a = 0;
            int b = 1;
            int resultado = 0;

            for (int i = 2; i <= n; i++) {
                resultado = a + b;
                a = b;
                b = resultado;
            }

            return resultado;
        }
    }

    public void destroy() {
    }
}