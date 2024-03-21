-- 1)	Inserimento di un nuovo tesserato  ---------------------------------------------------------------------------------

INSERT INTO tesserato (cf, nome, cognome, luogo_nascita, data_nascita)
VALUES
    ('ABC12345A1234567', 'Mario', 'Rossi', 'Milano', '1990-05-10'); 

-- 2)	Inserimento di una nuova tessera per una persona già esistente  ----------------------------------------------------

INSERT INTO tessera_atleta (data_emissione, data_scadenza, grado, qualifica, data_ultimo_passaggio, cf, id_disciplina)
VALUES
    ('2023-01-15', '2024-01-15', '5^DAN', 'maestro', '2022-12-10', 'ABC12345A12345678', 1); -- La query fallisce se il CF non esiste

INSERT INTO tessera_dirigente (data_emissione, data_scadenza, carica, cf)
VALUES
    ('2023-01-15', '2024-01-15', 'presidente', 'ABC12345A12345678'); -- La query fallisce se il CF non esiste

-- 3)	Visualizzazione di tutte le tessere da atleta con i dati delle relative persone  -----------------------------------

CREATE VIEW AtletiTesserati AS (
    SELECT DISTINCT t.cf, t.nome, t.cognome, t.luogo_nascita, ts.id AS id_tessera, ts.data_emissione, 
        ts.data_scadenza, ts.grado, ts.qualifica, ts.data_ultimo_passaggio, d.nome AS disciplina
    FROM tesserato AS t, tessera_atleta AS ts, disciplina AS d
    WHERE t.cf = ts.cf AND d.id = ts.id_disciplina
    ORDER BY t.cf
);

SELECT * FROM AtletiTesserati;

-- 4)	Inserimento di un nuovo corso  -------------------------------------------------------------------------------------

INSERT INTO corso (nome, giorni, ora_inizio, ora_fine, prezzo_mensile, num_partecipanti, id_disciplina)
VALUES
    ('Corso di Karate Base', 'Lunedi, Mercoledi, Venerdi', '10:00:00', '11:00:00', 35.00, 0, 1);

-- 5)	Iscrizione di un tesserato ad un corso  ----------------------------------------------------------------------------

INSERT INTO partecipa_corso (cf, id_corso)
VALUES
    ("GHI12345C3456789", 2); -- Vengono eseguiti i relativi trigger

-- 6)	Visualizzazione di tutti i corsi attivi con numero partecipanti  ---------------------------------------------------

CREATE VIEW CorsiAttivi AS (
	SELECT c.id, c.nome, c.giorni, c.ora_inizio, c.ora_fine, c.prezzo_mensile, c.num_partecipanti, d.nome AS disciplina
	FROM corso AS c, disciplina AS d
	WHERE c.id_disciplina = d.id
	ORDER BY d.id 
);

SELECT * FROM CorsiAttivi;

-- 7)	Visualizzazione di tutti gli iscritti ad un corso  -----------------------------------------------------------------

SELECT t.cf, t.nome, t.cognome
FROM corso AS c, partecipa_corso AS pc, tesserato AS t
WHERE c.id = pc.id_corso AND pc.cf = t.cf AND c.nome = "Corso di Taekwondo"; -- Ad esempio

-- 8)	Inserimento di una nuova competizione  -----------------------------------------------------------------------------

INSERT INTO competizione (nome, tipologia, data_competizione, orario, durata_minuti, id_disciplina, num_partecipanti)
VALUES
    ('Campionato di Karate I', 'Campionato Kumite', '2022-10-22', '14:30:00', 180, 1, 0);

-- 9)	Iscrizione di un tesserato ad una competizione  --------------------------------------------------------------------

INSERT INTO partecipa_competizione (cf, id_competizione, posizionamento)
VALUES
    ("VWX67890H8901234", 9, NULL); -- Vengono eseguiti i relativi trigger

-- 10)	Visualizzazione di tutte le competizioni con numero dei partecipanti  ----------------------------------------------

CREATE VIEW CompetizioniRegistrate AS (
	SELECT c.nome, c.tipologia, c.data_competizione, c.orario AS orario_inizio, DATE_ADD(c.orario, INTERVAL c.durata_minuti MINUTE) AS orario_fine, 
		d.nome AS disciplina, c.num_partecipanti
	FROM competizione AS c, disciplina AS d
	WHERE c.id_disciplina = d.id
);

SELECT * FROM CompetizioniRegistrate;

-- 11)	Visualizzazione di tutti gli iscritti ad una competizione  ---------------------------------------------------------

SELECT t.cf, t.nome, t.cognome
FROM competizione AS c, partecipa_competizione AS pc, tesserato AS t
WHERE c.id = pc.id_competizione AND pc.cf = t.cf AND c.nome = "Campionato di Jiu-Jitsu III"; -- Ad esempio

-- NB. Per le query che neccessitano di un input dall'utente (ad esempio le INSERT INTO) si suppone che esse vengano lanciate
--     da un linguaggio di backend come php, inserendo quindi i vari parametri