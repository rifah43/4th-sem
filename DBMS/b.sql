//select LAST_NAME||'''s ('||job_id||') salary with COMMISSION is: '|| (NVL(SALARY+SALARY*COMMISSION_PCT,SALARY)*12) "ANNUAL SALARY" from EMPLOYEES;

select LAST_NAME||'''s ('||job_id||') salary with COMMISSION is: '|| (NVL(SALARY+SALARY*COMMISSION_PCT,SALARY)*12) "ANNUAL SALARY" from EMPLOYEES where (12*SALARY)>=50000;

select FIRST_NAME||'''s ('||job_id||') salary with COMMISSION is: '|| (NVL(SALARY+SALARY*COMMISSION_PCT,SALARY)*12) "ANNUAL SALARY" from EMPLOYEES where first_name LIKE 'S%';

select FIRST_NAME||'''s ('||job_id||') salary with COMMISSION is: '|| (NVL(SALARY+SALARY*COMMISSION_PCT,SALARY)*12) "ANNUAL SALARY" from EMPLOYEES where first_name LIKE '__a%';
//
SQL> select department_id, salary from EMPLOYEES ORDER BY department_id , salary DESC;

SQL> select department_id, salary, job_id from EMPLOYEES WHERE &sal<=salary ORDER BY department_id;

SQL> select department_id, salary from EMPLOYEES WHERE salary=&sal_num;

