
insert into Persone(nome, cognome, data_nascita) values
("Mario", "Rossi", "2001-12-15"),
("Luigi", "Verdi", "2000-08-12"),
("Stefano", "Neri", "1988-05-24"),
("Carla", "Piattelli", "1968-10-01"),
("Mauro", "Gialli", "1979-01-22")

insert into ContoCorrenti(saldo, data_apertura) values
(2588,"2001-12-01"),
(145889,"2010-05-15"),
(6432,"2012-08-01"),
(12345,"2000-02-01"),
(9889,"1988-12-01"),
(1450034,"2003-09-01"),
(9876,"1999-07-01")

insert into TitolareCC(id_persona, id_conto) values
(1, 2),
(2, 3),
(3, 1),
(3, 4),
(4, 5),
(5, 6),
(5, 7),
(4, 6)

insert into ProdottiFinanziari(id_conto, data_stipula, numero_rate, id_contraente) values
(1, "2005-08-15", 25, 3),
(3, "2015-08-15", 14, 2),
(7, "2002-08-15", 20, 5)

insert into Transazione(id_contoIN, id_contoOUT, data, importo) values
(1,2, "2020-01-01", 12345),
(2,5, "2020-01-01", 34453),
(7,6, "2020-01-01", 32543),
(6,3, "2020-01-01", 12312345),
(7,1, "2020-01-01", 755),
(7,2, "2020-01-01", 1234),
(4,5, "2020-01-01", 576390),
(3,2, "2020-01-01", 908),
(1,5, "2020-01-01", 12),
(5,6, "2020-01-01", 245),
(5,2, "2020-01-01", 6544),
(6,3, "2020-01-01", 445896)

insert into TransazioneProdottoFinanziario(id_conto, data, importo, id_prodotto) values
(1, "2020-01-01", 124, 1),
(1, "2021-01-01", 124, 1),
(3, "2020-01-01", 350, 2),
(7, "2020-01-01", 150, 3),
(7, "2020-01-01", 150, 3),
(7, "2020-01-01", 150, 3),


