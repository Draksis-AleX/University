
select distinct t1.materia, numero_esercizi, numero_esercizi_risolti
from (select count(*) as numero_esercizi, materia
	from esercizi
    group by materia
    ) as t1 left join (
    select count(*) as numero_esercizi_risolti, materia
    from esercizi
    where numero_soluzioni > 0
    group by materia) as t2
	on t1.materia = t2.materia