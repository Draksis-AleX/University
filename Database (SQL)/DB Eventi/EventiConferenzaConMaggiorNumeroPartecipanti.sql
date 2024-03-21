

select e.id, count(pa.id_persona) as n_partecipanti
from (evento as e inner join (partecipante as pa inner join persona as p on pa.id_persona = p.id) on e.id = pa.id_evento) inner join categoriaevento as ca on e.id_categoria = ca.id
where p.stato_civile = "Sposato" and ca.descrizione = "Conferenza"
group by e.id
having n_partecipanti >= all (
	select count(pa.id_persona)
	from (evento as e inner join (partecipante as pa inner join persona as p on pa.id_persona = p.id) on e.id = pa.id_evento) inner join categoriaevento as ca on e.id_categoria = ca.id
	where p.stato_civile = "Sposato" and ca.descrizione = "Conferenza"
	group by e.id
)