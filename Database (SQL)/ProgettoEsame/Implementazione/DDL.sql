CREATE SCHEMA `db_scuola_arti_marziali` ;

USE `db_scuola_arti_marziali` ;

CREATE TABLE tesserato(
    cf VARCHAR(16) NOT NULL PRIMARY KEY,
    nome VARCHAR(20) NOT NULL,
    cognome VARCHAR(20) NOT NULL,
    luogo_nascita VARCHAR(20) NOT NULL,
    data_nascita DATE NOT NULL 
);

CREATE TABLE disciplina(
    id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    nome VARCHAR(50) NOT NULL,
    descrizione VARCHAR(250)
);

CREATE TABLE corso(
    id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    nome VARCHAR(50) NOT NULL,
    giorni VARCHAR(100) NOT NULL,
    ora_inizio TIME NOT NULL,
    ora_fine TIME NOT NULL,
    prezzo_mensile DECIMAL(5,2),
    num_partecipanti INT NOT NULL DEFAULT 0,
    id_disciplina INT NOT NULL, 
    FOREIGN KEY(id_disciplina) REFERENCES disciplina(id)
);

CREATE TABLE tessera_atleta(
    id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    data_emissione DATE NOT NULL,
    data_scadenza DATE NOT NULL,
    grado VARCHAR(6) NOT NULL DEFAULT "6^KYU",
    qualifica VARCHAR(30) NOT NULL DEFAULT "atleta",
    data_ultimo_passaggio DATE NOT NULL,
    cf VARCHAR(16) NOT NULL,
    id_disciplina INT NOT NULL,
    FOREIGN KEY(cf) REFERENCES tesserato(cf),
    FOREIGN KEY(id_disciplina) REFERENCES disciplina(id),
    CHECK (grado IN ("6^KYU", "5^KYU", "4^KYU", "3^KYU", "2^KYU", "1^KYU", "1^DAN", "2^DAN", "3^DAN", "4^DAN", "5^DAN", "6^DAN", "7^DAN", "8^DAN", "9^DAN", "10^DAN")),
    CHECK (qualifica IN ("atleta", "aspirante allenatore", "allenatore", "maestro"))
);

CREATE TABLE tessera_dirigente(
    id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    data_emissione DATE NOT NULL,
    data_scadenza DATE NOT NULL,
    carica VARCHAR(50) NOT NULL,
    cf VARCHAR(16) NOT NULL,
    FOREIGN KEY(cf) REFERENCES tesserato(cf),
    CHECK (carica IN ("presidente", "segretario", "consigliere"))
);

CREATE TABLE competizione(
    id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
    tipologia VARCHAR(100) NOT NULL,
    data_competizione DATE NOT NULL,
    orario TIME NOT NULL,
    durata_minuti INT NOT NULL,
    id_disciplina INT NOT NULL,
    num_partecipanti INT NOT NULL DEFAULT 0,
    FOREIGN KEY(id_disciplina) REFERENCES disciplina(id) 
);

CREATE TABLE partecipa_corso(
    cf VARCHAR(16) NOT NULL,
    id_corso INT NOT NULL,
    FOREIGN KEY(cf) REFERENCES tesserato(cf),
    FOREIGN KEY(id_corso) REFERENCES corso(id),
    PRIMARY KEY (cf, id_corso) 
);

CREATE TABLE tiene_corso(
    cf VARCHAR(16) NOT NULL,
    id_corso INT NOT NULL,
    FOREIGN KEY(cf) REFERENCES tesserato(cf),
    FOREIGN KEY(id_corso) REFERENCES corso(id),
    PRIMARY KEY (cf, id_corso) 
);

CREATE TABLE partecipa_competizione(
    cf VARCHAR(16) NOT NULL,
    id_competizione INT NOT NULL,
    posizionamento INT,
    FOREIGN KEY(cf) REFERENCES tesserato(cf),
    FOREIGN KEY(id_competizione) REFERENCES competizione(id),
    PRIMARY KEY (cf, id_competizione)
);

