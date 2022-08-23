DROP TABLE ntab;

CREATE TABLE ntab
(
	employee_id number NOT NULL,
	name VARCHAR(20) NOT NULL,
	salary number not null,
	CONSTRAINT ntab_PK PRIMARY KEY(employee_id)
);

declare
	cursor c_zip is
	select *
	from employees;
	vr_zip c_zip%rowtype;
	
begin
	open c_zip;
	
	loop
	fetch c_zip into vr_zip;
	exit when c_zip%notfound;
	
	if vr_zip.salary>5000 then
	INSERT INTO ntab VALUES (vr_zip.employee_id, vr_zip.first_name, vr_zip.salary);
	end if;
	end loop;
end;
/