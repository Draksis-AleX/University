
select DE.id_guida
from dataescursione as DE
where DE.id_guida not in(
	select DE1.id_guida
    from dataescursione as DE1 inner join Escursione as E on DE1.id_esc = E.id
    where E.difficolta = (
		select max(difficolta)
        from Escursione
	)
)