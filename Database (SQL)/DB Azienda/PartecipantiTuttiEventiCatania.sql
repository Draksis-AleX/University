
select P.nome, P.cognome
from Persona P
where not exists(
	select E.id
	from (Evento E join Organizzatore O on E.id = O.id_evento) 
		join Persona P1 on O.id_persona = P1.id
	where P1.provincia_residenza = "Catania" and not exists(
			select *
			from Partecipante PR
			where PR.id_persona = P.id and PR.id_evento = E.id))