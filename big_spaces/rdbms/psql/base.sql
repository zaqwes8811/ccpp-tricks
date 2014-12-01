-- tut:
-- http://www.tutorialspoint.com/dbms/dbms_overview.htm

CREATE TABLE IF NOT EXISTS COMPANY(
ID INT PRIMARY KEY  NOT NULL,
NAME TEXT NOT NULL,
AGE INT NOT NULL,
ADDRESS CHAR(10),
SALARY REAL
, JOIN_DATE	  DATE
);

CREATE TABLE IF NOT EXISTS DEPARTMENT(
ID INT PRIMARY KEY NOT NULL,
DEPT  CHAR(50) NOT NULL,
EMP_ID  INT NOT NULL
);

insert into company (id, name, age, address, salary, join_date)
  values (1, 'Paul', 32, 'calif', 200.0, '2001-07-13');
  
-- отбрасывает если одинаковый id, но продолжает выполнение
insert into company (id, name, age, address, salary, join_date)
  values (2, 'Paul', 32, 'calif', 200.0, default),
         (5, 'David', 27, 'Texas', 85000.00 , '2007-12-13');

select * from COMPANY;


DROP TABLE COMPANY;
DROP TABLE DEPARTMENT;