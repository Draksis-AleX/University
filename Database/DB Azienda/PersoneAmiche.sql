select distinct amici1.amico1, amici1.amico2 
from (select a1.amico1, a2.amico2
	from amici a1 join amici a2
	where a1.amico2 = a2.amico1) amici1 left join amici on
		amici1.amico1 = amici.amico1 and amici1.amico2 = amici.amico2
where amici.amico1 is null and amici1.amico1 > amici1.amico2