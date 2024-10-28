package br.uel.Prova1AdminMarceloFerreira;

import jakarta.validation.Valid;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;

import java.util.List;

@Controller
public class ItemCardapioController {
    @Autowired
    ItemCardapioRepository itemCardapioRepository;
    @Autowired
    RestauranteRepository restauranteRepository;

    @GetMapping("/novo-itemCardapio")
    public String mostrarFormNovoItemCardapio(@RequestParam("restauranteId") int restauranteId, Model model){
        Restaurante restaurante = restauranteRepository.findById(restauranteId)
                .orElseThrow(() -> new IllegalArgumentException("O id do item é inválido:" + restauranteId));
        model.addAttribute("restaurante", restaurante);
        ItemCardapio itemCardapio = new ItemCardapio();
        model.addAttribute("itemCardapio", itemCardapio);
        itemCardapio.setRestaurante(restaurante);
        return "/novo-itemCardapio";
    }
    @PostMapping("/adicionar-item")
    public String adicionarItemCardapio(@Valid ItemCardapio itemCardapio,
                                        BindingResult result) {
        if (result.hasErrors()) {
            return "/novo-itemCardapio";
        }
        System.out.println("EBA");
        itemCardapioRepository.save(itemCardapio);
        System.out.println("TESTE");
        return "redirect:/ver-cardapio/" + itemCardapio.getRestaurante().getId();
    }

    @GetMapping("/editar-item/{id}")
    public String mostrarFormAtualizarItem(@PathVariable("id") int id, Model model) {
        ItemCardapio itemCardapio = itemCardapioRepository.findById(id)
                .orElseThrow(() -> new IllegalArgumentException("O id do item é inválido:" + id));


        model.addAttribute("itemCardapio", itemCardapio);
        return "atualizar-itemCardapio";
    }
    @PostMapping("/atualizar-item/{id}")
    public String atualizarItem(@PathVariable("id") int id, @Valid ItemCardapio itemCardapio,BindingResult result, Model model) {
        if (result.hasErrors()) {
            itemCardapio.setId(id);
            return "atualizar-itemCardapio";
        }

        itemCardapioRepository.save(itemCardapio);
        return "redirect:/ver-cardapio/" + itemCardapio.getRestaurante().getId();
    }
    @GetMapping("/remover-item/{id}")
    public String removerRestaurante(@PathVariable("id") int id) {
        ItemCardapio itemCardapio  = itemCardapioRepository.findById(id)
                .orElseThrow(() -> new IllegalArgumentException("O id do item é inválido:" + id));
        itemCardapioRepository.delete(itemCardapio);
        return "redirect:/ver-cardapio/" + itemCardapio.getRestaurante().getId();
    }
}
