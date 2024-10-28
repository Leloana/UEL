package br.uel.Prova1AdminMarceloFerreira;

import jakarta.validation.Valid;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;

import java.util.List;

@Controller
public class RestauranteController {
    @Autowired
    RestauranteRepository restauranteRepository;
    @Autowired
    ItemCardapioRepository itemCardapioRepository;

    @GetMapping("/novo-restaurante")
    public String mostrarFormNovoRestaurante(Restaurante restaurante){
        return "/novo-restaurante";
    }
    @GetMapping(value={"/index", "/"})
    public String mostrarListaRestaurantes(Model model) {
        model.addAttribute("restaurantes", restauranteRepository.findAll());
        return "/index";
    }

    @PostMapping("/adicionar-restaurante")
    public String adicionarRestaurante(@Valid Restaurante restaurante,
                                   BindingResult result) {
        if (result.hasErrors()) {
            return "/novo-restaurante";
        }
        restauranteRepository.save(restaurante);
        return "redirect:/index";
    }
    @GetMapping("/editar/{id}")
    public String mostrarFormAtualizar(@PathVariable("id") int id, Model model) {
        Restaurante restaurante = restauranteRepository.findById(id)
                .orElse(null); // Retorna null se o restaurante não for encontrado
        if (restaurante == null) {
            // Se o restaurante não existe, redirecione para a página inicial ou faça outra ação apropriada
            return "redirect:/index";
        }

        model.addAttribute("restaurante", restaurante);
        return "atualizar-restaurante";
    }
    @PostMapping("/atualizar/{id}")
    public String atualizarRestaurante(@PathVariable("id") int id, @Valid Restaurante restaurante, BindingResult result, Model model) {
        if (result.hasErrors()) {
            restaurante.setId(id);
            model.addAttribute("restaurante", restaurante);
            return "atualizar-restaurante";
        }

        // Carregar o restaurante original do banco de dados
        Restaurante restauranteOriginal = restauranteRepository.findById(id)
                .orElseThrow(() -> new IllegalArgumentException("O id do restaurante é inválido:" + id));

        // Atualizar apenas os campos necessários do restaurante original
        restauranteOriginal.setNome(restaurante.getNome());
        // Atualize outras propriedades conforme necessário

        // Salvar o restaurante original atualizado
        restauranteRepository.save(restauranteOriginal);

        return "redirect:/index";
    }

    @GetMapping("/remover/{id}")
    public String removerRestaurante(@PathVariable("id") int id) {
        Restaurante restaurante = restauranteRepository.findById(id)
                .orElseThrow(() -> new IllegalArgumentException("O id do restaurante é inválido:" + id));
        restauranteRepository.delete(restaurante);
        return "redirect:/index";
    }
    @GetMapping("/ver-cardapio/{id}")
    public String acessarCardapio(@PathVariable("id") int id, Model model) {
        Restaurante restaurante = restauranteRepository.findById(id)
                .orElseThrow(() -> new IllegalArgumentException("O id do restaurante é inválido:" + id));
        model.addAttribute("restaurante", restaurante);

        if (restaurante == null) {
            return "redirect:/index";
        }
        List<ItemCardapio> itensCardapio = itemCardapioRepository.findByRestauranteId(restaurante.getId());
        model.addAttribute("itensCardapio", itensCardapio);

        return "cardapio";
    }
}
