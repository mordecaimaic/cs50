SELECT DISTINCT(name) FROM people, ratings, directors
WHERE people.id = directors.person_id
AND ratings.movie_id = directors.movie_id
AND ratings.rating >= 9.0;