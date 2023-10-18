-- Realizar una función postgreSQL, getTopActors, que reciba un parámetro “género” y que 
-- devuelva los actores o actrices que más veces han actuado en dicho género, ordenados de 
-- más actuaciones a menos, siempre que hayan trabajado en más de 4 películas de ese 
-- género, con información de la película en la que debutaron para ese género, el año de esa 
-- película y quién (o quiénes) dirigió esa película (pueden aparecer varios registros para el 
-- mismo actor porque hizo varias películas su primer año, varios directores para la misma 
-- película, etc.) 
CREATE OR REPLACE FUNCTION getTopActors(genre CHAR) RETURNS TABLE (Actor VARCHAR, Num bigint, Debut TEXT,  Film VARCHAR, Director VARCHAR) AS $$
BEGIN
    RETURN QUERY
    select firstquery.actorname as Actor, firstquery.cont as Num, secondquery.debut as Debut, secondquery.film as Film, secondquery.director as Director from
    (
    -- actor genero y pelis por genero si <4 se elimina del resultado
    select q.Actor, q.cont, q.actorname from 
        (select imdb_actors.actorid as Actor, count(*) as cont, imdb_actors.actorname as actorname
            from imdb_actors, imdb_actormovies, imdb_movies, imdb_moviegenres
            where imdb_moviegenres.movieid = imdb_movies.movieid 
            and imdb_movies.movieid = imdb_actormovies.movieid
            and imdb_actors.actorid = imdb_actormovies.actorid
            and imdb_moviegenres.genre = $1
            group by imdb_actors.actorid
        ) as q
        where q.cont > 4
    ) as firstquery,
    (
    -- primera pelicula de cada actor y genero de la pelicula titulo a 
    select distinct on (imdb_actormovies.actorid) imdb_actormovies.actorid as Actor, imdb_movies.movietitle as film, imdb_movies.year as debut, imdb_directors.directorname as director
        from imdb_movies, imdb_actormovies, imdb_moviegenres, imdb_directors, imdb_directormovies
        where imdb_movies.movieid=imdb_actormovies.movieid
        and imdb_moviegenres.movieid=imdb_movies.movieid
        and imdb_movies.movieid=imdb_directormovies.movieid
        and imdb_directormovies.directorid=imdb_directors.directorid
        and imdb_moviegenres.genre = $1
        group by imdb_actormovies.actorid, imdb_movies.movietitle, imdb_movies.year, imdb_movies.movieid, imdb_directors.directorname
        order by imdb_actormovies.actorid, imdb_directors.directorname, imdb_movies.year
    ) as secondquery
    where firstquery.Actor = secondquery.Actor
    order by num desc;
END; $$
LANGUAGE 'plpgsql';

-- select * from getTopActors('Action');


