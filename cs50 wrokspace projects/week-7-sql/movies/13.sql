--  An more advance way to complete it
-- Creat 1 Sub-table Call Kevin and join that table

SELECT people.name FROM people
JOIN stars ON stars.person_id = people.id
JOIN movies on stars.movie_id = movies.id
JOIN stars Kevin ON Kevin.movie_id = movies.id
WHERE Kevin.person_id = (
    SELECT people.id FROM people
    WHERE people.name = 'Kevin Bacon'
    AND people.birth = '1958'
)
AND people.name != 'Kevin Bacon';


-- A nested of sql query
-- Find all movies id of "Kevin Bacon" was starred
-- Then find all the person name
-- Then exclude the name "Kevin Bacon"

-- SELECT people.name FROM people
-- JOIN stars ON stars.person_id = people.id
-- JOIN  movies ON stars.movie_id = movies.id
-- WHERE movies.id IN(
--     SELECT movie_id FROM stars
--     JOIN people ON stars.person_id = people.id
--     WHERE people.name = 'Kevin Bacon'
--     AND people.birth = '1958'
-- )
-- AND people.name != 'Kevin Bacon';

