package br.uel.Prova1ConsumidorMarceloFerreira;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;

import java.util.List;

@Controller
public class RestauranteController {
    @Autowired
    RestauranteRepository restauranteRepository;
    @Autowired
    ItemCardapioRepository itemCardapioRepository;

    @GetMapping(value={"/index", "/"})
    public String mostrarListaRestaurantes(Model model) {
        model.addAttribute("restaurantes", restauranteRepository.findAll());
        return "/index";
    }
    @GetMapping("/ver-cardapio/{id}")
    public String acessarCardapio(@PathVariable("id") int id, Model model) {
        Restaurante restaurante = restauranteRepository.findById(id).orElse(null);
        if (restaurante == null) {
            return "redirect:/index";
        }
        model.addAttribute("restaurante", restaurante);


        List<ItemCardapio> itensCardapio = itemCardapioRepository.findByRestauranteId(restaurante.getId());
        model.addAttribute("itensCardapio", itensCardapio);

        return "cardapio";
    }
}
