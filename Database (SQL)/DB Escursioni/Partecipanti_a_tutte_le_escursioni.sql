
select P.nome, P.cognome
from persona as P
where not exists(
	select *
	from Escursione as E
    where not exists(
		select*
        from Partecipante as PAR
        where PAR.id_persona = P.id and PAR.id_escursione = E.id
	)
)