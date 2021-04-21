SELECT count(title) FROM movies
WHERE id IN (SELECT movie_id FROM ratings WHERE rating = 10);

-- note: use IN when there are multiple expected values