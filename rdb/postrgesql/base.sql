-- http://stackoverflow.com/questions/1766046/postgresql-create-table-if-not-exists
-- create table people (
--        id              integer,
--        firstname       varchar(20),
--        lastname        varchar(20),
--        phonenumber     char(10)
--);

insert into people (id, firstname, lastname, phonenumber) values 
	(1, 'Fred', 'Flin', '123');

select * from people;