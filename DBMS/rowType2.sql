declare
	vr_employee employees%rowtype;
	emp_id number;

begin
	emp_id := &emp_id;
	select *
	into vr_employee
	from employees
	where employee_id = emp_id;
	dbms_output.put_line(vr_employee.first_name||': '||'Annual salary is:' ||(NVL(vr_employee.SALARY+vr_employee.SALARY*vr_employee.COMMISSION_PCT,vr_employee.SALARY)*12) ||' & the annual tax is '||(NVL(vr_employee.SALARY+vr_employee.SALARY*vr_employee.COMMISSION_PCT,vr_employee.SALARY)*12)*.1);
exception
	when no_data_found
	then
	raise_application_error(-2001,'The Student'||'is not in the database');
	
end;
/