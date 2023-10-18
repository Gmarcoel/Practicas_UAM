drop function if exists updateOrder() cascade;
-- Funcion updateOrder()
create function updateOrder() returns trigger as $$
begin
    -- Actualizar la información de la tabla 'orders'
    -- Si se elimina un artículo del carrito, actualizar la información de la tabla 'orders'

    if (tg_op = 'DELETE') then    
            update orders 
            set totalamount =  tax + (cost-(old.quantity*old.price)), netamount = (cost-(old.quantity*old.price))
            from (
                select orderid, sum(price*quantity) as cost 
                from orderdetail 
                where orderid = old.orderid
                group by orderid
            ) as q
            where orders.orderid = old.orderid;
        return old;
    elsif (tg_op = 'INSERT') then
        update orders 
        set totalamount = tax + (cost+(new.quantity*new.price)), netamount = (cost+(new.quantity*new.price))
        from (
            select orderid, sum(price*quantity) as cost 
            from orderdetail 
            where orderid = new.orderid
            group by orderid
        ) as q, 
        where orders.orderid = new.orderid;
        return new;
    

    elsif (tg_op = 'UPDATE') then
        update orders 
        set totalamount = tax + (cost+((new.quantity-old.quantity)*new.price)), netamount = (cost+((new.quantity-old.quantity)*new.price))
        from (
            select orderid, sum(price*quantity) as cost 
            from orderdetail 
            where orderid = new.orderid
            group by orderid
        ) as q
        where orders.orderid = new.orderid;
        return new;
    
    
    end if;
    -- Si 

    return new;
end;
$$ language plpgsql;

-- Realizar un trigger, updOrders, que actualice la información de la tabla 'orders' cuando se 
-- añada, actualice o elimine un artículo del carrito. 

drop trigger updOrders on orderdetail;
create trigger updOrders before insert or update or delete on orderdetail for each row execute procedure updateOrder();
