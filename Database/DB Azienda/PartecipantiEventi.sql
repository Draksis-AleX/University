select P.id, P.nome, P.cognome, E.id, E.titolo
from (Persona P join Partecipante PR on P.id = PR.id_persona)
	join Evento E on E.id = PR.id_evento
