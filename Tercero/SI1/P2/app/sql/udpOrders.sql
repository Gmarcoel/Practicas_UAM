drop function if exists updateOrder();
-- Funcion updateOrder()
create function updateOrder() returns trigger as $$
begin
    -- Actualizar la información de la tabla 'orders'
    -- Si se elimina un artículo del carrito, actualizar la información de la tabla 'orders'
    if(new.quantity=0) then
        delete from orders where orders.orderid = new.orderid;
    end if;
    if (old.orderid is not null) then
        update orders set total = (select sum(price * quantity + taxes) from orderdetail where orderdetail.orderid = old.orderid and orderdetail.productid = new.productid)
            where orders.orderid = old.orderid;
    end if;
    -- Si 

    return new;
end;
$$ language plpgsql;

-- Realizar un trigger, updOrders, que actualice la información de la tabla 'orders' cuando se 
-- añada, actualice o elimine un artículo del carrito. 
create trigger updOrders before insert or update or delete on orderdetail for each row execute procedure updateOrder();
