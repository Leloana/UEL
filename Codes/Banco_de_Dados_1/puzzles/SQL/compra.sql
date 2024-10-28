--SIMULANDO INICIO COMPRA

--INSERINDO CARRINHO
WITH last_id AS (
--RECUPERANDO ULTIMO ID GERADO PELA SERIE
    INSERT INTO loja.carrinho DEFAULT VALUES RETURNING id
)
--INSERINDO CARRINHO ATUAL USANDO ID DO CARRINHO CRIADO
INSERT INTO loja.carrinho_atual (id_carrinho) VALUES ((SELECT id FROM last_id));

--INSERINDO CLIENTE USANDO ID DO CARRINHO ATUAL
INSERT INTO loja.cliente (login, senha, data_criacao, id_carrinho_atual) VALUES ('puzzle', md5('puzzle'), CURRENT_DATE, (SELECT currval(pg_get_serial_sequence('loja.carrinho', 'id'))));

--INSERINDO CUBO AO CARRINHO ATUAL
WITH cliente AS (
    SELECT * FROM loja.cliente WHERE login = 'puzzle'
)
INSERT INTO loja.carrinho_contem_puzzle (id_carrinho, nome_puzzle, quantidade, preco)
VALUES ((SELECT id_carrinho_atual FROM cliente), 'Rubik''s 2x2 Cube', 3, (SELECT preco FROM loja.puzzle WHERE nome = 'Rubik''s 2x2 Cube'));

--INSERINDO CUBO AO CARRINHO ATUAL
WITH cliente AS (
    SELECT * FROM loja.cliente WHERE login = 'puzzle'
)
INSERT INTO loja.carrinho_contem_puzzle (id_carrinho, nome_puzzle, quantidade, preco)
VALUES ((SELECT id_carrinho_atual FROM cliente), 'GAN251 M Pro', 1, (SELECT preco FROM loja.puzzle WHERE nome = 'GAN251 M Pro'));

--INSERINDO CUBO AO CARRINHO ATUAL
WITH cliente AS (
    SELECT * FROM loja.cliente WHERE login = 'puzzle'
)
INSERT INTO loja.carrinho_contem_puzzle (id_carrinho, nome_puzzle, quantidade, preco)
VALUES ((SELECT id_carrinho_atual FROM cliente), 'MoYu RS3 M 2020 3x3', 5, (SELECT preco FROM loja.puzzle WHERE nome = 'MoYu RS3 M 2020 3x3'));

--ATUALIZANDO QUANTIDADE DO 'GAN251 M Pro' PARA O CLIENTE 1981
WITH cliente AS (
    SELECT * FROM loja.cliente WHERE login = 'puzzle'
)
UPDATE loja.carrinho_contem_puzzle SET quantidade = 2 
    WHERE id_carrinho = (SELECT id_carrinho_atual FROM cliente) AND nome_puzzle = 'GAN251 M Pro';

--SIMULANDO COMPRA FINALIZADA
WITH cliente AS (
    SELECT * FROM loja.cliente WHERE login = 'puzzle'
)
INSERT INTO loja.carrinho_comprado (id_carrinho,data_compra,id_cliente)
    VALUES ((SELECT id_carrinho_atual FROM cliente), CURRENT_DATE,(SELECT id FROM cliente));

WITH last_id AS (
--RECUPERANDO ULTIMO ID GERADO PELA SERIE
    INSERT INTO loja.carrinho DEFAULT VALUES RETURNING id
),
cliente AS (
    SELECT * FROM loja.cliente WHERE login = 'puzzle'
)
--INSERINDO CARRINHO ATUAL USANDO ID DO CARRINHO CRIADO
UPDATE loja.carrinho_atual SET id_carrinho = (SELECT id FROM last_id) WHERE id_carrinho = (SELECT id_carrinho_atual FROM cliente);
