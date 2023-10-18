ALTER TABLE customers SET (autovacuum_vacuum_threshold=100000000, autovacuum_analyze_threshold=100000000);
ALTER TABLE imdb_actormovies SET (autovacuum_vacuum_threshold=100000000, autovacuum_analyze_threshold=100000000);
ALTER TABLE imdb_actors SET (autovacuum_vacuum_threshold=100000000, autovacuum_analyze_threshold=100000000);
ALTER TABLE imdb_directormovies SET (autovacuum_vacuum_threshold=100000000, autovacuum_analyze_threshold=100000000);
ALTER TABLE imdb_directors SET (autovacuum_vacuum_threshold=100000000, autovacuum_analyze_threshold=100000000);
ALTER TABLE imdb_moviecountries SET (autovacuum_vacuum_threshold=100000000, autovacuum_analyze_threshold=100000000);
ALTER TABLE imdb_moviegenres SET (autovacuum_vacuum_threshold=100000000, autovacuum_analyze_threshold=100000000);
ALTER TABLE imdb_movielanguages SET (autovacuum_vacuum_threshold=100000000, autovacuum_analyze_threshold=100000000);
ALTER TABLE imdb_movies SET (autovacuum_vacuum_threshold=100000000, autovacuum_analyze_threshold=100000000);
ALTER TABLE inventory SET (autovacuum_vacuum_threshold=100000000, autovacuum_analyze_threshold=100000000);
ALTER TABLE orderdetail SET (autovacuum_vacuum_threshold=100000000, autovacuum_analyze_threshold=100000000);
ALTER TABLE orders SET (autovacuum_vacuum_threshold=100000000, autovacuum_analyze_threshold=100000000);
ALTER TABLE products SET (autovacuum_vacuum_threshold=100000000, autovacuum_analyze_threshold=100000000);

