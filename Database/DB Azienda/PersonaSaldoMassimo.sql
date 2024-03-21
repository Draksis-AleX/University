
/*create view SaldoTot as (
	select P.id, sum(CC.saldo) as saldo
    from (Persone P join TitolareCC TCC on P.id = TCC.id_persona)
		join ContoCorrenti CC on CC.id = TCC.id_conto
	group by P.id
);*/

select CC.id, CC.saldo
from SaldoTot CC
where CC.saldo = (
	select max(saldo)
    from SaldoTot
)