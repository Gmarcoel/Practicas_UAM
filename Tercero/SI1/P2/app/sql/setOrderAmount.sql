

-- Apartado C
------------------------------------------------------------------


-- Una vez se disponga de esta información, realizar un procedimiento almacenado, 
-- setOrderAmount, que complete las columnas 'netamount' (suma de los precios de las 
-- películas del pedido) y 'totalamount' ('netamount' más impuestos) de la tabla 'orders' 
-- cuando éstas no contengan ningún valor. Invocadlo en actualiza.sql para realizar una carga 
-- inicial. 
drop function if exists setOrderAmount() cascade;
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

