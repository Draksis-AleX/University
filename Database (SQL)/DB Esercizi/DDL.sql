
use dbesercizi;

create table Studenti(
	matricola int not null auto_increment primary key,
    nome varchar(20) not null,
    cognome varchar(20) not null
);

create table Materie(
	id int not null auto_increment primary key,
    titolo varchar(30) not null,
    descrizione varchar(100) not null
);

create table Esercizi(
	id int not null auto_increment primary key, 
    testo varchar(200) not null,
    soluzione varchar(200) not null,
    materia int not null references Materia(id),
    numero_soluzioni int not null
);

create table Risolto(
	id_eser int not null references Esercizi(id),
    id_stud int not null references Studenti(id),
    data_soluzione date not null,
    primary key(id_eser, id_stud)
);