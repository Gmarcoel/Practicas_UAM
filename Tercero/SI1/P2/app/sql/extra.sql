-- select * from orders where status is null


--INSERT INTO orderdetail (orderid, prod_id, price, quantity) VALUES(43531, 198, 110, 2);
--DELETE FROM orderdetail
--WHERE orderid=43531 and prod_id=198;
--update orderdetail 
--set quantity=1
--where prod_id=3427 and orderid=43531;
--SELECT orders.orderid, orderdetail.prod_id, orderdetail.quantity, orderdetail.price ,orders.netamount, orders.totalamount, customers.username FROM customers natural join orderscustomers natural join orders natural join orderdetail where orderid=43531
-- SELECT orderid, prod_id, quantity, price FROM orderdetail where orderid=43531
-- select username, password, customerid, orderid from customers natural join orderscustomers natural join orders where orders.status is null;
-- INSERT INTO orderdetail (orderid, prod_id, price, quantity) VALUES(88699, 198, 30, 1);
-- SELECT orderdetail.price, quantity, movietitle, description, movieid FROM customers natural join orderscustomers natural join orders natural join orderdetail natural join products natural join imdb_productmovies natural join imdb_movies WHERE customerid=6836 and status is NULL;


-- SELECT prod_id FROM orderdetail WHERE orderid=181856 
-- select username from customers where customerid=6036
-- SELECT orderid FROM customers natural join orderscustomers natural join orders WHERE customerid=13539 and orders.status is NULL;
--  SELECT orderid, username, password, customerid FROM customers natural join orderscustomers natural join orders WHERE orders.status is NULL;
-- SELECT prod_id FROM orderdetail WHERE orderid=181869 and prod_id=4760
--select orderid from customers natural join orderscustomers natural join orders WHERE customerid=12499 and orders.status is NULL;
-- select customerid from customers WHERE username='ftp' ;
--SELECT orderid FROM customers natural join orderscustomers natural join orders WHERE customerid=14098 and orders.status is NULL;


select balance from customers where customerid=14099;
        update customers set loyalty = loyalty + (q.price*(5/100)), balance=balance-q.price
        from (
            select totalamount as price, customerid
            from orders natural join orderscustomers
            where customerid=14098 and orders.status is NULL
        ) as q
        where q.customerid = customers.customerid;
select balance from customers where customerid=14099
--select customerid from customers where username='asdasfsdvs'
--SELECT orderid FROM customers natural join orderscustomers natural join orders WHERE customerid=14099 and orders.status is NULL;

--