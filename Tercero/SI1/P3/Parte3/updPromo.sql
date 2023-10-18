-- Crear un script updPromo.sql, que creará una nueva columna, promo, en la tabla
-- customers. Esta columna contendrá un descuento (en porcentaje) promocional
ALTER TABLE customers ADD COLUMN promo NUMERIC(4, 2);


-- Añadir al script la creación de un trigger sobre la tabla customers de forma que al alterar
-- la columna promo de un cliente, se le haga un descuento en los artículos de su cesta o
-- carrito del porcentaje indicado en la columna promo sobre el precio de la tabla products.


CREATE OR REPLACE FUNCTION updPromo() RETURNS TRIGGER 
AS $$
BEGIN
    PERFORM PG_SLEEP(10);
    update orders set totalamount = totalamount * (1 - NEW.promo / 100)
    where customerid = NEW.customerid and status = NULL;
    return NEW;
END;
$$ language 'plpgsql';

drop trigger promoTrigger on customers
CREATE TRIGGER promoTrigger AFTER UPDATE ON customers FOR EACH ROW EXECUTE PROCEDURE updPromo()




update customers set promo = 50 where customerid = 12116