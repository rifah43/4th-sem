--select employee_id , salary from employees;

--update employees set salary = salary*2 where employee_id = 204;

--select employee_id , salary from employees;

--rollback;

--select employee_id , salary from employees;

--create or replace procedure raise_salary (p_id in employees.employee_id%type, p_percent in number) is begin update employees set salary = salary*(1+p_percent/100) where employee_id = p_id;
--end raise_salary;
--/

--create or replace procedure query_emp (p_id in employees.employee_id%type, p_name out employees.last_name%type , p_salary out employees.salary%type)
--is begin 
--select last_name, salary into p_name, p_salary from employees where employee_id = p_id;
--end query_emp;
--/

--create or replace procedure format_phone
--(p_phone_no in out varchar2)
--is begin
--p_phone_no := '(' || substr(p_phone_no,1,3)
--			|| ')' || substr(p_phone_no,4,3)
--			|| '-' ||substr(p_phone_no,7);
--end format_phone;
--/

drop table id_no;
drop table newNo;

CREATE TABLE id_no
(
	id number not null,
	phone_no varchar2(14) not null
);

CREATE TABLE newNo
(
	format_no varchar2(14) not null
);

INSERT INTO id_no VALUES (1, '0123456789');
INSERT INTO id_no VALUES (2, '1234567890');
INSERT INTO id_no VALUES (3, '2345678901');
INSERT INTO id_no VALUES (4, '3456789012');
INSERT INTO id_no VALUES (5, '4567890123');

create or replace procedure format_phone
(p_phone_no in out varchar2)
is begin
p_phone_no := '(' || substr(p_phone_no,1,3)
			|| ')' || substr(p_phone_no,4,3)
			|| '-' ||substr(p_phone_no,7);
end format_phone;
/


