SELECT nome_puzzle, SUM(quantidade) AS total_vendido, SUM(quantidade * preco) AS valor_total 
    FROM loja.carrinho_contem_puzzle AS ccp
        JOIN loja.carrinho_comprado AS cc ON ccp.id_carrinho = cc.id_carrinho 
        GROUP BY nome_puzzle
        ORDER BY total_vendido DESC, valor_total DESC;

SELECT p.nome_marca, SUM(ccp.quantidade) AS total_vendido, SUM(ccp.quantidade * ccp.preco) AS valor_total 
    FROM loja.carrinho_contem_puzzle AS ccp 
        JOIN loja.carrinho_comprado AS cc ON ccp.id_carrinho = cc.id_carrinho 
        JOIN loja.puzzle AS p ON ccp.nome_puzzle = p.nome 
        GROUP BY p.nome_marca
        ORDER BY total_vendido DESC, valor_total DESC;

SELECT 
    CASE 
        WHEN preco < 50 THEN '0..50' 
        WHEN preco BETWEEN 50 AND 100 THEN '50..100' 
        WHEN preco BETWEEN 100 AND 200 THEN '100..200' 
        ELSE '200..' 
    END AS faixa_preco, SUM(quantidade) AS total_vendido, SUM(quantidade * preco) AS valor_total 
        FROM loja.carrinho_contem_puzzle AS ccp 
        JOIN loja.carrinho_comprado AS cc ON ccp.id_carrinho = cc.id_carrinho 
        GROUP BY faixa_preco
        ORDER BY total_vendido DESC, valor_total DESC;

SELECT p.tipo AS categoria, SUM(ccp.quantidade) AS total_vendido, SUM(ccp.quantidade * ccp.preco) AS valor_total 
    FROM loja.carrinho_contem_puzzle AS ccp 
    JOIN loja.carrinho_comprado AS cc ON ccp.id_carrinho = cc.id_carrinho 
    JOIN loja.puzzle AS p ON ccp.nome_puzzle = p.nome 
    GROUP BY p.tipo
    ORDER BY total_vendido DESC, valor_total DESC;

SELECT cliente.id, cliente.login, COUNT(DISTINCT cc.id_carrinho) AS total_compras, COALESCE(SUM(ccp.quantidade * ccp.preco), 0) AS valor_total 
    FROM loja.cliente
    LEFT OUTER JOIN loja.carrinho_comprado AS cc ON cliente.id = cc.id_cliente
    LEFT OUTER JOIN loja.carrinho_contem_puzzle AS ccp ON cc.id_carrinho = ccp.id_carrinho
    GROUP BY cliente.id
    ORDER BY total_compras DESC, valor_total DESC;

SELECT cliente.id, cliente.login, MIN(cc.data_compra - cliente.data_criacao) AS dias_para_primeira_compra 
    FROM loja.cliente 
    JOIN loja.carrinho_comprado AS cc ON cliente.id = cc.id_cliente 
    GROUP BY cliente.id
    ORDER BY dias_para_primeira_compra ASC;

SELECT cliente.id, cliente.login, COUNT(DISTINCT p.tipo) AS categorias_compradas 
    FROM loja.cliente 
    JOIN loja.carrinho_comprado AS cc ON cliente.id = cc.id_cliente 
    JOIN loja.carrinho_contem_puzzle AS ccp ON cc.id_carrinho = ccp.id_carrinho 
    JOIN loja.puzzle AS p ON ccp.nome_puzzle = p.nome
    GROUP BY cliente.id;

WITH compra_categoria AS (
    SELECT DISTINCT cliente.login, cliente.id, p.tipo AS categoria, cc.data_compra, cc.id_carrinho
        FROM loja.cliente
        JOIN loja.carrinho_comprado AS cc ON cliente.id = cc.id_cliente
        JOIN loja.carrinho_contem_puzzle AS ccp ON cc.id_carrinho = ccp.id_carrinho 
        JOIN loja.puzzle AS p ON ccp.nome_puzzle = p.nome
) SELECT id, login, categoria, AVG(tempo) AS tempo_medio_entre_categoria
    FROM (
        SELECT id, login, categoria,
            LEAD(data_compra) OVER (PARTITION BY id, categoria ORDER BY data_compra) - data_compra as tempo
        FROM compra_categoria
    ) AS tempo_entre_compras
    GROUP BY id, login, categoria
    ORDER BY id;
