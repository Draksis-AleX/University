
select CC.id, CC.saldo
from ContoCorrenti CC
where CC.saldo = (
	select max(saldo)
    from ContoCorrenti
)