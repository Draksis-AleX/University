
select p1.id_persona, p2.id_persona
from partecipante as p1, partecipante as p2
where p1.id_escursione = p2.id_escursione and p1.id_persona < p2.id_persona
and (p1.id_persona, p2.id_persona) not in(
	select p1.id_persona, p2.id_persona
    from partecipante as p1, partecipante as p2
    where p1.id_escursione <> p2.id_escursione and p1.id_persona < p2.id_persona
    and (not exists(
		select *
        from partecipante as par1
        where par1.id_persona = p1.id_persona and par1.id_escursione = p1.id_escursione)
	or not exists(
		select *
        from partecipante as par2
        where par2.id_persona = p2.id_persona and par2.id_escursione = p2.id_escursione)
	)
)