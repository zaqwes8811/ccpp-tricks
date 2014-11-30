-- copy and edit: 
-- http://www.postgresql.org/docs/8.1/static/tutorial-table.html
--
-- TODO: load table from file.
--
create table weather (
  -- TODO: where is primary key?
  city  varchar(80),
  temp_lo  int,
  temp_hi int,
  prcp  real,
  date date
);
 
create table cities (
  name varchar(80),
  location point  -- not null -- на left outer join похоже не влияет
);

-- http://stackoverflow.com/questions/16618299/postgres-copy-from-csv-file-no-such-file-or-directory
--COPY weather FROM './weather.txt';

INSERT INTO weather 
  VALUES ('San Francisco', 46, 50, 0.25, '1994-11-27');
INSERT INTO weather (city, temp_lo, temp_hi, prcp, date)
  VALUES ('San Francisco', 43, 57, 0.0, '1994-11-29');
INSERT INTO weather (date, city, temp_hi, temp_lo)
  VALUES ('1994-11-29', 'Hayward', 54, 37);


INSERT INTO cities VALUES ('San Francisco', '(-194.0, 53.0)');


-- BAD STYLE: 'select *' http://www.postgresql.org/docs/8.1/static/tutorial-select.html
select * from weather;
select * from cities;

-- Можно создавать временный столбец?
select city, (temp_hi+temp_lo)/2 as temp_avg, date from weather;
select * from weather
  where city = 'San Francisco' and prcp > 0.0;

select * from weather
  order by city;
  
-- http://stackoverflow.com/questions/15628277/sql-order-by-multiple-columns
select * from weather
  order by city, temp_lo;
  
select distinct city from weather;

-- Coupling tables 

--
-- Можно соединят таблицы !!или по особому обходить одну таблицу
select * from weather, cities where city = name;

-- with filtration
SELECT city, temp_lo, temp_hi, prcp, date, location
    FROM weather, cities
    ;
    --WHERE city = name;  -- DANGER: произошла странная вещь - таблица расширилась, но не правильно!
    
-- http://stackoverflow.com/questions/38549/difference-between-inner-and-outer-joins
-- http://blog.codinghorror.com/a-visual-explanation-of-sql-joins/
-- Ключевые моменты - Mathced and AllFrom
select * from weather;
select * from cities;
--print 'Mult';
--RAISE INFO 'col1      col2';
select * from weather inner join cities on (weather.city = cities.name);  -- пересеение - Mult

-- !all from left and !!matched from right
-- правая заполняется по соответствию, либо заоплняется нулями
select * from weather left outer join cities on (weather.city = cities.name);  
--select * from weather right outer join cities on (weather.city = cities.name);

-- объединение - Union
--select * from weather full outer join cities on weather.city = cities.name;-- is null;
-- select * from on ... where some is null
 
-- self-join
-- запрос чего 
--SELECT 
--  W1.city, W1.temp_lo AS low, W1.temp_hi AS high, W2.city, W2.temp_lo AS low, W2.temp_hi AS high
  
--  FROM weather W1, weather W2
--  WHERE W1.temp_lo < W2.temp_lo AND W1.temp_hi > W2.temp_hi; -- свойство одного кортежа?

-- Stage: AGGREGATE FUNCTIONS
-- какая минималльная температура максимальна?
select max(temp_lo) from weather;
-- в каком городе?
-- select city from weather where temp_lo = max(temp_lo);  -- WRONG
select city from weather
  where temp_lo = (select max(temp_lo) from weather);
  
-- по конкретному городу
select city, max(temp_lo)
  from weather
  group by city--;  -- сжатие по этому тегу
  having max(temp_lo) < 40;  -- TODO: это работает?
  
/*"It is important to understand the interaction between aggregates and 
SQL's WHERE and HAVING clauses. The fundamental 
difference between WHERE and HAVING is this: 
WHERE selects input rows before groups and 
aggregates are computed (thus, it controls which 
rows go into the aggregate computation), whereas HAVING 
selects group rows after groups and aggregates are computed. 
Thus, the WHERE clause must not contain aggregate functions; 
it makes no sense to try to use an aggregate to determine 
which rows will be inputs to the aggregates. On the other hand, 
the HAVING clause always contains aggregate functions. 
(Strictly speaking, you are allowed to write a HAVING 
clause that doesn't use aggregates, but it's seldom useful. 
The same condition could be used more efficiently at the WHERE stage.)"*/

-- Stage: MODIFICATONS
select * from weather;
update weather
  set temp_hi = temp_hi - 2, temp_lo = temp_lo - 2
  where date > '1994-11-28';
select * from weather;

delete from weather where city = 'Hayward';
select * from weather;

 -- Clear
 drop table weather;
 drop table cities;