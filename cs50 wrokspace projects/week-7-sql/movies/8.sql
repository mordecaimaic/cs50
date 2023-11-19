SELECT name from people, movies, stars
WHERE people.id = stars.person_id
AND movies.id = stars.movie_id
AND movies.title = 'Toy Story';

-- SELECT name from people
-- WHERE people.id in (
--     SELECT person_id FROM stars
--     WHERE movie_id = (
--         SELECT id FROM movies
--         WHERE title = 'Toy Story')
--          );
