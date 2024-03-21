with recursive sequel as (
	select L.id, L.id_sequel
    from Libro as L
    union all
    select L.id, L.id_sequel
    from Libro as L, sequel
    where sequel.id_sequel = L.id
)
select id, count(*) - 1 as nSequel
from sequel
group by id
having count(*) >= 3