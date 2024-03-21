select marca
from auto
where marca not in (
select distinct a3.marca
	from (
		Select a1.marca, a1.id
		from auto a1
		except
		select a2.marca, a2.id
		from auto a2, autoposseduta ap
		where ap.id_auto = a2.id
	)as a3
)