select E.id, E.titolo
from (SELECT 
        `E`.`id` AS `id`,
        (`E`.`costo_partecipazione` * COUNT(`P`.`id_persona`)) AS `incasso`
    FROM
        (`evento` `E`
        JOIN `partecipante` `P` ON ((`E`.`id` = `P`.`id_evento`)))
    GROUP BY `E`.`id`) I join Evento E on E.id = I.id
where I.incasso = (select max(I.incasso)
	from (SELECT 
        `E`.`id` AS `id`,
        (`E`.`costo_partecipazione` * COUNT(`P`.`id_persona`)) AS `incasso`
    FROM
        (`evento` `E`
        JOIN `partecipante` `P` ON ((`E`.`id` = `P`.`id_evento`)))
    GROUP BY `E`.`id`) I)