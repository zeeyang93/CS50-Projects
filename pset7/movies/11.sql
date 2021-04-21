-- suggest to JOIN table movies with ratings first

SELECT title FROM movies JOIN ratings ON movies.id = ratings.movie_id WHERE id
IN (SELECT movie_id FROM stars WHERE person_id
IN (SELECT id FROM people WHERE name = 'Chadwick Boseman'))
ORDER BY rating DESC LIMIT 5;

-- note: SELECT title FROM movies WHERE id IN () can scramble the data that was already sorted within the ()!