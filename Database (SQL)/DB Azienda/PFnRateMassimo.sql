
select PF.id, PF.numero_rate
from ProdottiFinanziari PF
where PF.numero_rate = (
	select max(numero_rate)
    from ProdottiFinanziari
)