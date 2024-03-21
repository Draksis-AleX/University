
select p.id_tipo, p.id, count(cf) as np
from prodotto as p, acquistoprodotto as ap
where p.id = ap.id_prodotto
group by p.id_tipo, p.id
having count(cf) >= (
	select max(np)
	from (
		select p.id_tipo, p.id, count(cf) as np
		from prodotto as p, acquistoprodotto as ap
		where p.id = ap.id_prodotto
		group by p.id_tipo, p.id
	) as r1
    where r1.id_tipo = p.id_tipo
)
order by p.id_tipo