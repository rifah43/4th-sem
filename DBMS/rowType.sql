declare
	vr_employee employees%rowtype;

begin
	select *
	into vr_employee
	from employees
	where employee_id = 156;
	dbms_output.put_line(vr_employee.first_name||vr_employee.last_name||'has an id of 156');
exception
	when no_data_found
	then
	raise_application_error(-2001,'The Student'||'is not in the database');
	
end;
/