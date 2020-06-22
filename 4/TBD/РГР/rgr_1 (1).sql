create database 'c:\firebird-learn\firma.fdb'
user 'sysdba' password 'masterkey'
page_size = 4096
default character set win1251;

create table s(
	id integer not null primary key,
	fio varchar(30),
	money integer,
	city varchar(15)
);

create table p(
	id integer not null primary key,
	name varchar(20),
	color varchar(15),
	weight integer,
	city varchar(20)
);

create table sp(
	id_post integer,
	id_det integer,
	quantity integer
);

-- добавляем связи между таблицами
alter table sp
	add constraint id_post foreign key(id_post)
	references s(id)
	on delete cascade
	on update cascade
;
alter table sp
	add constraint id_det foreign key(id_det)
	references p(id)
	on delete cascade
	on update cascade
;

insert into s
values('1','Иванов И. И.', '50000', 'Лондон');
insert into s
values('2','Петров П. П.', '20000', 'Москва');
insert into s
values('3','Сидоров С. С.', '150000', 'Париж');
insert into s
values('4','Васильев В. В.', '300000', 'Лондон');
insert into s
values('5','Семенов С. С.', '70000', 'Киев');

insert into p
values('1','Болт','#000000','34','Киев');
insert into p
values('2','Винт','#ff0000','67','Киев');
insert into p
values('3','Гайка_мал','#ffff00','18','Лондон');
insert into p
values('4','Гвоздь','#ffffff','56','Париж');
insert into p
values('5','Петля','#00ff00','90','Москва');

insert into sp
values('2','3','120');
insert into sp
values('2','4','190');
insert into sp
values('2','5','15');
insert into sp
values('1','4','18');
insert into sp
values('3','5','190');
insert into sp
values('1','5','100');
insert into sp
values('2','2','20');
insert into sp
values('3','1','150');
insert into sp
values('4','3','30');
insert into sp
values('5','4','18');
insert into sp
values('2','1','25');
insert into sp
values('1','3','14');
insert into sp
values('4','5','22');
insert into sp
values('1','2','67');
insert into sp
values('3','3','15');
insert into sp
values('4','1','18');
insert into sp
values('5','1','217');
commit;
--3)
select id_det from sp;
commit;
--4)
alter table p
add bank_account integer;
commit;
--5)
select * from s
where 'Лондон' not like city;
commit;
--6)
select id, money from s
where city = 'Москва';
commit;
--7)
select id, money from s
where 'Париж' like city and
money < 50000
order by money desc;
commit;
--8)
select * from s;
commit;
--9)
select * from p
where weight >= 30 and
weight <= 60;
commit;
--10)вес деталей в граммах
select id, weight*1000 as weight_g, 'гр.'  from p;
commit;
--11)
select id from p
where weight = 12 or
weight = 18 or 
weight = 34;
commit;
--12)начинается на Г (название детали)
select * from p
where left(name,1) = 'Г';
commit;
--13)кончается на т (название детали)
select * from p
where right(name,1) = 'т';
commit;
--14)есть буква о в середине строки (название детали)
select * from p
where position('о', substring(name from 1 for (CHAR_LENGTH(name)-1))) <> 0;
commit;
--15)л на третьей позиции в строке (название детали)
select * from p
where position('л', name) = 3;
commit;
--16)есть _ в названии детали
select * from p
where position('_', name) <> 0;
commit;
--17.1)комбинации о деталях и поставщиках в одном городе с помощью join
select * 
from p join s
on p.city = s.city;
commit;
--17.2)комбинации о деталях и поставщиках в одном городе без join
select * 
from p, s 
where p.city = s.city;
commit;
--18)изменение строки в таблице деталей
UPDATE p
SET color = '#ffff00',
weight = weight + 5,
city = null
WHERE id = 2;
-- вывод измененной строки
select * from p 
where id = 2;
commit;
--19)удалить колонку счет в банке из таблицы p
alter table p drop bank_account;
show table p;
commit;
--20)удвоить состояние поставщиков в Лондоне
UPDATE s
SET money = money * 2
WHERE city = 'Лондон';
-- вывод изменений
select * from s 
where city = 'Лондон';
commit;
--21)удалить поставщиков из Лондона
delete from s 
where city = 'Лондон';
select * from s;
commit;
--22)добавить запись в таблицу p
insert into p
values('6','Лента','#ff9900',null,'Минск');
select * from p;
commit;
--23)вывести номер детали где не определено значение веса
select id from p
where weight is null;
commit;
--24)Выдать общее количество поставщиков, поставляющих в настоящее время детали
select count(distinct id_post) from SP;
commit;
--25)Для каждой поставляемой детали выдать её номер и объем поставок.
select id_det, sum(quantity) from SP group by id_det;
commit;
--26)Для каждой детали выдать её номер и объем поставок за исключением поставщика под номером 
select id_det, sum(quantity) from SP where id_post <> 3 group by id_det;
commit;
--27)Выдать номера деталей для всех деталей, поставляемых более чем одним поставщиком
select distinct id_det from SP as o where exists(
select * from SP as i where i.id_det = o.id_det
and i.id_post <> o.id_post);
commit;
--29)Вывести информацию об именах поставщиков и о том, в каком количестве и какие детали они поставляют
SELECT S.FIO, SP.id_det, SP.Quantity FROM S,SP
WHERE SP.id_post = S.id ORDER BY S.id;
commit;

SELECT S.FIO, SP.id_det, SP.Quantity 
FROM S join SP
on SP.id_post = S.id 
ORDER BY S.id;

--30)Вывести информацию об имени поставщика и названии деталей, которые он поставляет
SELECT S.FIO, P.Name FROM S,P,SP
WHERE SP.id_det = P.id AND SP.id_post = S.id ORDER BY S.id;

SELECT S.FIO, P.Name 
FROM SP join P
on SP.id_det = P.id 
join S
on SP.id_post = S.id 
ORDER BY S.id;

--31)Вывести все пары поставщиков, живущих в одном городе. Исключить комбинации продавцов с ними же, а также дубликаты строк, выводимые в обратном порядке
select distinct a.fio
from s a, s b
where a.city = b.city and not(a.fio =b.fio);

select distinct a.fio
from s as a join s as b
on a.city = b.city and not(a.fio =b.fio);

commit;
--32)Вывести фамилии всех поставщиков, которые поставляют детали с номером 1
SELECT id, FIO FROM S
WHERE id IN (SELECT id_post FROM SP WHERE id_det=1);
commit;
--33)Вывести фамилии поставщиков, которые поставляют, по крайней мере, одну красную деталь
select id, fio from s
where id in (select id_post from sp
where id_det in (select id from p where color = '#FF0000'));
commit;
--34)Вывести номера и фамилии поставщиков, которые поставляют по крайней мере одну деталь, поставляемую поставщиком 3
SELECT DISTINCT sp.id_post, s.fio
FROM sp, s
WHERE sp.id_det IN
  (SELECT sp.id_det
  FROM sp
  WHERE sp.id_post = 3);
  
  SELECT DISTINCT sp.id_post, s.fio
FROM sp join s
on sp.id_post = s.id
WHERE sp.id_det IN
  (SELECT sp.id_det
  FROM sp
  WHERE sp.id_post = 3);

commit;
--35)Вывести номера поставщиков, для которых в базе существует информация о номерах поставляемых деталей.
SELECT id FROM S WHERE EXISTS(SELECT * FROM SP
WHERE S.id=SP.id_post);
commit;
--36)Вывести номера поставщиков, для которых не существует информация о номерах поставляемых деталей
select id from S where id not in (select id_post from SP);
select id from S where not exists(select * from SP where S.id = SP.id_post);
commit;
--37)Вывести номера поставщиков, которые поставляют все детали
SELECT id, FIO FROM S
WHERE id IN (SELECT id_post FROM SP GROUP BY id_post
HAVING COUNT(DISTINCT id_det) = (SELECT COUNT(id) FROM P));

commit;
--38)Вывести номера только тех деталей, которые не поставляет поставщик 1
select id from p
where id in(select id_det from sp
where not (id_post = 1));
commit;
--39)Вывести номера деталей, которые имеют вес больше 34 или поставляются поставщиком 3
select id from p
where id in(select sp.id_det, p.id from sp, p 
where (sp.id_post = 3) or (p.weight > 34));
commit;
--40)Вывести названия деталей, которые поставляет поставщик с номером 2
select name from p
where id in(select id_det from sp
where id_post = 2);
commit;
--41)Вывести номера поставщиков с состоянием меньшим, чем текущее максимальное состояние в таблице поставщиков
Select id from S
where money < (Select max(money) from S);
commit;
--42)Выдать номера, состояние и город для всех поставщиков, у которых состояние равно или больше среднего по городу
SELECT id, money, city FROM S a
WHERE money >= (SELECT AVG (money) FROM S b 
WHERE b.city = a.city);
commit;
--43)Для каждой поставляемой детали получить её номер и общий объём поставок. Сохранить результат в новой таблице
CREATE TABLE for_time
(id_det CHAR (6),
amount INTEGER);
INSERT
INTO for_time (id_det, amount)
SELECT id_det, SUM (quantity)
FROM SP
GROUP BY id_det;
commit;
--44)Вывести имена поставщиков и названия деталей, которые поставляются в наибольшем объеме.
SELECT p.name, s.fio, max(sp.quantity)
FROM sp, p, s
where p.id = sp.id_det and s.id = sp.id_post
group by p.name, s.fio
order by max(quantity);

SELECT p.name, s.fio, max(sp.quantity)
FROM sp join p
on p.id = sp.id_det
join s 
on s.id = sp.id_post
group by p.name, s.fio
order by quantity;


-- конец --------------------------------------------------------------------------------------------------------

