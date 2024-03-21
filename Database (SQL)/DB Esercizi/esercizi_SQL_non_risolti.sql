

select E.id, E.testo
from Esercizi as E
where numero_soluzioni = 0 and E.testo like "%SQL%"