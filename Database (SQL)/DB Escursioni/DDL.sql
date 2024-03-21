
use dbescursioni;

create table Escursione(
	id int not null auto_increment,
    titolo varchar(50) not null,
    descrizione varchar(100) not null,
    durata int not null,
    difficolta int not null,
    costo decimal(10,2) not null,
    primary key (id)
);

create table Persona(
	id int not null auto_increment,
    nome varchar(30) not null,
    cognome varchar(30) not null,
    primary key (id)
);

create table DataEscursione(
	id int not null auto_increment,
    data_esc date not null,
    id_esc int not null references Escursione(id),
    id_guida int not null references Persona(id),
    primary key(id)
);

create table Partecipante(
	id_persona int not null references Persona(id),
    id_escursione int not null references Escursione(id),
    primary key (id_persona, id_escursione)
)