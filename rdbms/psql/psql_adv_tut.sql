create table cities (
  name varchar(80)  primary key,
  location point  -- not null -- на left outer join похоже не влияет
);

create table weather (
  city  varchar(80) references cities(name),  -- integrity
  temp_lo  int,
  temp_hi int,
  prcp  real check (prcp >= 0.0),  -- Ограничения для согласованности?
  date date
);
 


-- http://stackoverflow.com/questions/16618299/postgres-copy-from-csv-file-no-such-file-or-directory
--COPY weather FROM './weather.txt';


INSERT INTO cities VALUES ('San Francisco', '(-194.0, 53.0)');


INSERT INTO weather 
  VALUES ('San Francisco', 46, 50, 0.25, '1994-11-27');
INSERT INTO weather (city, temp_lo, temp_hi, prcp, date)
  VALUES ('San Francisco', 43, 57, 0.0, '1994-11-29');
  
/*
INSERT INTO weather (date, city, temp_hi, temp_lo)
  VALUES ('1994-11-29', 'Hayward', 54, 37);

*/



-- BAD STYLE: 'select *' http://www.postgresql.org/docs/8.1/static/tutorial-select.html
select * from weather;
select * from cities;

/*

-- Stage: Views
-- inner join
create view myview as
  select city, temp_lo, temp_hi, prcp, date, location
    from weather, cities
    where city = name;
    
select * from myview;

-- Stage: ref integrity
*/

-- Stage: transactions
-- So transactions must be all-or-nothing not only in terms of their 
-- permanent effect on the database, but also in terms of their 
-- visibility as they happen. 

-- Troubles:
-- TODO: А блокировать то нужно?
-- http://dmitry.miramik.ru/2011/02/17/tranzakcii-i-blokirovka-v-postgresql/
-- http://zarabotai-s-elisespam.ru/?p=401

-- ACID
-- http://stackoverflow.com/questions/3740280/acid-and-database-transactions
-- http://www.lightwolftech.com/index.php?page=backgrounders

-- Stage: Windows
-- http://postgresql.ru.net/manual/tutorial-window.html

create table empsalary (
  depname text,
  empno int,
  salary int,
  avg real
);

insert into empsalary values 
('develop'   ,    11 ,   5200) , --5020.0000000000000000),
('sales'     ,     1 ,   5000) , --4866.6666666666666667),
('develop'   ,     9 ,   4500) , --5020.0000000000000000),
('develop'   ,     8 ,   6000) , --5020.0000000000000000),
('develop'   ,    10 ,   5200) , --5020.0000000000000000),
('personnel' ,     5 ,   3500) , --3700.0000000000000000),
('personnel' ,     2 ,   3900) , --3700.0000000000000000),
('sales'     ,     3 ,   4800) , --4866.6666666666666667),
('develop'   ,     7 ,   4200) , --5020.0000000000000000),
('sales'     ,     4 ,   4800);-- , --4866.6666666666666667);

select * from empsalary;
--select depname, empno, salary, avg(salary)   over(partition by depname) from empsalary;

-- TODO: почему получилось так много строк?
 SELECT depname, empno, salary, avg(salary) 
  OVER (PARTITION BY depname
  --order by salary
  ) FROM empsalary;
 -- Clear
 --drop view myview;
 
 drop table empsalary;
 drop table weather;
 drop table cities;