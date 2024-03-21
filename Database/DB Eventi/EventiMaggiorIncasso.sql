use dbeventi;

select Evento.id, sum(Evento.costo_partecipazione) as incasso
from Evento inner join Partecipante on Evento.id = Partecipante.id_evento
group by Evento.id
having incasso >= all (
	select sum(Evento.costo_partecipazione)
	from Evento inner join Partecipante on Evento.id = Partecipante.id_evento
	group by Evento.id )