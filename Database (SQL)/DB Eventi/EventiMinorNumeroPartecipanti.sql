
select evento.id, count(partecipante.id_persona) as n_partecipanti
from partecipante inner join evento on partecipante.id_evento = evento.id
where year(evento.data_evento) = 2023
group by evento.id
having n_partecipanti <= all (
	select count(partecipante.id_persona)
	from partecipante inner join evento on partecipante.id_evento = evento.id
	where year(evento.data_evento) = 2023
	group by evento.id )
