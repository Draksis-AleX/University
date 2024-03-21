
select A.id, A.marca
from auto as A
where A.id not in(select id_auto from autoposseduta)