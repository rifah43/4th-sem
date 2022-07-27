SELECT LOAN_NUMBER FROM LOAN WHERE BRANCH_NAME = 'Perryridge' AND AMOUNT > 1200;

SELECT CUSTOMER_NAME, T.LOAN_NUMBER, S.AMOUNT FROM BORROWER T, LOAN S WHERE T.LOAN_NUMBER = S.LOAN_NUMBER;

select customer_name, borrower.loan_number loan_id, amount from borrower, loan where borrower.loan_number = loan.loan_number;

select distinct T.branch_name from branch T, branch S where T.asset > S.asset and S.branch_city = 'Brooklyn';

select customer_name from customer where customer_street like '%a%';

select distinct customer_name from    borrower, loan where borrower.loan_number = loan.loan_number and branch_name = 'Perryridge' order by customer_name;

select distinct customer_name from    borrower, loan where borrower.loan_number = loan.loan_number and branch_name = 'Perryridge' order by customer_name desc;

(select customer_name from depositor) union (select customer_name from borrower);

(select customer_name from depositor) intersect (select customer_name from borrower);

(select customer_name from depositor) minus (select customer_name from borrower);

select avg (balance) from account where branch_name = 'Perryridge';

select count (*) from customer;

select count (distinct customer_name) from depositor;

select branch_name, count (distinct customer_name) from depositor, account where depositor.account_number = account.account_number group by branch_name;

select branch_name, avg (balance) from account group by branch_name having avg (balance) < 1200;

select distinct customer_name from borrower where customer_name in (select customer_name from depositor );

select distinct customer_name from borrower where customer_name not in (select customer_name from depositor );

select distinct customer_name from borrower, loan where borrower.loan_number = loan.loan_number and branch_name = 'Perryridge' and customer_name in (select customer_name from depositor, account where branch_name = 'Perryridge' and depositor.account_number = account.account_number);