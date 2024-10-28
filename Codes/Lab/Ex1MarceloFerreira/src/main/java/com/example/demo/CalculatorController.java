package com.example.demo;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;

@Controller
public class CalculatorController {

    @GetMapping("/calculator")
    public String showCalculatorForm(Model model){

        model.addAttribute("calculator", new Calculator());
        return "calculator";

    }

    @PostMapping("/calculator")
    public String calculate(@RequestParam(name = "operation") String operation,Calculator calculator, Model model){

        int result = 0;

        switch(operation) {
            case "add":
                result = calculator.getNum1() + calculator.getNum2();
                break;
            case "subtract":
                result = calculator.getNum1() - calculator.getNum2();
                break;
            case "multiply":
                result = calculator.getNum1() * calculator.getNum2();
                break;
            case "divide":
                if (calculator.getNum2() != 0) {
                    result = calculator.getNum1() / calculator.getNum2();
                } else {
                    model.addAttribute("error", "Cannot divide by zero!");
                    return "calculator";
                }
                break;
        }

        model.addAttribute("result", result);
        return "calculator";
    }

}