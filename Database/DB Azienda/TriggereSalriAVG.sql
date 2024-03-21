

delimiter //

create trigger onUpdateSalaryAVG
before update on Impiegato
for each row
if (select avg(salario)
	from Impiegato
    where DipNum = old.DipNum) > (select avg(salario)
									from Impiegato
									where DipNum = old.DipNum) * 1.03
then set new.Salario = old.Salario;
end if;
end;
//

delimiter; 