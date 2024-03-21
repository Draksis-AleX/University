

create trigger updateNumeroSoluzioni
after insert on risolto
for each row
	update esercizi
	set numero_soluzioni = numero_soluzioni + 1
	where id = new.id_eser
