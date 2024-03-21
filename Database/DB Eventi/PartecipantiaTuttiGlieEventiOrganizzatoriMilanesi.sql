
select *
from persona as p
where not exists ( 
	select *
	from organizzatore as o inner join persona on o.id_persona = persona.id
    where persona.provincia_residenza = "Milano" and not exists (
		select *
        from partecipante as pa
        where pa.id_persona = p.id and pa.id_evento = o.id_evento
        )
	)