select E.titolo, count(P.id) as n_partecipanti
from ((Evento E join Partecipante PR on E.id = PR.id_evento)
	join Persona P on PR.id_persona = P.id) 
    join CategoriaEvento CE on E.categoria = CE.id
where CE.descrizione = "matrimonio" and P.stato_civile = "sposato"
group by E.titolo
having count(P.id) >= (select max(n_partecipanti)
						from partecipantimatrimonisposati)