
use DBEventi;

CREATE TABLE Persona (
    id int NOT NULL AUTO_INCREMENT,
    nome varchar(30) not null,
    cognome varchar(30) not null,
    provincia_residenza varchar(50) not null,
    stato_civile varchar(30),
    PRIMARY KEY (id)
);

CREATE TABLE CategoriaEvento (
    id int not null AUTO_INCREMENT primary key,
    descrizione varchar(100) not null
);

CREATE TABLE Catering (
    id int not null AUTO_INCREMENT primary key,
    nome varchar(50) not null,
    descrizione varchar(100),
    sede varchar(100) not null
);

CREATE TABLE Evento (
    id int NOT NULL AUTO_INCREMENT primary key,
    titolo varchar(50) not null,
    data_evento date NOT NULL,
    id_categoria int NOT NULL references CategoriaEvento(id),
    costo_partecipazione decimal(10, 2) not null,
    id_catering int not null references Catering(id)
);

CREATE TABLE Partecipante (
    id_persona int not null references Persona(id),
    id_evento int not null references Evento(id),
    primary key (id_persona, id_evento)
);

CREATE TABLE Organizzatore (
    id_persona int not null references Persona(id),
    id_evento int not null references Evento(id),
    primary key (id_persona, id_evento)
);

