use dbauto;

create table Auto(
	id int not null auto_increment primary key,
    marca varchar(20) not null,
    alimentazione varchar(30) not null,
    cilindrata int not null
);

create table AutoPosseduta(
	targa varchar(7) not null primary key,
    id_auto int not null references Auto(id),
    costo_rifornimenti int not null,
    data_immatricolazione date not null
);

create table Rifornimento(
	targa varchar(7) not null references AutoPosseduta(targa),
    data_rifornimento date not null,
    prezzo_litro int not null,
    litri int not null,
    primary key (targa, data_rifornimento)
);

create table Manutenzione(
	targa varchar(7) not null references AutoPosseduta(targa),
    data_manutenzione date not null,
    descrizione varchar(100) not null,
    costo int not null,
    primary key (targa, data_manutenzione)
);




