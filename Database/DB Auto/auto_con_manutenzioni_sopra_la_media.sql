
select targa, count(*) N_Manutenzioni, sum(costo)
from manutenzione
group by targa
having N_Manutenzioni > (
	select avg(nmat)
    from (
		select count(*) as nmat
        from manutenzione
        group by targa
	) as r1
)