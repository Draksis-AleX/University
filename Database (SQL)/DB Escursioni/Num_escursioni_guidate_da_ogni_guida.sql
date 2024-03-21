

select DE.id_guida, count(DE.id_esc) as Num_Escursioni_Guidate
from dataescursione as DE
group by DE.id_guida
order by DE.id_guida