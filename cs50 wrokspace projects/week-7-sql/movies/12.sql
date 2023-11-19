--  An more advance way to complete it
-- Creat 4 sub-table, each people have 2 sub-table
-- 1 sub-table is in stars , the other is sub-table is in people, both are Bradley Cooper's.
-- 1 sub-table is in stars , the other is sub-table is in people, both are Bradley Cooper's.


SELECT movies.title FROM movies
JOIN stars Bradley ON Bradley.movie_id = movies.id
JOIN people p1 ON Bradley.person_id = p1.id

JOIN stars Jennifer ON Jennifer.movie_id = movies.id
JOIN people p2 ON Jennifer.person_id = p2.id

WHERE p1.name = 'Bradley Cooper'
AND p2.name = 'Jennifer Lawrence';



-- A nested version of sql query
-- Find the movie titles of one person first, check if the titles are in the another person's titles


-- SELECT title FROM movies, stars, people
-- WHERE movies.id = stars.movie_id
-- AND people.id = stars.person_id
-- AND people.name = 'Bradley Cooper'
-- AND title IN (
-- SELECT title FROM movies, stars, people
-- WHERE movies.id = stars.movie_id
-- AND people.id = stars.person_id
-- AND people.name = 'Jennifer Lawrence'
-- );