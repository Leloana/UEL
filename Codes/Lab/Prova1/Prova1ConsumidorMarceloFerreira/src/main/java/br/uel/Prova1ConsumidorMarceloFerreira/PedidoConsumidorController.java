package br.uel.Prova1ConsumidorMarceloFerreira;

import jakarta.servlet.http.HttpServletRequest;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.util.CollectionUtils;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;

import java.util.ArrayList;
import java.util.List;

@Controller
public class PedidoConsumidorController {
    private static final String SESSION_FAVORITOS = "sessionFavoritos";
    @Autowired
    RestauranteRepository restauranteRepository;
    @Autowired
    ItemCardapioRepository itemCardapioRepository;

    @GetMapping("/pedir/{id}")
    public String pedirItem(@PathVariable("id") int id,
                                   HttpServletRequest request){
        ItemCardapio itemCardapio = itemCardapioRepository.findById(id).orElse(null);
        if(itemCardapio == null){
            return "redirect:/index";
        }
        PedidoConsumidor pedido = new PedidoConsumidor();
        pedido.setItem(itemCardapio);
        pedido.setQuantidade(1);
        pedido.setId(id);

        List<PedidoConsumidor> carrinho = (List<PedidoConsumidor>)
                request.getSession().getAttribute(SESSION_FAVORITOS);

        if (CollectionUtils.isEmpty(carrinho)) {
            carrinho = new ArrayList<>();
        }

        boolean itemJaNoCarrinho = false;

        for (PedidoConsumidor pedidoCarrinho : carrinho) {
            int idItemCarrinho = pedidoCarrinho.getId();
            if (idItemCarrinho == id) {
                pedidoCarrinho.setQuantidade(pedidoCarrinho.getQuantidade()+1);
                itemJaNoCarrinho = true;
                break;
            }
        }
        if(!itemJaNoCarrinho){
            carrinho.add(pedido);
        }
        request.getSession().setAttribute(SESSION_FAVORITOS, carrinho);

        return "redirect:/pedidos";
    }
    @GetMapping(value={"/pedidos"})
    public String mostrarListaPedidos(Model model, HttpServletRequest request) {
        List<PedidoConsumidor> carrinho = (List<PedidoConsumidor>) request.getSession().getAttribute(SESSION_FAVORITOS);
        double newValue = 0.0;
        //INICIAR O CARRINHO CASO ELE NAO EXISTA
        if (carrinho == null) {
            carrinho = new ArrayList<>();
        }

        // CRIA UMA COPIA DO CARRINHO PARA PERCORRER LOOP(EM CASO DE REMOÇÃO NAO DAR ERRO)
        List<PedidoConsumidor> carrinhoAtualizado = new ArrayList<>(carrinho);
        //LOOP PARA ATUALIZAR O PEDIDO EM CASO DE MUDANCA NO BANCO DE DADOS
        for (PedidoConsumidor pedidoCarrinho : carrinhoAtualizado) {
            int idItemCarrinho = pedidoCarrinho.getId();
            ItemCardapio itemAtual = itemCardapioRepository.findById(idItemCarrinho).orElse(null);
            if (itemAtual == null) {
                // Se o item não existe mais no banco de dados, remova-o da lista de pedidos
                carrinho.remove(pedidoCarrinho);
            } else {
                //ATUALIZA INFORMAÇÕES PARA QUE O PEDIDO SEJA IGUAL AO BANCO DE DADOS
                pedidoCarrinho.getItem().setPreco(itemAtual.getPreco());
                pedidoCarrinho.getItem().setDescricao(itemAtual.getDescricao());
                pedidoCarrinho.getItem().setNome(itemAtual.getNome());
                newValue += pedidoCarrinho.getQuantidade() * pedidoCarrinho.getItem().getPreco();
            }
        }

        model.addAttribute("valorTotal", newValue);
        model.addAttribute("itensPedidos", carrinho);
        return "/pedidos";
    }

    @GetMapping("/aumentar-pedido/{id}")
    public String aumentarItem(@PathVariable("id") int id,
                            HttpServletRequest request) {
        List<PedidoConsumidor> carrinho = (List<PedidoConsumidor>)
                request.getSession().getAttribute(SESSION_FAVORITOS);

        for (PedidoConsumidor pedidoCarrinho : carrinho) {
            if (pedidoCarrinho.getId() == id) {
                pedidoCarrinho.setQuantidade(pedidoCarrinho.getQuantidade()+1);
                break;
            }
        }
        request.getSession().setAttribute(SESSION_FAVORITOS, carrinho);
        return "redirect:/pedidos";
    }

    @GetMapping("/diminuir-pedido/{id}")
    public String diminuirItem(@PathVariable("id") int id,
                               HttpServletRequest request) {
        List<PedidoConsumidor> carrinho = (List<PedidoConsumidor>)
                request.getSession().getAttribute(SESSION_FAVORITOS);

        for (PedidoConsumidor pedidoCarrinho : carrinho) {
            if (pedidoCarrinho.getId() == id) {
                pedidoCarrinho.setQuantidade(pedidoCarrinho.getQuantidade()-1);
                if(pedidoCarrinho.getQuantidade() == 0){
                    carrinho.remove(pedidoCarrinho);
                }
                break;
            }
        }
        request.getSession().setAttribute(SESSION_FAVORITOS, carrinho);
        return "redirect:/pedidos";
    }

}
