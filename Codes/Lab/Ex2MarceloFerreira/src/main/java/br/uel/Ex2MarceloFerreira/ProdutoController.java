package br.uel.Ex2MarceloFerreira;


import jakarta.validation.Valid;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;


@Controller
public class ProdutoController {
    @Autowired
    ProdutoRepository produtoRepository;

    @GetMapping("/novo-produto")
    public String mostrarFormNovoProduto(Produto produto){
        return "/novo-produto";
    }
    @GetMapping(value={"/index", "/"})
    public String mostrarListaProdutos(Model model) {
        model.addAttribute("produtos", produtoRepository.findAll());
        return "/index";
    }

    @PostMapping("/adicionar-produto")
    public String adicionarProduto(@Valid Produto produto,
                                   BindingResult result) {
        if (result.hasErrors()) {
            return "/novo-produto";
        }
        produtoRepository.save(produto);
        return "redirect:/index";
    }
    @GetMapping("/editar/{id}")
    public String mostrarFormAtualizar(@PathVariable("id") int id, Model model) {
        Produto produto = produtoRepository.findById(id)
                .orElseThrow(() -> new IllegalArgumentException("O id do produto é inválido:" + id));


        model.addAttribute("produto", produto);
        return "atualizar-produto";
    }
    @PostMapping("/atualizar/{id}")
    public String atualizarProduto(@PathVariable("id") int id, @Valid Produto produto,BindingResult result, Model model) {
        if (result.hasErrors()) {
            produto.setId(id);
            return "atualizar-produto";
        }

        produtoRepository.save(produto);
        return "redirect:/index";
    }
    @GetMapping("/remover/{id}")
    public String removerProduto(@PathVariable("id") int id) {
        Produto produto = produtoRepository.findById(id)
                .orElseThrow(() -> new IllegalArgumentException("O id do contato é inválido:" + id));
        produtoRepository.delete(produto);
        return "redirect:/index";
    }

}
