DROP TABLE nf;

CREATE TABLE nf
(
	region_name VARCHAR(100) NOT NULL,
	country_name VARCHAR(100) NOT NULL,
	city_name VARCHAR(100) NOT NULL,
	department_name VARCHAR(100) NOT NULL,
	job_title VARCHAR(100) NOT NULL,
	employee_id number NOT NULL,
	last_name VARCHAR(100) NOT NULL,
	annual_salary number not null,
	annual_tax number not null
);

declare
	cursor c_zip1 is
	select regions.region_name,countries.country_name,locations.city,departments.department_name,jobs.job_title, employees.employee_id, employees.last_name, employees.salary, employees.commission_pct
	from regions,countries,locations,departments,jobs,employees;
	vr_zip1 c_zip1%rowtype;
	
begin
	open c_zip1;
	
	loop
	fetch c_zip1 into vr_zip1;
	exit when c_zip1%notfound;
	dbms_output.put_line(vr_zip1.department_name);
	--INSERT INTO nn VALUES (vr_zip1.region_name, vr_zip1.country_name, vr_zip1.city, vr_zip1.department_name, vr_zip1.job_title, vr_zip1.employee_id, vr_zip1.last_name, (NVL(vr_zip1.SALARY+vr_zip1.SALARY*vr_zip1.COMMISSION_PCT,vr_zip1.SALARY)*12), vr_zip1.SALARY*12*.1);
	end loop;
end;
/