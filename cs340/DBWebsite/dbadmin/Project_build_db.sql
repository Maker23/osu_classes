-- Tables that describe many-to-many relationships
DROP TABLE IF EXISTS `karacter_moment`;  -- HasRoleIn
DROP TABLE IF EXISTS `opus_author`;      -- AuthoredBy

-- Tables with keyed primary data
DROP TABLE IF EXISTS `moment`;
DROP TABLE IF EXISTS `location`;

DROP TABLE IF EXISTS `author`;
DROP TABLE IF EXISTS `karacter`;
-- DROP TABLE IF EXISTS `location_type`;
DROP TABLE IF EXISTS `opus`;

--
-- Tables with keyed primary data
CREATE TABLE `author` (
	`id` int(11) NOT NULL AUTO_INCREMENT,
	`fname` varchar(127) NOT NULL,
	`mnames` varchar(255),
	`lname` varchar(127),
	`title` varchar(15),
	`birthdate` date,
	`deathdate` date,
  PRIMARY KEY (`id`)
);

CREATE TABLE `karacter` (
	`id` int(11) NOT NULL AUTO_INCREMENT,
	`fname` varchar(127) NOT NULL,
	`mnames` varchar(255),
	`lname` varchar(127),
	`title` varchar(15),
  PRIMARY KEY (`id`)
);

-- CREATE TABLE `location_type` (
--	`id` int(11) NOT NULL AUTO_INCREMENT,
--	`name` varchar(255) NOT NULL,
--  PRIMARY KEY (`id`)
-- );

CREATE TABLE `location` (
	`id` int(11) NOT NULL AUTO_INCREMENT,
	`address` varchar(63),
	`street` varchar(63),
	`city` varchar(63) NOT NULL,
	`country` varchar(63) NOT NULL,
  PRIMARY KEY (`id`)
);

CREATE TABLE `opus` (
	`id` int(11) NOT NULL AUTO_INCREMENT,
	`title` varchar(255) NOT NULL,
	`alt_titles` varchar(255),
	`genre` varchar(255),
	`publication_date` date,
  PRIMARY KEY (`id`)
);

CREATE TABLE `moment` (
	`id` int(11) NOT NULL AUTO_INCREMENT,
	`oid` int NOT NULL,
	`description` varchar(255),
	`date` date,
	`lid` int,
  FOREIGN KEY (`oid`) REFERENCES `opus` (`id`),
  FOREIGN KEY (`lid`) REFERENCES `location` (`id`),
  PRIMARY KEY (`id`)
);

CREATE TABLE `karacter_moment` (   -- HasRoleIn
	`id` int(11) NOT NULL AUTO_INCREMENT,
	`kid` int,
	`mid` int NOT NULL,
	PRIMARY KEY (`id`),
  FOREIGN KEY (`kid`) REFERENCES `karacter` (`id`),
  FOREIGN KEY (`mid`) REFERENCES `moment` (`id`)
);

CREATE TABLE `opus_author` (   -- AuthoredBy
	`oid` int NOT NULL,
	`aid` int NOT NULL,
	PRIMARY KEY (`oid`,`aid`),
  FOREIGN KEY (`oid`) REFERENCES `opus` (`id`),
  FOREIGN KEY (`aid`) REFERENCES `author` (`id`)
);

