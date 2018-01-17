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
('The Final Problem',NULL,'mystery,short story','1893-00-00'),
('The Beekeeper\'s Apprentice','On the Segregation of the Queen','mystery,novel','1994-00-00');

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
((select id from opus where title='The Beekeeper\'s Apprentice'),'First meeting between Holmes and Russell',NULL,(select id from location where street is NULL and city='Sussex')),
((select id from opus where title='The Final Problem'),'First meeting between Holmes and Moriarty','1891-00-00',(select id from location where street is NULL and city='London')),
((select id from opus where title='Hound of the Baskervilles'),'James Mortimer asks Holmes to look at the case',NULL,(select id from location where street='Baker St' and city='London')),
((select id from opus where title='A Study in Scarlet'),'PRIMARY',NULL,(select id from location where street is NULL and city='London')),
((select id from opus where title='Hound of the Baskervilles'),'PRIMARY',NULL,(select id from location where street is NULL and city='Dartmoor')),
((select id from opus where title='The Beekeeper\'s Apprentice'),'PRIMARY',NULL,(select id from location where street is NULL and city='Sussex')),
((select id from opus where title='The Final Problem'),'PRIMARY',NULL,(select id from location where street is NULL and city='London')),
((select id from opus where title='A Scandal in Bohemia'),'PRIMARY',NULL,(select id from location where street is NULL and city='London'));

INSERT INTO `karacter_moment` (kid,mid)
VALUES
((select id from karacter where fname='Sherlock' and lname='Holmes'),
 (select id from moment where description ='First meeting between Holmes and Watson')),
((select id from karacter where fname='John' and lname='Watson'),
 (select id from moment where description ='First meeting between Holmes and Watson')),

((select id from karacter where title='Professor' and lname='Moriarty'),
 (select id from moment where oid = (select id from opus where title = 'The Final Problem') and description='PRIMARY')),
((select id from karacter where fname='Sherlock' and lname='Holmes'),
 (select id from moment where oid = (select id from opus where title = 'The Final Problem') and description='PRIMARY')),
((select id from karacter where fname='Sherlock' and lname='Holmes'),
 (select id from moment where oid = (select id from opus where title = 'Hound of the Baskervilles') and description='PRIMARY')),
((select id from karacter where fname='John' and lname='Watson'),
 (select id from moment where oid = (select id from opus where title = 'Hound of the Baskervilles') and description='PRIMARY')),
((select id from karacter where fname='Sherlock' and lname='Holmes'),
 (select id from moment where oid = (select id from opus where title = 'A Study in Scarlet') and description='PRIMARY')),
((select id from karacter where fname='John' and lname='Watson'),
 (select id from moment where oid = (select id from opus where title = 'A Study in Scarlet') and description='PRIMARY')),
((select id from karacter where fname='James' and lname='Mortimer'),
 (select id from moment where oid = (select id from opus where title = 'Hound of the Baskervilles') and description='PRIMARY')),
((select id from karacter where title='Detective' and lname='Lestrade'),
 (select id from moment where oid = (select id from opus where title = 'A Study in Scarlet') and description='PRIMARY')),
((select id from karacter where fname='Irene' and lname='Adler'),
 (select id from moment where oid = (select id from opus where title = 'A Scandal in Bohemia') and description='PRIMARY')),
((select id from karacter where fname='John' and lname='Watson'),
 (select id from moment where oid = (select id from opus where title = 'A Scandal in Bohemia') and description='PRIMARY')),
((select id from karacter where fname='Sherlock' and lname='Holmes'),
 (select id from moment where oid = (select id from opus where title = 'A Scandal in Bohemia') and description='PRIMARY')),
((select id from karacter where fname='Sherlock' and lname='Holmes'),
 (select id from moment where oid = (select id from opus where title = 'The Beekeeper\'s Apprentice') and description='PRIMARY')),
((select id from karacter where fname='Mary' and lname='Russell'),
 (select id from moment where oid = (select id from opus where title = 'The Beekeeper\'s Apprentice') and description='PRIMARY')),

((select id from karacter where fname='Sherlock' and lname='Holmes'),
 (select id from moment where description ='First meeting between Holmes and Moriarty')),
((select id from karacter where title='Professor' and lname='Moriarty'),
 (select id from moment where description ='First meeting between Holmes and Moriarty')),

((select id from karacter where fname='Mary' and lname='Russell'),
 (select id from moment where description ='First meeting between Holmes and Russell')),
((select id from karacter where fname='Sherlock' and lname='Holmes'),
 (select id from moment where description ='First meeting between Holmes and Russell'))

;

 
INSERT INTO `opus_author` (oid,aid)
VALUES
((select id from opus where title='A Study in Scarlet'),(select id from author where fname='Arthur' and lname='Doyle')),
((select id from opus where title='Hound of the Baskervilles'),(select id from author where fname='Arthur' and lname='Doyle')),
((select id from opus where title='A Scandal in Bohemia'),(select id from author where fname='Arthur' and lname='Doyle')),
((select id from opus where title='The Final Problem'),(select id from author where fname='Arthur' and lname='Doyle')),
((select id from opus where title='The Beekeeper\'s Apprentice'),(select id from author where fname='Laurie' and lname='King'));
