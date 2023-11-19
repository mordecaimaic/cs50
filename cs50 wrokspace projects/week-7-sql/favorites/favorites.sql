SELECT * FROM shows WHERE title LIKE 'Brooklyn%%'
UPDATE shows SET title = 'Brooklyn Nine-Nine' WHERE title LIKE 'Brooklyn%';

SELECT * FROM shows WHERE title LIKE 'Game%'
UPDATE shows SET title = 'Game of Thrones' WHERE title LIKE 'Game%';

SELECT * FROM shows WHERE title LIKE 'Grey%'
UPDATE shows SET title = 'Grey’s Anatomy' WHERE title LIKE 'Grey%';

SELECT * FROM shows WHERE title LIKE 'It%'
UPDATE shows SET title = 'It’s Always Sunny in Philadelphia' WHERE title LIKE 'It%';

SELECT * FROM shows WHERE title LIKE 'Park%'
UPDATE shows SET title = 'Parks and Recreation' WHERE title LIKE 'Park%';

SELECT * FROM shows WHERE title LIKE 'The Office'
UPDATE shows SET title = 'The Office' WHERE title LIKE 'The Office';
UPDATE shows SET title = 'The Office' WHERE title LIKE 'The%Office';
