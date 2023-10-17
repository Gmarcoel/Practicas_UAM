-- numpartitipation en imdb_directormovies tiene que ser erradicado o non primary
ALTER TABLE imdb_directormovies
  DROP constraint imdb_directormovies_pkey;

ALTER TABLE imdb_directormovies
    ADD PRIMARY KEY (directorid, movieid);

-- extrainformation in imdb_movielanguages tiene que ser non primary
ALTER TABLE imdb_movielanguages
    DROP constraint imdb_movielanguages_pkey;
ALTER TABLE imdb_movielanguages
	ADD PRIMARY KEY (movieid, "language");


-- podriamos cambiar la relacion entreproducts y imbd_movies por una entidad que las relacione 
CREATE TABLE imdb_productmovies	as (select prod_id, m.movieid from products, imdb_movies m where m.movieid = products.movieid);
alter table imdb_productmovies
	add foreign key (movieid) references imdb_movies(movieid);
alter table imdb_productmovies
	add FOREIGN KEY (prod_id) REFERENCES products(prod_id);
ALTER TABLE imdb_productmovies
    ADD PRIMARY KEY (prod_id, movieid);
ALTER TABLE products
    DROP COLUMN movieid;
-- actorid y movieid en actormovies tienen que ser primary keys
ALTER TABLE imdb_actormovies
    ADD PRIMARY KEY (actorid, movieid);
-- tiene que haber una relacion entre imdb_movies y actormovies y otra de imdb_actors y actormovies
ALTER TABLE imdb_actormovies
    add FOREIGN KEY (movieid) REFERENCES imdb_movies(movieid) ON DELETE cascade;
ALTER TABLE imdb_actormovies
    add FOREIGN KEY (actorid) REFERENCES imdb_actors(actorid) ON DELETE cascade;

-- productid en inventory tiene que tenere una relacion con products
ALTER TABLE inventory
    ADD FOREIGN KEY (prod_id) REFERENCES products(prod_id);

-- creamos tabla que relacione orders con customers
CREATE TABLE orderscustomers as (select orderid, c.customerid from orders, customers as c where orders.customerid = c.customerid);
alter table orderscustomers
	add foreign key (orderid) references orders(orderid);
alter table orderscustomers
	add FOREIGN KEY (customerid) REFERENCES customers(customerid);
ALTER TABLE orderscustomers
    ADD PRIMARY KEY (orderid, customerid);
ALTER TABLE orders
    DROP COLUMN customerid;


-- orderid y prod_id tendrian que estar conectadas con products y orders respectivamente y ser primary keys
CREATE TABLE aux as (select o.orderid, o.prod_id, sum(o.price) as price, sum(o.quantity) as quantity from orderdetail o group by o.orderid, o.prod_id);
DROP TABLE orderdetail;
CREATE TABLE orderdetail as (select * from aux);
DROP TABLE aux;
   
ALTER TABLE orderdetail
    ADD PRIMARY KEY (orderid, prod_id);
ALTER TABLE orderdetail
    ADD FOREIGN KEY (prod_id) REFERENCES products(prod_id);
ALTER TABLE orderdetail
    ADD FOREIGN KEY (orderid) REFERENCES orders(orderid);





-- Funcionalidad añadida para las tablas
--------------------------------------------------------------------------------

-- Una nueva tabla ‘alerts’ para guardar los momentos (fecha/hora) en los que el
--   stock de un producto (inventario) llega a cero.
CREATE TABLE alerts as (SELECT prod_id, LOCALTIMESTAMP as alertdate from inventory where inventory.stock=0);

ALTER TABLE alerts
    ADD PRIMARY KEY (prod_id, alertdate);
    
ALTER TABLE alerts
    ADD FOREIGN KEY (prod_id) REFERENCES products(prod_id);
-- Un campo numérico ‘loyalty’ en la tabla ‘customers’, con valor por defecto cero,
-- para guardar los puntos de fidelización de los clientes.
ALTER TABLE customers
    ADD COLUMN loyalty integer DEFAULT 0;

-- Un campo ‘balance’ en la tabla ‘customers’, para guardar el saldo de los clientes.
AlTER TABLE customers
    ADD COLUMN balance decimal;

-- Crear un procedimiento que inicialice el campo ‘balance’ de la tabla ‘customers’ 
-- a un número aleatorio entre 0 y N, con signatura:
CREATE OR REPLACE FUNCTION setCustomersBalance(IN initialBalance bigint) returns void AS $$
BEGIN
    UPDATE customers
        SET balance = round(cast((random()* initialBalance)as numeric),2);
end; $$

LANGUAGE 'plpgsql';
   
-- Llamar a la funcion setCustomersBalance para inicializar el campo ‘balance’ de la tabla ‘customers’.
select setCustomersBalance(100);



-- Apartado C
------------------------------------------------------------------


-- Una vez se disponga de esta información, realizar un procedimiento almacenado, 
-- setOrderAmount, que complete las columnas 'netamount' (suma de los precios de las 
-- películas del pedido) y 'totalamount' ('netamount' más impuestos) de la tabla 'orders' 
-- cuando éstas no contengan ningún valor. Invocadlo en actualiza.sql para realizar una carga 
-- inicial. 
CREATE OR REPLACE FUNCTION setOrderAmount() returns void AS $$
BEGIN
 UPDATE orders
    SET netamount = q.netamount,
        totalamount = q.totalamount
    FROM    (SELECT orders.orderid, SUM(products.price * orderdetail.quantity) as netamount, SUM(products.price * orderdetail.quantity) + orders.tax as totalamount
                FROM orderdetail, orders, products
                WHERE orders.orderid = orderdetail.orderid and products.prod_id = orderdetail.prod_id
                GROUP BY orders.orderid) AS q
    WHERE orders.orderid = q.orderid;
end; $$
LANGUAGE 'plpgsql';

select setOrderAmount();

-- function to loop between two years and get the top sales

-- 
-- 
-- CREATE OR REPLACE FUNCTION sales(IN year1 integer, IN year2 integer) returns table("Year" integer, film text, sales integer) AS $$
-- BEGIN
--     RETURN QUERY
-- for counter in year1..year2 loop
-- 	raise notice 'counter: %', counter;
--     
--     -- For each year, get the top sales
--     select imdb_movies.movietitle as film, imdb_movies."year" as "Year", sum(inventory.sales) as sales from inventory, imdb_productmovies, imdb_movies 
-- 	    where inventory.prod_id = imdb_productmovies.prod_id 
-- 	        and imdb_movies.movieid = imdb_productmovies.movieid and imdb_movies.year = cast(counter as varchar)
-- 	    group by imdb_movies.movieid
-- 	    order by sales desc
-- 	    limit 1;
-- 
-- 
-- 
--    end loop;
-- END; $$
-- LANGUAGE 'plpgsql';
-- 
-- select * from sales(2018, 2019);
-- 
-- 



-- Para garantizar la integridad de los datos (los valores posibles de las columnas), crear las 
-- tablas correspondientes y convertir los atributos multivaluados ‘moviecountries’, 
-- ‘moviegenres’ y ‘movielanguages’ en relaciones entre la tabla ‘movies’ y las tablas creadas. 
-- Estos cambios también se incorporarán al script actualiza.sql. 
CREATE TABLE languages as (SELECT distinct "language" from imdb_movielanguages);
ALTER TABLE languages ADD PRIMARY KEY ("language");
ALTER TABLE imdb_movielanguages ADD FOREIGN KEY ("language") REFERENCES languages("language");

CREATE TABLE genres as (SELECT distinct genre from imdb_moviegenres);
ALTER TABLE genres ADD PRIMARY KEY (genre);
ALTER TABLE imdb_moviegenres ADD FOREIGN KEY (genre) REFERENCES genres(genre);

CREATE TABLE countries as (SELECT distinct country from imdb_moviecountries);
ALTER TABLE countries ADD PRIMARY KEY (country);
ALTER TABLE imdb_moviecountries ADD FOREIGN KEY (country) REFERENCES countries(country);


-- Hacer que los valores de la tabla customers deje de ser not null
ALTER TABLE customers
    ALTER COLUMN firstname DROP NOT NULL;
ALTER TABLE customers
    ALTER COLUMN lastname DROP NOT NULL;
ALTER TABLE customers
    ALTER COLUMN city DROP NOT NULL;
ALTER TABLE customers
    ALTER COLUMN country DROP NOT NULL;
ALTER TABLE customers
    ALTER COLUMN region DROP NOT NULL;
ALTER TABLE customers
    ALTER COLUMN creditcardtype DROP NOT NULL;
ALTER TABLE customers
    ALTER COLUMN creditcardexpiration DROP NOT NULL;



-- hacer que las ids se generen solas
CREATE SEQUENCE customerid_number
   OWNED BY customers.customerid;

SELECT setval('customerid_number', (SELECT max(customerid) FROM customers));
  
  
ALTER TABLE customers ALTER customerid
   SET DEFAULT nextval('customerid_number');

