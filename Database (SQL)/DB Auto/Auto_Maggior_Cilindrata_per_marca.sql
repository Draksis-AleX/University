select A.marca, A.id
from auto as A
where A.cilindrata >= (
	select max(A2.cilindrata)
    from auto as A2
    where A2.marca = A.marca
    )
