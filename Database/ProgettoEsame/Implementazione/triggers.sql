--------------------------------- AGGIORNA ATTRIBUTO #PARTECIPANTI DEL CORSO ----------------------------------------

CREATE TRIGGER UpdatePartecipantiCorso
AFTER INSERT ON partecipa_corso
FOR EACH ROW
    UPDATE corso
    SET num_partecipanti = num_partecipanti + 1
    WHERE corso.id = NEW.id_corso;

--------------------------------- AGGIORNA ATTRIBUTO #PARTECIPANTI DELLA COMPETIZIONE ----------------------------------------

CREATE TRIGGER UpdatePartecipantiCompetizione
AFTER INSERT ON partecipa_competizione
FOR EACH ROW
    UPDATE competizione
    SET num_partecipanti = num_partecipanti + 1
    WHERE competizione.id = NEW.id_competizione;

--------------------------------- CONTROLLA CHE UN TESSERATO SIA ABILITATO A PARTECIPARE AD UN CORSO ------------------------

DELIMITER //
CREATE TRIGGER CheckTessera
BEFORE INSERT ON partecipa_corso
FOR EACH ROW
BEGIN
	DECLARE id_disc INTEGER;
    SELECT id_disciplina INTO id_disc FROM corso WHERE corso.id = NEW.id_corso;
	
    IF NOT EXISTS(
        SELECT * FROM tessera_atleta WHERE cf = NEW.cf AND id_disciplina = id_disc
    ) THEN 
		SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = "Per partecipare ad un corso e' necessario possedere una tessera per la disciplina insegnata";
	END IF;
END;//
DELIMITER ;

-- TEST :

INSERT INTO partecipa_corso (cf, id_corso)
VALUES
    ("ABC12345A1234567", 5);

--------------------------------- CONTROLLA CHE UN TESSERATO SIA ABILITATO A TENERE UN CORSO ------------------------

DELIMITER //
CREATE TRIGGER CheckInsegnante
BEFORE INSERT ON tiene_corso
FOR EACH ROW
BEGIN
	DECLARE id_disc INTEGER;
    SELECT id_disciplina INTO id_disc FROM corso WHERE corso.id = NEW.id_corso;
	
    IF NOT EXISTS(
        SELECT * FROM tessera_atleta WHERE cf = NEW.cf AND (qualifica = "allenatore" OR qualifica = "maestro") AND id_disciplina = id_disc
    ) THEN 
		SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = "Per tenere un corso il tesserato deve possedere una tessera per quella disciplina con la qualifica minima di allenatore";
	END IF;
END;//
DELIMITER ;

-- TEST :

INSERT INTO tiene_corso (cf, id_corso)
VALUES
    ("ABC12345A1234567", 3);

--------------------------------- CONTROLLA CHE UN TESSERATO SIA ABILITATO A PARTECIPARE AD UNA COMPETIZIONE ------------------------

DELIMITER //
CREATE TRIGGER CheckTesseraCompetizione
BEFORE INSERT ON partecipa_competizione
FOR EACH ROW
BEGIN
	DECLARE id_disc INTEGER;
    SELECT id_disciplina INTO id_disc FROM competizione WHERE competizione.id = NEW.id_competizione;
	
    IF NOT EXISTS(
        SELECT * FROM tessera_atleta WHERE cf = NEW.cf AND id_disciplina = id_disc
    ) THEN 
		SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = "Per partecipare ad una competizione e' necessario possedere una tessera per la disciplina relativa";
	END IF;
END;//
DELIMITER ;

-- TEST :

INSERT INTO partecipa_competizione (cf, id_competizione, posizionamento)
VALUES
    ("BCD67890J0123456", 4, NULL);

--------------------------------- CONTROLLA CHE UNA COMPETIZIONE SIA TERMINATA PRIMA DI INSERIRE POSIZIONAMENTO ------------------------

DELIMITER //
CREATE TRIGGER CheckFineCompetizione
BEFORE INSERT ON partecipa_competizione
FOR EACH ROW
BEGIN
    IF (NEW.posizionamento IS NOT NULL) THEN
        IF NEW.id_competizione NOT IN (
            SELECT id
            FROM competizione
            WHERE competizione.data_competizione < NOW() or DATE_ADD(competizione.orario, interval competizione.durata_minuti minute) < NOW()
        ) THEN
            SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = "Per inserire il posizionamento in una competizione essa deve essere terminata";
        END IF;
    END IF;
END;//
DELIMITER ;

DELIMITER //
CREATE TRIGGER CheckFineCompetizioneAlter
BEFORE UPDATE ON partecipa_competizione
FOR EACH ROW
BEGIN
    IF (NEW.posizionamento IS NOT NULL) THEN
        IF NEW.id_competizione NOT IN (
            SELECT id
            FROM competizione
            WHERE competizione.data_competizione < NOW() or DATE_ADD(competizione.orario, interval competizione.durata_minuti minute) < NOW()
        ) THEN
            SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = "Per inserire il posizionamento in una competizione essa deve essere terminata";
        END IF;
    END IF;
END;//
DELIMITER ;

-- TEST :

INSERT INTO partecipa_competizione (cf, id_competizione, posizionamento)
VALUES
    ("DEF67890B2345678", 5, 1);

    -- oppure --

UPDATE partecipa_competizione
SET posizionamento = 1
WHERE cf = "ABC12345A1234567" AND id_competizione = 6; 

--------------------------------- CONTROLLA DATA ULTIMO PASSAGGIO PER PASSARE DI GRADO ------------------------------------------------

DELIMITER //
CREATE TRIGGER CheckDataUltimoPassaggio
BEFORE UPDATE ON tessera_atleta
FOR EACH ROW
BEGIN 
    IF(OLD.grado <> NEW.grado) THEN
        IF(DATE_ADD(OLD.data_ultimo_passaggio, INTERVAL 5 MONTH) > NOW()) THEN
            SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = "Per poter passare di grado devono essere passati almeno 5 mesi dall'ultimo passaggio";
        END IF;
    END IF;
END;//
DELIMITER ;

-- TEST :

UPDATE tessera_atleta 
SET grado = "6^DAN" 
WHERE id = 1;

