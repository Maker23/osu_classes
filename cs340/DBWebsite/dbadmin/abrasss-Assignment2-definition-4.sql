--
-- abrasss@oregonstate.edu  CS340-400-Spring 2017
-- Assignment 2
--
-- For part one of this assignment you are to make a database with the following specifications and run the following queries
-- Table creation queries should immedatley follow the drop table queries, this is to facilitate testing on my end

DROP TABLE IF EXISTS `works_on`;
DROP TABLE IF EXISTS `project`;
DROP TABLE IF EXISTS `client`;
DROP TABLE IF EXISTS `employee`;



-- Create a table called client with the following properties:
-- id - an auto incrementing integer which is the primary key
-- first_name - a varchar with a maximum length of 255 characters, cannot be null
-- last_name - a varchar with a maximum length of 255 characters, cannot be null
-- dob - a date type (you can read about it here http://dev.mysql.com/doc/refman/5.0/en/datetime.html)
-- the combination of the first_name and last_name must be unique in this table

CREATE TABLE client (
	id int auto_increment NOT NULL,
  first_name varchar(255) NOT NULL,
  last_name varchar(255) NOT NULL,
  dob date,
  UNIQUE uniq (first_name,last_name),
	PRIMARY KEY (id)
) ENGINE=InnoDB;


-- Create a table called employee with the following properties:
-- id - an auto incrementing integer which is the primary key
-- first_name - a varchar of maximum length 255, cannot be null
-- last_name - a varchar of maximum length 255, cannot be null
-- dob - a date type 
-- date_joined - a date type 
-- the combination of the first_name and last_name must be unique in this table

-- employee table creation query replaces this text
CREATE TABLE employee (
	id int auto_increment NOT NULL,
	first_name varchar(255) NOT NULL,
	last_name varchar(255) NOT NULL,
	dob date,
	date_joined date,
	UNIQUE uniq (first_name, last_name),
	PRIMARY KEY (id)
) ENGINE=InnoDB;

-- Create a table called project with the following properties:
-- id - an auto incrementing integer which is the primary key
-- cid - an integer which is a foreign key reference to the client table
-- name - a varchar of maximum length 255, cannot be null
-- notes - a text type
-- the name of the project should be unique in this table

-- project table creation query replaces this text
CREATE TABLE project (
	id int auto_increment NOT NULL,
	cid int,
	name varchar(255) NOT NULL,
	notes TEXT,
	UNIQUE (name),
	FOREIGN KEY (cid) REFERENCES client (id) ON DELETE CASCADE ON UPDATE CASCADE,
	PRIMARY KEY (id)
) ENGINE=InnoDB;


-- Create a table called works_on with the following properties, this is a table representing a many-to-many relationship
-- between employees and projects:
-- eid - an integer which is a foreign key reference to employee
-- pid - an integer which is a foreign key reference to project
-- start_date - a date type 
-- The primary key is a combination of eid and pid

CREATE TABLE works_on(
	eid int,
	pid int,
	start_date date,
	FOREIGN KEY (eid) REFERENCES employee (id) ON DELETE CASCADE ON UPDATE CASCADE,
	FOREIGN KEY (pid) REFERENCES project  (id) ON DELETE CASCADE ON UPDATE CASCADE,
	PRIMARY KEY (eid,pid)
) ENGINE=InnoDB;


INSERT INTO client  (first_name, last_name, dob)
VALUES 
	('Sara', 'Smith', '1970-02-01'),
	('David', 'Atkins', '1979-11-18'),
	('Daniel', 'Jensen', '1985-03-02')
;

INSERT INTO employee  (first_name, last_name, dob, date_joined)
VALUES 
	('Adam','Lowd','1975-01-02','2009-01-01'),
	('Michael', 'Fern','1980-10-18','2013-06-05'),
	('Deena','Young','1984-03-21','2013-11-10')
;

INSERT INTO project (cid,name,notes) 
VALUES
 ((select id from client where first_name='Sara' AND last_name='Smith'), 'Diamond','Should be done by Jan 2017'),
 ((select id from client where first_name='David' AND last_name='Atkins'), 'Eclipse',NULL),
 ((select id from client where first_name='Daniel' AND last_name='Jensen'), 'Moon',NULL)
;

INSERT INTO works_on (eid,pid,start_date) 
VALUES
 ((select id from employee where first_name='Adam' AND last_name='Lowd'), 
	(select id from project where name = 'Diamond'),
	'2012-01-01'),
 ((select id from employee where first_name='Michael' AND last_name='Fern'), 
	(select id from project where name = 'Eclipse'),
	'2013-08-08'),
 ((select id from employee where first_name='Michael' AND last_name='Fern'), 
	(select id from project where name = 'Moon'),
	'2014-09-11')
;

