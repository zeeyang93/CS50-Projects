SELECT name FROM songs
WHERE artist_id = (SELECT id FROM artists WHERE name = 'Post Malone');

--here we need to match artist_id with a second table 'artist'