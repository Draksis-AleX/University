
select E.id, E.titolo
from (select EV.id, count(PR.id_persona) as n_partecipanti
		from Evento EV join Partecipante PR on EV.id = PR.id_evento
        where year(EV.giorno) = "2023" 
        group by EV.id) NP join Evento E on NP.id = E.id
where NP.n_partecipanti = (select min(n_partecipanti)
							from (select EV.id, count(PR.id_persona) as n_partecipanti
									from Evento EV join Partecipante PR on EV.id = PR.id_evento
									where year(EV.giorno) = "2023" 
									group by EV.id) NP) 