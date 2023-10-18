-- Crear una consulta, ciudadesDistintas.sql, que muestre el número de ciudades 
-- distintas con clientes que tienen pedidos en un mes dado usando el formato YYYYMM (por 
-- ejemplo 201604) y que además tienen una tarjeta de crédito del tipo ‘VISA’ .
drop index if exists ind;
create index ind on customers(creditcardtype);
create index ind on orders(date_part('month', orders.orderdate));
create index ind on orders(date_part('year', orders.orderdate));
create index ind on orders(date_part('month', orders.orderdate),date_part('year', orders.orderdate));

drop index if exists ind1;
drop index if exists ind2;


create index ind1 on orders(date_part('month', orders.orderdate));
create index ind2 on orders(date_part('year', orders.orderdate));

create index ind2 on orders(date_part('year', orders.orderdate));
create index ind1 on orders(date_part('month', orders.orderdate));

explain select count(distinct(c.city)) from customers c natural join orders o
            where '08' = date_part('month', o.orderdate) 
            and '2016' = date_part('year', o.orderdate)
            and c.creditcardtype = 'VISA'