#
# abrasss@oregonstate.edu  CS340-400-Spring 2017
# Assignment 2
#

#1 Find all films with maximum length or minimum rental duration (compared to all other films). 
#In other words let L be the maximum film length, and let R be the minimum rental duration in the table film. You need to find all films that have length L or duration R or both length L and duration R.
#You just need to return attribute film id for this query. 

SELECT film_id FROM film 
WHERE 
	length = (SELECT max(length) FROM film)
OR
	rental_duration = (SELECT min(rental_duration) FROM film);
	

#2 We want to find out how many of each category of film ED CHASE has started in so return a table with category.name and the count
#of the number of films that ED was in which were in that category order by the category name ascending (Your query should return every category even if ED has been in no films in that category).

SELECT name AS category, count(oj.category_id) AS 'number of films'
FROM category c
LEFT OUTER JOIN
(SELECT category_id FROM film_category fc
	INNER JOIN 
	(SELECT film_id FROM film_actor WHERE actor_id = (SELECT actor_id FROM actor WHERE first_name='Ed' and last_name='Chase')) f 
	ON fc.film_id = f.film_id) oj
	ON c.category_id = oj.category_id
GROUP BY c.category_id;


#3 Find the first name, last name and total combined film length of Sci-Fi films for every actor
#That is the result should list the names of all of the actors(even if an actor has not been in any Sci-Fi films)and the total length of Sci-Fi films they have been in.

SELECT aa.first_name, aa.last_name, COALESCE(Total,0) AS 'Total length'
FROM actor aa
LEFT OUTER JOIN
(
SELECT a.actor_id,first_name,last_name, SUM(f.length) as Total 
FROM actor a  
	INNER JOIN film_actor fa ON a.actor_id = fa.actor_id 
	INNER JOIN film f ON f.film_id = fa.film_id 
	INNER JOIN film_category fc ON fc.film_id = f.film_id 
WHERE fc.category_id = (SELECT category_id FROM category WHERE name="Sci-Fi")  
GROUP BY a.actor_id
) oj ON oj.actor_id = aa.actor_id
ORDER BY last_name, first_name ASC
;



#4 Find the first name and last name of all actors who have never been in a Sci-Fi film
SELECT aa.first_name, aa.last_name
FROM actor aa
LEFT OUTER JOIN
(
SELECT a.actor_id,first_name,last_name, COUNT(fc.film_id) as Total 
FROM actor a  
	INNER JOIN film_actor fa ON a.actor_id = fa.actor_id 
	INNER JOIN film f ON f.film_id = fa.film_id 
	INNER JOIN film_category fc ON fc.film_id = f.film_id 
WHERE fc.category_id = (SELECT category_id FROM category WHERE name="Sci-Fi")  
GROUP BY a.actor_id
) oj ON oj.actor_id = aa.actor_id
WHERE Total is NULL
ORDER BY last_name, first_name ASC
;


#5 Find the film title of all films which feature both KIRSTEN PALTROW and WARREN NOLTE
#Order the results by title, descending (use ORDER BY title DESC at the end of the query)
#Warning, this is a tricky one and while the syntax is all things you know, you have to think oustide
#the box a bit to figure out how to get a table that shows pairs of actors in movies

SELECT title FROM film 
WHERE film_id IN
(
	SELECT p.film_id 
	FROM
	(
		SELECT film_id 
		FROM film_actor fa 
		WHERE actor_id = (SELECT actor_id FROM actor WHERE first_name='KIRSTEN' and last_name='PALTROW')
	) p
	INNER JOIN
	(
		SELECT film_id 
		FROM film_actor fa 
		WHERE actor_id = (SELECT actor_id FROM actor WHERE first_name='WARREN' and last_name='NOLTE')
	) n 
	ON p.film_id = n.film_id
)
ORDER BY title DESC;


