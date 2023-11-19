SELECT title FROM movies, stars, people, ratings
WHERE movies.id = stars.movie_id
AND people.id = stars.person_id
AND movies.id = ratings.movie_id
AND people.name = 'Chadwick Boseman'
ORDER BY ratings.rating DESC
LIMIT 5;