-- Realizar un trigger, updInventoryAndCustomer, explicando de forma adecuada en la 
-- memoria cuándo dispararlo, que realice las siguientes tareas:  
-- actualice las tablas ‘orders’ e 'inventory' 
-- cree una alerta en la tabla 'alertas' para aquellos productos comprados cuya cantidad en 
-- stock en el inventario llega a cero  
-- sume los puntos de fidelización conseguidos por la compra en la tabla ‘customers’ 
-- descuente en la tabla ‘customers’ el precio total de la compra

drop function if exists updInventoryAndCustomer() cascade;

create function updInventoryAndCustomer() returns trigger as $$
begin
    if old.status is null and new.status is not null then
    -- actualice las tablas ‘orders’ e 'inventory' 
        update orders set orderdate = now() where orderid = new.orderid;
        update inventory set stock = stock - q.quantity 
        from( select quantity, prod_id from orderdetail where orderdetail.orderid=new.orderid) as q
        where q.prod_id = inventory.prod_id;
    -- cree una alerta en la tabla 'alertas' para aquellos productos comprados cuya cantidad en 
    -- stock en el inventario llega a cero     
        insert into alerts(prod_id)
        select q.prod_id
        from (
            select inventory.prod_id, inventory.stock
            from orderdetail natural join products natural join inventory 
            where orderdetail.orderid = new.orderid
        ) as q
        where q.stock <= 0;
        -- sume los puntos de fidelización conseguidos por la compra en la tabla ‘customers’ 
        -- descuente en la tabla ‘customers’ el precio total de la compra
        
        update customers set loyalty = loyalty + (q.price*(5/100)), balance=balance-q.price
        from (
            select totalamount as price, customerid
            from orders natural join orderscustomers
            where orders.orderid=new.orderid
        ) as q
        where q.customerid = customers.customerid;
    end if;
    return new;

end;
$$ 
language plpgsql;



drop trigger updInventoryAndCustomer on orders;
create trigger updInventoryAndCustomer after update on orders for each row execute procedure updInventoryAndCustomer();
