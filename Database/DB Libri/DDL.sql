use dblibri;

create table Libro(
	id int not null primary key auto_increment,
    titolo varchar(100) not null,
    autore varchar(50) not null,
    data_uscita date not null,
    id_sequel int,
    genere varchar(50) not null
);

create table CopiaLibro(
	id int not null primary key auto_increment,
    id_libro int not null references Libro(id)
);

create table Persona(
	id int not null primary key auto_increment,
    nome varchar(30) not null,
    cognome varchar(30) not null,
    prestiti int not null default(0)
);

create table Prestito(
	id_libro int not null references CopiaLibro(id),
    id_persona int not null references Persona(id),
    data_prestito date not null,
    data_restituzione date,
    restituito boolean not null,
    primary key (id_libro, id_persona, data_prestito)
)