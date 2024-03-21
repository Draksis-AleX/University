delimiter //

create trigger esperienza
after insert on dataescursione
for each row

begin
Declare X integer;
Declare Y integer;

select difficolta into Y
from escursione
where id = new.id_esc;

if Y > 1 then
	select count(*) into X
    from escursione as e, dataescursione as de
    where de.id_esc = e.id and new.id_guida = de.id_guida and difficolta = Y-1;
    
    if X < 5 then
		delete from dataescursione where id = new.id;
	end if;
end if;
end//

delimiter ;