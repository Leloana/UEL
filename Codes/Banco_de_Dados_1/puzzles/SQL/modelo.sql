CREATE SCHEMA loja;

CREATE FUNCTION loja.fn_puzzle_disjunta (
        nome_puzzle VARCHAR(40),
        tipo_puzzle VARCHAR(10)
)
    RETURNS BOOLEAN
AS $$
BEGIN
    RETURN (
        SELECT COALESCE(true, false)
            FROM  loja.puzzle
            WHERE nome = nome_puzzle
            AND   tipo = tipo_puzzle
        );
END
$$ LANGUAGE plpgsql;

CREATE TABLE loja.carrinho (
	id SERIAL,
	CONSTRAINT pk_carrinho PRIMARY KEY(id)
);

CREATE TABLE loja.carrinho_atual (
	id_carrinho INT,
	CONSTRAINT pk_carrinho_atual PRIMARY KEY(id_carrinho),
	CONSTRAINT fk_carrinho_atual_filho FOREIGN KEY(id_carrinho)
		REFERENCES loja.carrinho(id)
);

CREATE TABLE loja.cliente (
	id SERIAL,
    login VARCHAR(20) NOT NULL,
    senha CHARACTER(32) NOT NULL,
    data_criacao DATE NOT NULL,
	id_carrinho_atual INT NOT NULL,
	CONSTRAINT pk_cliente PRIMARY KEY(id),
	CONSTRAINT fk_carrinho_atual_cliente FOREIGN KEY(id_carrinho_atual)
		REFERENCES loja.carrinho_atual (id_carrinho) ON UPDATE CASCADE,
    CONSTRAINT uq_login_cliente UNIQUE (login)
);

CREATE TABLE loja.carrinho_comprado (
	id_carrinho int,
	data_compra DATE NOT NULL,
	id_cliente  int,
	CONSTRAINT pk_carrinho_comprado PRIMARY KEY(id_carrinho),
	CONSTRAINT fk_carrinho_comprado FOREIGN KEY(id_carrinho)
		REFERENCES loja.carrinho(id),
	CONSTRAINT fk_cliente_compras FOREIGN KEY(id_cliente)
		REFERENCES loja.cliente(id)
);

CREATE TABLE loja.marca (
	nome VARCHAR(40),
	CONSTRAINT pk_marca PRIMARY KEY(nome)
);

CREATE TABLE loja.puzzle (
	nome       VARCHAR(40),
    tipo       VARCHAR(10) NOT NULL,
	preco      NUMERIC (10,2) NOT NULL,
	nome_marca VARCHAR(40) NOT NULL,
	CONSTRAINT pk_puzzle PRIMARY KEY(nome),
	CONSTRAINT fk_marca_puzzle FOREIGN KEY(nome_marca)
		REFERENCES loja.marca(nome) ON UPDATE CASCADE,
    CONSTRAINT ck_puzzle_tipo CHECK (tipo IN ('cubo2', 'cubo3', 'cubo4', 'piraminx', 'clock'))
);

CREATE TABLE loja.carrinho_contem_puzzle (
	id_carrinho INT,
	nome_puzzle VARCHAR(40),
	quantidade INT NOT NULL,
    preco NUMERIC (10,2) NOT NULL,
	CONSTRAINT pk_cc_puzzle PRIMARY KEY (id_carrinho, nome_puzzle),
	CONSTRAINT fk_carrinho_puzzle FOREIGN KEY(id_carrinho)
		REFERENCES loja.carrinho(id),
	CONSTRAINT fk_puzzle_carrinho  FOREIGN KEY(nome_puzzle)
		REFERENCES loja.puzzle(nome) ON UPDATE CASCADE
);

CREATE TABLE loja.imagem (
	imagem VARCHAR(1024),
	nome_puzzle VARCHAR(40) NOT NULL,
	CONSTRAINT pk_imagem PRIMARY KEY(imagem, nome_puzzle),
	CONSTRAINT fk_puzzle_imagem FOREIGN KEY(nome_puzzle)
		REFERENCES loja.puzzle(nome) ON UPDATE CASCADE
);

CREATE TABLE loja.palavra_chave (
	palavra VARCHAR(40),
	nome_puzzle VARCHAR(40) NOT NULL,
	CONSTRAINT pk_chave PRIMARY KEY(palavra, nome_puzzle),
	CONSTRAINT fk_puzzle_pal_chave FOREIGN KEY(nome_puzzle)
		REFERENCES loja.puzzle(nome) ON UPDATE CASCADE
);

CREATE TABLE loja.cubo2(
	nome_puzzle VARCHAR(40),
	com_adesivo BOOLEAN NOT NULL,
	CONSTRAINT pk_cubo2 PRIMARY KEY(nome_puzzle),
	CONSTRAINT fk_puzzle_cubo FOREIGN KEY(nome_puzzle)
		REFERENCES loja.puzzle(nome) ON UPDATE CASCADE,
    CONSTRAINT ck_puzzle_disjunta CHECK (loja.fn_puzzle_disjunta(nome_puzzle, 'cubo2'))
);

CREATE TABLE loja.cubo3(
	nome_puzzle VARCHAR(40),
	com_adesivo BOOLEAN NOT NULL,
	CONSTRAINT pk_cubo3 PRIMARY KEY(nome_puzzle),
	CONSTRAINT fk_puzzle_cubo FOREIGN KEY(nome_puzzle)
		REFERENCES loja.puzzle(nome) ON UPDATE CASCADE,
    CONSTRAINT ck_puzzle_disjunta CHECK (loja.fn_puzzle_disjunta(nome_puzzle, 'cubo3'))
);

CREATE TABLE loja.cubo4(
	nome_puzzle VARCHAR(40),
	com_adesivo BOOLEAN NOT NULL,
	CONSTRAINT pk_cubo4 PRIMARY KEY(nome_puzzle),
	CONSTRAINT fk_puzzle_cubo FOREIGN KEY(nome_puzzle)
		REFERENCES loja.puzzle(nome) ON UPDATE CASCADE,
    CONSTRAINT ck_puzzle_disjunta CHECK (loja.fn_puzzle_disjunta(nome_puzzle, 'cubo4'))
);

CREATE TABLE loja.piraminx(
	nome_puzzle VARCHAR(40),
	CONSTRAINT pk_piraminx PRIMARY KEY(nome_puzzle),
	CONSTRAINT fk_puzzle_piraminx FOREIGN KEY(nome_puzzle)
		REFERENCES loja.puzzle(nome) ON UPDATE CASCADE,
    CONSTRAINT ck_puzzle_disjunta CHECK (loja.fn_puzzle_disjunta(nome_puzzle, 'piraminx'))
);

CREATE TABLE loja.clock(
	nome_puzzle VARCHAR(40),
	CONSTRAINT pk_clock PRIMARY KEY(nome_puzzle),
	CONSTRAINT fk_puzzle_clock FOREIGN KEY(nome_puzzle)
		REFERENCES loja.puzzle(nome) ON UPDATE CASCADE,
    CONSTRAINT ck_puzzle_disjunta CHECK (loja.fn_puzzle_disjunta(nome_puzzle, 'clock'))
);
