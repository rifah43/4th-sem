--declare
--v_emp_name employees.last_name%type;
--v_emp_sal employees.salary%type;
--begin
--query_emp(171, v_emp_name, v_emp_sal);
--dbms_output.put_line(v_emp_name||'earns'|| to_char(v_emp_sal, '$999,999.00'));
--end;
--/

--declare
--v_phone_no ;
--begin
--v_phone_no:= '1234567890';
--format_phone(v_phone_no);
--dbms_output.put_line(v_phone_no);
--end;
--/

declare
v_phone_no varchar2(13);

begin 
select phone_no into v_phone_no from id_no where id=2;
format_phone(v_phone_no);
insert into newNo values(v_phone_no);
end;
/