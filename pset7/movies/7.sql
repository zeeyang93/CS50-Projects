SELECT title, rating
FROM movies JOIN ratings ON movies.id = ratings.movie_id

-- means select column title/rating from table of joined movies/ratings

WHERE year = 2010 AND title IS NOT NULL
ORDER BY rating DESC, title ASC