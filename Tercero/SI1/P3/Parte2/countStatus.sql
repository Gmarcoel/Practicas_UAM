-- Sin índice --
----------------

drop index if exists con1_index;
-- Consulta 1
explain select count(*) 
	from orders where status is null;  
-- Consulta 2
explain select count(*) from orders where status ='Shipped'; 

-- Creación índice --
---------------------
drop index if exists con1_index;
create index con1_index on orders(status)
-- Consulta 1
explain select count(*) 
from orders where status is null;  
-- Consulta 2
explain select count(*) from orders where status ='Shipped'; 

-- Analize --
-------------
analyze verbose orders

-- Consulta 1
explain select count(*) 
	from orders 
	where status is null;

-- Consulta 2
explain select count(*) 
	from orders 
	where status ='Shipped'; 


-- Consulta 3
explain select count(*) from orders 
	where status ='Paid';  

-- Consulta 4
explain select count(*) from orders 
	where status ='Processed'; 