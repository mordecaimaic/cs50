SELECT DISTINCT(name) from people, movies, stars
WHERE people.id = stars.person_id
AND movies.id = stars.movie_id
AND movies.year = '2004'
ORDER BY people.birth ASC;



-- SELECT name, year from people, movies
-- WHERE people.id in (
--     SELECT person_id FROM stars
--     WHERE movie_id in (
--         SELECT id FROM movies
--         WHERE year = '2004')
--          )
--     ORDER BY name ASC;

