create database 'D:\firma_copy.fdb'
user 'SYSDBA' password 'masterkey'
page_size = 4096
default character set win1251;

CREATE TABLE s(
	id INTEGER NOT NULL PRIMARY KEY,
	fio VARCHAR(20),
	money INTEGER,
	city VARCHAR(15)
);

CREATE TABLE p(
	id INTEGER NOT NULL PRIMARY KEY,
	name VARCHAR(20),
	color VARCHAR(15),
	weight INTEGER,
	city VARCHAR(20)
);

CREATE TABLE sp(
	id_post INTEGER,
	id_det INTEGER,
	quantity INTEGER
);


ALTER TABLE sp
	ADD CONSTRAINT id_post FOREIGN KEY(id_post)
	REFERENCES s(id)
	ON DELETE CASCADE
	ON UPDATE CASCADE
;
ALTER TABLE sp
	ADD CONSTRAINT id_det FOREIGN KEY(id_det)
	REFERENCES p(id)
	ON DELETE CASCADE
	ON UPDATE CASCADE
;

INSERT INTO s
	VALUES(1, 'Ivanov I.I.', 50000, 'London');
INSERT INTO s
	VALUES(2, 'Petrov P.P.', 20000, 'Moskva');
INSERT INTO s
	VALUES(3, 'Sidorov S.S.', 150000, 'Kerch');
INSERT INTO s
	VALUES(4, 'Vasilev V.V.', 300000, 'London');
INSERT INTO s
	VALUES(5, 'Semenov S.S.', 70000, 'Kerch');

INSERT INTO p
	VALUES(1, 'Bolt', '#000000', 34, 'Kerch');
INSERT INTO p
	VALUES(2, 'Vint', '#ff0000', 67, 'Kerch');
INSERT INTO p
	VALUES(3, 'Gayka_mal', '#ffff00', 18, 'London');
INSERT INTO p
	VALUES(4, 'Gvozd', '#ffffff', 56, 'Kerch');
INSERT INTO p
	VALUES(5, 'Vtulka', '#00ff00', 90, 'Moskva');

INSERT INTO sp VALUES(2,3,120);
INSERT INTO sp VALUES(2,4,190);
INSERT INTO sp VALUES(2,5,15);
INSERT INTO sp VALUES(1,4,18);
INSERT INTO sp VALUES(3,5,190);
INSERT INTO sp VALUES(5,5,200);
INSERT INTO sp VALUES(1,5,100);
INSERT INTO sp VALUES(2,2,20);
INSERT INTO sp VALUES(3,1,150);
INSERT INTO sp VALUES(4,3,30);
INSERT INTO sp VALUES(5,4,18);
INSERT INTO sp VALUES(2,1,25);
INSERT INTO sp VALUES(1,3,14);
INSERT INTO sp VALUES(4,5,22);
INSERT INTO sp VALUES(1,2,67);
INSERT INTO sp VALUES(3,3,15);
INSERT INTO sp VALUES(4,1,18);
INSERT INTO sp VALUES(5,1,217);


SELECT id_det FROM sp;


ALTER TABLE p ADD bank_account INTEGER;


SELECT * FROM s
	WHERE 'London' NOT LIKE city;


SELECT id, money FROM s
	WHERE city = 'Moskva';


SELECT id, money FROM s
	WHERE 'Paris' LIKE city AND
	money < 50000
	ORDER BY money DESC;


SELECT * FROM s;


SELECT * FROM p
	WHERE weight >= 30 AND
	weight <= 60;


SELECT id, weight*1000 AS weight_g, 'gr.' FROM p;


SELECT id FROM p
	WHERE weight = 12 OR
	weight = 18 OR 
	weight = 34;


SELECT * FROM p
	WHERE LEFT(name,1) = 'G';


SELECT * FROM p
	WHERE RIGHT(name,1) = 't';


SELECT * FROM p
	WHERE POSITION('o', 
	SUBSTRING(name 
	FROM 1 FOR (CHAR_LENGTH(name)-1))) <> 0;


SELECT * FROM p
	WHERE POSITION('l', name) = 3;


SELECT * FROM p
	WHERE POSITION('_', name) <> 0;


SELECT * FROM p JOIN s
	ON p.city = s.city;


SELECT * FROM p, s 
	WHERE p.city = s.city;


UPDATE p
	SET color = '#ffff00',
	weight = weight + 5,
	city = NULL
		WHERE id = 2;
		SELECT * FROM p 
			WHERE id = 2;


ALTER TABLE p DROP bank_account;
SHOW TABLE p;


UPDATE s
	SET money = money * 2
		WHERE city = 'London';
		SELECT * FROM s 
			WHERE city = 'London';


DELETE FROM s 
	WHERE city = 'London';
	SELECT * FROM s;


INSERT INTO p
	VALUES(6,'Lenta','#ff9900',NULL,'Minsk');
	SELECT * FROM p;


SELECT id FROM p
	WHERE weight IS NULL;


SELECT COUNT(DISTINCT id_post) 
	FROM sp;


SELECT id_det, SUM(quantity) 
	FROM sp 
	GROUP BY id_det;


SELECT id_det, SUM(quantity) 
	FROM sp 
		WHERE id_post <> 3 
		GROUP BY id_det;


SELECT DISTINCT id_det 
	FROM sp AS o 
		WHERE EXISTS(
		SELECT * FROM sp AS i 
			WHERE i.id_det = o.id_det
			AND i.id_post <> o.id_post);

SELECT s.fio, sp.id_det, sp.quantity
	FROM s JOIN sp
	on sp.id_post = s.id
	ORDER BY s.id;

SELECT s.fio, sp.id_det, sp.quantity 
	FROM s,sp
		WHERE sp.id_post = s.id 
		ORDER BY s.id;


SELECT s.fio, p.name 
	FROM s,p,sp
		WHERE sp.id_det = p.id 
		AND sp.id_post = s.id 
		ORDER BY s.id;


SELECT DISTINCT a.fio
	FROM s a, s b
		WHERE a.city = b.city 
		AND NOT(a.fio = b.fio);


SELECT fio 
	FROM s
		WHERE id IN (
		SELECT id_post 
			FROM sp WHERE id_det = 1);


SELECT fio 
	FROM s
		WHERE id IN (
		SELECT id_post FROM sp
			WHERE id_det IN (
			SELECT id FROM p 
				WHERE color = '#FF0000'));


SELECT DISTINCT sp.id_post, s.fio
	FROM sp, s
	WHERE sp.id_det IN
		(SELECT sp.id_det
			FROM sp
			WHERE sp.id_post = 3);


SELECT id FROM s 
	WHERE EXISTS(SELECT * 
		FROM sp
		WHERE s.id = sp.id_post);


SELECT id FROM s 
	WHERE id NOT IN (
	SELECT id_post FROM sp);
SELECT id FROM s 
	WHERE NOT EXISTS(
	SELECT * FROM sp 
		WHERE s.id = sp.id_post);


SELECT id, fio FROM s
	WHERE id IN (
	SELECT id_post 
		FROM sp 
		GROUP BY id_post
			HAVING COUNT(DISTINCT id_det) = (
			SELECT COUNT(id) FROM p));



SELECT id FROM p
	WHERE id IN(
	SELECT id_det FROM sp
		WHERE NOT(id_post = 1));


SELECT id FROM p
	WHERE id IN(
	SELECT sp.id_det, p.id FROM sp, p 
		WHERE (sp.id_post = 3) OR (p.weight > 34));


SELECT name FROM p
	WHERE id IN(
	SELECT id_det FROM sp
		WHERE id_post = 2);


SELECT id FROM s
	WHERE money < (
	SELECT MAX(money) FROM s);


SELECT id, money, city FROM s a
	WHERE money >= (
	SELECT AVG (money) FROM s b 
		WHERE b.city = a.city);


CREATE TABLE for_time(
	id_det CHAR (6),
	amount INTEGER);
	
INSERT INTO for_time (id_det, amount)	
	SELECT id_det, SUM(quantity)
		FROM sp
		GROUP BY id_det;


SELECT p.name, s.fio, MAX(sp.quantity)
	FROM sp, p, s
	WHERE p.id = sp.id_det AND s.id = sp.id_post
		GROUP BY p.name, s.fio, sp.quantity
		ORDER BY sp.quantity;
		
SELECT p.name, s.fio, max(sp.quantity)
FROM sp join p
on p.id = sp.id_det
join s 
on s.id = sp.id_post
group by p.name, s.fio, quantity
order by quantity;

select s.fio, p.color
from s, p
where s.city = 'Kerch'
group by s.fio, p.color;

SELECT id_det, SUM(quantity) FROM sp
	WHERE id_det IN(
	SELECT id FROM p 
		WHERE NOT(p.name = 'Petlya'))
		GROUP BY id_det;
		
SELECT id FROM p
	WHERE id IN(
	SELECT id_det FROM sp
		WHERE NOT(id_post = 1));
		
SELECT fio, city FROM s
	WHERE id IN(
		SELECT id_post FROM sp
		GROUP BY id_post
		COUNT(DISTINCT id_det));
			
			
			HAVING COUNT(DISTINCT id_det) = (
			SELECT COUNT(id) FROM p));

SELECT id, money FROM s
	WHERE 'Paris' LIKE city AND
	money < 50000
	ORDER BY money DESC;

SELECT id, fio FROM s
	WHERE id IN (
	SELECT id_post 
		FROM sp 
		GROUP BY id_post
			HAVING COUNT(DISTINCT id_det) = (
			SELECT COUNT(id) FROM p));

SELECT fio, city, COUNT(id_det) FROM s, sp
WHERE id = id_post
GROUP BY fio, city
ORDER BY COUNT(DISTINCT id_det) ASC;

