--declare
--v_counter number:=1;
--begin
--while v_counter>0
--for v_counter in 1..5
--loop
--dbms_output.put_line('v_counter='|| v_counter);
--v_counter := v_counter-1;
--end loop;


--while v_counter>0
--for v_counter in reverse 1..5
--loop
--dbms_output.put_line('v_counter='|| v_counter);
--end loop;

--end;
--/

declare
v_counter1 integer:=0;
v_counter2 integer;

begin
while v_counter1<3
loop
dbms_output.put_line('v_counter1='|| v_counter1);
v_counter2:=0;
while v_counter2<2
loop
dbms_output.put_line('v_counter2='|| v_counter2);
v_counter2 := v_counter2+1;
end loop;
end loop;

end;
/

