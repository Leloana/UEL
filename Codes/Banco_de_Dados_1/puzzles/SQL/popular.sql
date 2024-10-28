--INSERINDO MARCAS
INSERT INTO loja.marca (nome) VALUES ('Rubik''s');
INSERT INTO loja.marca (nome) VALUES ('GANCube');
INSERT INTO loja.marca (nome) VALUES ('MoYu');
INSERT INTO loja.marca (nome) VALUES ('QiYi');

--INSERINDO CUBO 3x3
INSERT INTO loja.puzzle (nome, tipo, preco, nome_marca) VALUES ('Rubik''s 3x3 Cube', 'cubo3', 50.00, 'Rubik''s');
INSERT INTO loja.cubo3 (nome_puzzle, com_adesivo) VALUES ('Rubik''s 3x3 Cube', false);
--INSERINDO cubo 2x2
INSERT INTO loja.puzzle (nome, tipo, preco, nome_marca) VALUES ('Rubik''s 2x2 Cube', 'cubo2', 50.00, 'Rubik''s');
INSERT INTO loja.cubo2 (nome_puzzle, com_adesivo) VALUES ('Rubik''s 2x2 Cube', false);
--INSERINDO CUBO 4x4
INSERT INTO loja.puzzle (nome, tipo, preco, nome_marca) VALUES ('Rubik''s 4x4 Cube', 'cubo4', 50.00, 'Rubik''s');
INSERT INTO loja.cubo4 (nome_puzzle, com_adesivo) VALUES ('Rubik''s 4x4 Cube', false);
--INSERINDO CUBO GAN14 Maglev Pro
INSERT INTO loja.puzzle (nome, tipo, preco, nome_marca) VALUES ('GAN14 Maglev Pro', 'cubo3', 450.00, 'GANCube');
INSERT INTO loja.cubo3 (nome_puzzle, com_adesivo) VALUES ('GAN14 Maglev Pro', true);
--INSERINDO CUBO GAN12 Maglev
INSERT INTO loja.puzzle (nome, tipo, preco, nome_marca) VALUES ('GAN12 Maglev', 'cubo3', 300.00, 'GANCube');
INSERT INTO loja.cubo3 (nome_puzzle, com_adesivo) VALUES ('GAN12 Maglev', false);
--INSERINDO CUBO GAN251 M Pro
INSERT INTO loja.puzzle (nome, tipo, preco, nome_marca) VALUES ('GAN251 M Pro', 'cubo2', 200.00, 'GANCube');
INSERT INTO loja.cubo2 (nome_puzzle, com_adesivo) VALUES ('GAN251 M Pro', true);
--INSERINDO CUBO MoYu RS3 M 2020 3x3
INSERT INTO loja.puzzle (nome, tipo, preco, nome_marca) VALUES ('MoYu RS3 M 2020 3x3', 'cubo3', 40.00, 'MoYu');
INSERT INTO loja.cubo3 (nome_puzzle, com_adesivo) VALUES ('MoYu RS3 M 2020 3x3', false);
--INSERINDO PIRAMINX MoYu WeiLong Pyraminx Magnetic
INSERT INTO loja.puzzle (nome, tipo, preco, nome_marca) VALUES ('MoYu WeiLong Pyraminx Magnetic', 'piraminx', 80.00, 'MoYu');
INSERT INTO loja.piraminx (nome_puzzle) VALUES ('MoYu WeiLong Pyraminx Magnetic');
--INSERINDO PIRAMINX QiYi MS Pyraminx
INSERT INTO loja.puzzle (nome, tipo, preco, nome_marca) VALUES ('QiYi MS Pyraminx', 'piraminx', 40.00, 'QiYi');
INSERT INTO loja.piraminx (nome_puzzle) VALUES ('QiYi MS Pyraminx');
--INSERINDO CLOCK QiYi Magnetic Clock
INSERT INTO loja.puzzle (nome, tipo, preco, nome_marca) VALUES ('QiYi Magnetic Clock', 'clock', 180.00, 'QiYi');
INSERT INTO loja.clock (nome_puzzle) VALUES ('QiYi Magnetic Clock');
