INSERT INTO `author` (fname,mnames,lname,title,birthdate,deathdate)
VALUES
('Arthur','Ignatius Conan','Doyle','Sir','1859-05-22','1930-07-07'),
('Laurie','R','King',NULL,'1952-09-15',NULL),
('Neil','Richard MacKinnon','Gaiman',NULL,'1960-11-10',NULL);

INSERT INTO `karacter` (fname,mnames,lname,title)
VALUES
('Sherlock',NULL,'Holmes',NULL),
('John','Hamish','Watson','Dr.'),
('Mary',NULL,'Watson',NULL),
('James',NULL,'Mortimer','Dr.'),
('Baskerville',NULL,'Henry','Sir'),
('Lestrade',NULL,'G.','Detective'),
('Wilhelm','Gottsreich Sigismond','von Ormstein','Grand Duke'),
('Irene',NULL,'Adler',NULL),
('Mary',NULL,'Russell',NULL),
('Simpson',NULL,'Jessica',NULL),
('Moriarty',NULL,NULL,'Professor'),
('Patricia',NULL,'Donleavy',NULL);

INSERT INTO `opus` (title,alt_titles,genre,publication_date)
VALUES
('A Study in Scarlet',NULL,'mystery,novel','1887-00-00'),
('Hound of the Baskervilles',NULL,'mystery,novel','1902-00-00'),
('A Scandal in Bohemia',NULL,'mystery,short story','1891-00-00'),
('The Beekeeper\'s Apprentice','On the Segregation of the Queen','mystery,novel','1994');

INSERT INTO `location` (address,street,city,country)
VALUES
('221B','Baker St','London','England'),
(NULL,'Brixton Road','London','England'),
(NULL,NULL,'London','England'),
(NULL,NULL,'Sussex','England'),
(NULL,NULL,'Oxford','England'),
(NULL,NULL,'Dartmoor','England');

INSERT INTO `moment` (oid, description,date,lid)
VALUES
((select id from opus where title='A Study in Scarlet'),'First meeting between Holmes and Watson',NULL,(select id from location where street is NULL and city='London')),
((select id from opus where title='Hound of the Baskervilles'),'James Mortimer asks Holmes to look at the case',NULL,(select id from location where street='Baker St' and city='London')),
((select id from opus where title='Hound of the Baskervilles'),'Most of the book',NULL,(select id from location where city='Dartmoor'));

INSERT INTO `karacter_moment` (kid,mid)
VALUES
((select id from karacter where fname='Sherlock' and lname='Holmes'),
 (select id from moment where description ='First meeting between Holmes and Watson')),
((select id from karacter where fname='John' and lname='Watson'),
 (select id from moment where description ='First meeting between Holmes and Watson'));
 
INSERT INTO `opus_author` (oid,aid)
VALUES
((select id from opus where title='A Study in Scarlet'),(select id from author where fname='Arthur' and lname='Doyle')),
((select id from opus where title='Hound of the Baskervilles'),(select id from author where fname='Arthur' and lname='Doyle')),
((select id from opus where title='A Scandal in Bohemia'),(select id from author where fname='Arthur' and lname='Doyle')),
((select id from opus where title='The Beekeeper\'s Apprentice'),(select id from author where fname='Laurie' and lname='King'));
