delimiter //

create trigger onUpdateSalary
before update on Impiegato
for each row
if new.Salario > (select Salario
					from Dipartimento D join Impiegato I on D.DipNum = I.DipNum
                    where D.DipNum = old.DipNum and Nome = NomeManager)
then set new.Salario = (select Salario
					from Dipartimento D join Impiegato I on D.DipNum = I.DipNum
                    where D.DipNum = old.DipNum and Nome = NomeManager);
end if;
end; //

delimiter ;
