
create schema Banca;

create table ContoCorrenti(
    id int auto_increment primary key,
    saldo float(15,2) not null,
    data_apertura date not null
);

create table ProdottiFinanziari(
    id int auto_increment primary key,
    id_conto int not null references ContoCorrenti(id),
    data_stipula date not null,
    numero_rate int not null,
    id_contraente int not null references Persone(id)
);

create table Persone(
    id int auto_increment primary key,
    nome varchar(20) not null,
    cognome varchar(20) not null,
    data_nascita date not null
);

create table TitolareCC(
    id_persona int not null references Persone(id),
    id_conto int not null references ContoCorrenti(id)
);

create table Transazione(
    id_contoIN int not null references ContoCorrenti(id),
    id_contoOUT int not null references ContoCorrenti(id),
    data date not null,
    causale varchar(250),
    importo float(15,2) not null
);

create table TransazioneProdottoFinanziario(
    id_conto int not null references ContoCorrenti(id),
    data date not null,
    causale varchar(250),
    importo float(15,12) not null,
    id_prodotto int not null references ProdottiFinanziari(id)
);