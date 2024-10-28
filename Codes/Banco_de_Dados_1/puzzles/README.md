Loja virtual de puzzles giratórios mecânicos, as informações dos puzzles são nome,preço,quantidade em estoque, as imagens deles e  palavras-chaves que os identificam, a loja conterá alguns tipos de puzzles que serão cubos mágicos(Rubik's Cube) 2x2x2, 3x3x3 e 4x4x4, os cubos poderão ou não ter adesivos, além do cubo mágico a loja conterá os puzzles piraminxs e clocks.Cada puzzle conterá uma marca, sendo que essa marca poderá ser de vários puzzles, da marca guardaremos o nome.

A loja será acessada por um cliente, dele guardaremos a sessão. O cliente terá, ao entrar, um carrinho, que possui um id e o carrinho conterá puzzles escolhidos pelo cliente, sendo que ao ser adicionado mais de uma vez o mesmo puzzle no carrinho deve-se aumentar a quantidade daquele puzzle no carrinho. Ao ser finalizada a compra o carrinho que o cliente fez as compras deverá ser registrado guardando a data da compra e após isso um novo carrinho deverá ser atribuído ao cliente, para que ele inicie uma nova compra.

A loja deverá conter um admin que adicionará os produtos, um admin poderá adicionar vários produtos e marcas. Do admin será guardado o login e a senha para ser usada na autenticação.

Foi utilizado o software [Erdplus](https://erdplus.com/standalone) para os modelos entidade-relacionamento e relacional.

Relatórios importantes:
- Vendas por puzzle
- Vendas por marca
- Vendas por faixa de preço
- Vendas por categoria (cubo 2x2, cubo 3x3, cubo 4x4, piraminx, clock)
- Compras por usuário
- Tempo para a primeira compra de usuário
- Quantidade de categorias compradas por usuário
- Tempo médio entre compra de categoria por usuário

