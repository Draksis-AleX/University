

select E.titolo, E.descrizione, E.difficolta
from Escursione as E
where E.costo = (
	select max(costo)
    from escursione
)