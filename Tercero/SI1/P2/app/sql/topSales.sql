-- Realizar una función postgreSQL, getTopSales, que reciba como argumentos dos años 
-- diferentes y devuelva las películas que más se han vendido entre esos dos años, una por 
-- año, ordenadas de mayor a menor por número de ventas. 
CREATE OR REPLACE FUNCTION getTopSales(IN year1 integer, IN year2 integer) returns table("year" text, movie varchar, sales bigint, id integer) AS $$
BEGIN
    RETURN QUERY 
    SELECT distinct
        ON (imdb_movies.year) imdb_movies.year as "year",  imdb_movies.movietitle as movie, sum(inventory.sales) as sales, imdb_movies.movieid as id
        from inventory, imdb_productmovies, imdb_movies 
	    where inventory.prod_id = imdb_productmovies.prod_id 
	        and imdb_movies.movieid = imdb_productmovies.movieid
            and imdb_movies.year >= cast(year1 as text) and imdb_movies.year <= cast(year2 as text)
	    group by imdb_movies.year, imdb_movies.movietitle, imdb_movies.movieid
	    order by imdb_movies.year, sales desc;
END; $$
LANGUAGE 'plpgsql';

-- select * from getTopSales(1998, 2015);

