-- Sakila Sample Database Data
-- Version 0.8

-- Copyright (c) 2006, MySQL AB
-- All rights reserved.

-- Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

--  * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
--  * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
--  * Neither the name of MySQL AB nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

-- THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL';


-- Dumping data for table actor
--

SET AUTOCOMMIT=0;
INSERT INTO actor VALUES (1,'PENELOPE','GUINESS','2006-02-15 04:34:33'),(2,'NICK','WAHLBERG','2006-02-15 04:34:33'),(3,'ED','CHASE','2006-02-15 04:34:33'),(4,'JENNIFER','DAVIS','2006-02-15 04:34:33'),(5,'JOHNNY','LOLLOBRIGIDA','2006-02-15 04:34:33'),(6,'BETTE','NICHOLSON','2006-02-15 04:34:33'),(7,'GRACE','MOSTEL','2006-02-15 04:34:33'),(8,'MATTHEW','JOHANSSON','2006-02-15 04:34:33'),(9,'JOE','SWANK','2006-02-15 04:34:33'),(10,'CHRISTIAN','GABLE','2006-02-15 04:34:33'),(11,'ZERO','CAGE','2006-02-15 04:34:33'),(12,'KARL','BERRY','2006-02-15 04:34:33'),(13,'UMA','WOOD','2006-02-15 04:34:33'),(14,'VIVIEN','BERGEN','2006-02-15 04:34:33'),(15,'CUBA','OLIVIER','2006-02-15 04:34:33'),(16,'FRED','COSTNER','2006-02-15 04:34:33'),(17,'HELEN','VOIGHT','2006-02-15 04:34:33'),(18,'DAN','TORN','2006-02-15 04:34:33'),(19,'BOB','FAWCETT','2006-02-15 04:34:33'),(20,'LUCILLE','TRACY','2006-02-15 04:34:33'),(21,'KIRSTEN','PALTROW','2006-02-15 04:34:33'),(22,'ELVIS','MARX','2006-02-15 04:34:33'),(23,'SANDRA','KILMER','2006-02-15 04:34:33'),(24,'CAMERON','STREEP','2006-02-15 04:34:33'),(25,'KEVIN','BLOOM','2006-02-15 04:34:33'),(26,'RIP','CRAWFORD','2006-02-15 04:34:33'),(27,'JULIA','MCQUEEN','2006-02-15 04:34:33'),(28,'WOODY','HOFFMAN','2006-02-15 04:34:33'),(29,'ALEC','WAYNE','2006-02-15 04:34:33'),(30,'SANDRA','PECK','2006-02-15 04:34:33'),(31,'SISSY','SOBIESKI','2006-02-15 04:34:33'),(32,'TIM','HACKMAN','2006-02-15 04:34:33'),(33,'MILLA','PECK','2006-02-15 04:34:33'),(34,'AUDREY','OLIVIER','2006-02-15 04:34:33'),(35,'JUDY','DEAN','2006-02-15 04:34:33'),(36,'BURT','DUKAKIS','2006-02-15 04:34:33'),(37,'VAL','BOLGER','2006-02-15 04:34:33'),(38,'TOM','MCKELLEN','2006-02-15 04:34:33'),(39,'GOLDIE','BRODY','2006-02-15 04:34:33'),(40,'JOHNNY','CAGE','2006-02-15 04:34:33'),(41,'JODIE','DEGENERES','2006-02-15 04:34:33'),(42,'TOM','MIRANDA','2006-02-15 04:34:33'),(43,'KIRK','JOVOVICH','2006-02-15 04:34:33'),(44,'NICK','STALLONE','2006-02-15 04:34:33'),(45,'REESE','KILMER','2006-02-15 04:34:33'),(46,'PARKER','GOLDBERG','2006-02-15 04:34:33'),(47,'JULIA','BARRYMORE','2006-02-15 04:34:33'),(48,'FRANCES','DAY-LEWIS','2006-02-15 04:34:33'),(49,'ANNE','CRONYN','2006-02-15 04:34:33'),(50,'NATALIE','HOPKINS','2006-02-15 04:34:33'),(51,'GARY','PHOENIX','2006-02-15 04:34:33'),(52,'CARMEN','HUNT','2006-02-15 04:34:33'),(53,'MENA','TEMPLE','2006-02-15 04:34:33'),(54,'PENELOPE','PINKETT','2006-02-15 04:34:33'),(55,'FAY','KILMER','2006-02-15 04:34:33'),(56,'DAN','HARRIS','2006-02-15 04:34:33'),(57,'JUDE','CRUISE','2006-02-15 04:34:33'),(58,'CHRISTIAN','AKROYD','2006-02-15 04:34:33'),(59,'DUSTIN','TAUTOU','2006-02-15 04:34:33'),(60,'HENRY','BERRY','2006-02-15 04:34:33'),(61,'CHRISTIAN','NEESON','2006-02-15 04:34:33'),(62,'JAYNE','NEESON','2006-02-15 04:34:33'),(63,'CAMERON','WRAY','2006-02-15 04:34:33'),(64,'RAY','JOHANSSON','2006-02-15 04:34:33'),(65,'ANGELA','HUDSON','2006-02-15 04:34:33'),(66,'MARY','TANDY','2006-02-15 04:34:33'),(67,'JESSICA','BAILEY','2006-02-15 04:34:33'),(68,'RIP','WINSLET','2006-02-15 04:34:33'),(69,'KENNETH','PALTROW','2006-02-15 04:34:33'),(70,'MICHELLE','MCCONAUGHEY','2006-02-15 04:34:33'),(71,'ADAM','GRANT','2006-02-15 04:34:33'),(72,'SEAN','WILLIAMS','2006-02-15 04:34:33'),(73,'GARY','PENN','2006-02-15 04:34:33'),(74,'MILLA','KEITEL','2006-02-15 04:34:33'),(75,'BURT','POSEY','2006-02-15 04:34:33'),(76,'ANGELINA','ASTAIRE','2006-02-15 04:34:33'),(77,'CARY','MCCONAUGHEY','2006-02-15 04:34:33'),(78,'GROUCHO','SINATRA','2006-02-15 04:34:33'),(79,'MAE','HOFFMAN','2006-02-15 04:34:33'),(80,'RALPH','CRUZ','2006-02-15 04:34:33'),(81,'SCARLETT','DAMON','2006-02-15 04:34:33'),(82,'WOODY','JOLIE','2006-02-15 04:34:33'),(83,'BEN','WILLIS','2006-02-15 04:34:33'),(84,'JAMES','PITT','2006-02-15 04:34:33'),(85,'MINNIE','ZELLWEGER','2006-02-15 04:34:33'),(86,'GREG','CHAPLIN','2006-02-15 04:34:33'),(87,'SPENCER','PECK','2006-02-15 04:34:33'),(88,'KENNETH','PESCI','2006-02-15 04:34:33'),(89,'CHARLIZE','DENCH','2006-02-15 04:34:33'),(90,'SEAN','GUINESS','2006-02-15 04:34:33'),(91,'CHRISTOPHER','BERRY','2006-02-15 04:34:33'),(92,'KIRSTEN','AKROYD','200
COMMIT;

--
-- Dumping data for table category
--

SET AUTOCOMMIT=0;
INSERT INTO category VALUES (1,'Action','2006-02-15 04:46:27'),(2,'Animation','2006-02-15 04:46:27'),(3,'Children','2006-02-15 04:46:27'),(4,'Classics','2006-02-15 04:46:27'),(5,'Comedy','2006-02-15 04:46:27'),(6,'Documentary','2006-02-15 04:46:27'),(7,'Drama','2006-02-15 04:46:27'),(8,'Family','2006-02-15 04:46:27'),(9,'Foreign','2006-02-15 04:46:27'),(10,'Games','2006-02-15 04:46:27'),(11,'Horror','2006-02-15 04:46:27'),(12,'Music','2006-02-15 04:46:27'),(13,'New','2006-02-15 04:46:27'),(14,'Sci-Fi','2006-02-15 04:46:27'),(15,'Sports','2006-02-15 04:46:27'),(16,'Travel','2006-02-15 04:46:27');
COMMIT;

--
-- Dumping data for table film
--

SET AUTOCOMMIT=0;
INSERT INTO film VALUES (1,'ACADEMY DINOSAUR','A Epic Drama of a Feminist And a Mad Scientist who must Battle a Teacher in The Canadian Rockies',2006,1,NULL,6,'0.99',86,'20.99','PG','Deleted Scenes,Behind the Scenes','2006-02-15 05:03:42'),(2,'ACE GOLDFINGER','A Astounding Epistle of a Database Administrator And a Explorer who must Find a Car in Ancient China',2006,1,NULL,3,'4.99',48,'12.99','G','Trailers,Deleted Scenes','2006-02-15 05:03:42'),(3,'ADAPTATION HOLES','A Astounding Reflection of a Lumberjack And a Car who must Sink a Lumberjack in A Baloon Factory',2006,1,NULL,7,'2.99',50,'18.99','NC-17','Trailers,Deleted Scenes','2006-02-15 05:03:42'),(4,'AFFAIR PREJUDICE','A Fanciful Documentary of a Frisbee And a Lumberjack who must Chase a Monkey in A Shark Tank',2006,1,NULL,5,'2.99',117,'26.99','G','Commentaries,Behind the Scenes','2006-02-15 05:03:42'),(5,'AFRICAN EGG','A Fast-Paced Documentary of a Pastry Chef And a Dentist who must Pursue a Forensic Psychologist in The Gulf of Mexico',2006,1,NULL,6,'2.99',130,'22.99','G','Deleted Scenes','2006-02-15 05:03:42'),(6,'AGENT TRUMAN','A Intrepid Panorama of a Robot And a Boy who must Escape a Sumo Wrestler in Ancient China',2006,1,NULL,3,'2.99',169,'17.99','PG','Deleted Scenes','2006-02-15 05:03:42'),(7,'AIRPLANE SIERRA','A Touching Saga of a Hunter And a Butler who must Discover a Butler in A Jet Boat',2006,1,NULL,6,'4.99',62,'28.99','PG-13','Trailers,Deleted Scenes','2006-02-15 05:03:42'),(8,'AIRPORT POLLOCK','A Epic Tale of a Moose And a Girl who must Confront a Monkey in Ancient India',2006,1,NULL,6,'4.99',54,'15.99','R','Trailers','2006-02-15 05:03:42'),(9,'ALABAMA DEVIL','A Thoughtful Panorama of a Database Administrator And a Mad Scientist who must Outgun a Mad Scientist in A Jet Boat',2006,1,NULL,3,'2.99',114,'21.99','PG-13','Trailers,Deleted Scenes','2006-02-15 05:03:42'),(10,'ALADDIN CALENDAR','A Action-Packed Tale of a Man And a Lumberjack who must Reach a Feminist in Ancient China',2006,1,NULL,6,'4.99',63,'24.99','NC-17','Trailers,Deleted Scenes','2006-02-15 05:03:42'),(11,'ALAMO VIDEOTAPE','A Boring Epistle of a Butler And a Cat who must Fight a Pastry Chef in A MySQL Convention',2006,1,NULL,6,'0.99',126,'16.99','G','Commentaries,Behind the Scenes','2006-02-15 05:03:42'),(12,'ALASKA PHANTOM','A Fanciful Saga of a Hunter And a Pastry Chef who must Vanquish a Boy in Australia',2006,1,NULL,6,'0.99',136,'22.99','PG','Commentaries,Deleted Scenes','2006-02-15 05:03:42'),(13,'ALI FOREVER','A Action-Packed Drama of a Dentist And a Crocodile who must Battle a Feminist in The Canadian Rockies',2006,1,NULL,4,'4.99',150,'21.99','PG','Deleted Scenes,Behind the Scenes','2006-02-15 05:03:42'),(14,'ALICE FANTASIA','A Emotional Drama of a A Shark And a Database Administrator who must Vanquish a Pioneer in Soviet Georgia',2006,1,NULL,6,'0.99',94,'23.99','NC-17','Trailers,Deleted Scenes,Behind the Scenes','2006-02-15 05:03:42'),(15,'ALIEN CENTER','A Brilliant Drama of a Cat And a Mad Scientist who must Battle a Feminist in A MySQL Convention',2006,1,NULL,5,'2.99',46,'10.99','NC-17','Trailers,Commentaries,Behind the Scenes','2006-02-15 05:03:42'),(16,'ALLEY EVOLUTION','A Fast-Paced Drama of a Robot And a Composer who must Battle a Astronaut in New Orleans',2006,1,NULL,6,'2.99',180,'23.99','NC-17','Trailers,Commentaries','2006-02-15 05:03:42'),(17,'ALONE TRIP','A Fast-Paced Character Study of a Composer And a Dog who must Outgun a Boat in An Abandoned Fun House',2006,1,NULL,3,'0.99',82,'14.99','R','Trailers,Behind the Scenes','2006-02-15 05:03:42'),(18,'ALTER VICTORY','A Thoughtful Drama of a Composer And a Feminist who must Meet a Secret Agent in The Canadian Rockies',2006,1,NULL,6,'0.99',57,'27.99','PG-13','Trailers,Behind the Scenes','2006-02-15 05:03:42'),(19,'AMADEUS HOLY','A Emotional Display of a Pioneer And a Technical Writer who must Battle a Man in A Baloon',2006,1,NULL,6,'0.99',113,'20.99','PG','Commentaries,Deleted Scenes,Behind the Scenes','2006-02-15 05:03:42'),(20,'AMELIE HELLFIGHTERS','A Boring Drama of a Woman And a Squirrel who must Conquer a Student in A Baloo
COMMIT;

--
-- Dumping data for table film_actor
--

SET AUTOCOMMIT=0;
INSERT INTO film_actor VALUES (1,1,'2006-02-15 05:05:03'),(1,23,'2006-02-15 05:05:03'),(1,25,'2006-02-15 05:05:03'),(1,106,'2006-02-15 05:05:03'),(1,140,'2006-02-15 05:05:03'),(1,166,'2006-02-15 05:05:03'),(1,277,'2006-02-15 05:05:03'),(1,361,'2006-02-15 05:05:03'),(1,438,'2006-02-15 05:05:03'),(1,499,'2006-02-15 05:05:03'),(1,506,'2006-02-15 05:05:03'),(1,509,'2006-02-15 05:05:03'),(1,605,'2006-02-15 05:05:03'),(1,635,'2006-02-15 05:05:03'),(1,749,'2006-02-15 05:05:03'),(1,832,'2006-02-15 05:05:03'),(1,939,'2006-02-15 05:05:03'),(1,970,'2006-02-15 05:05:03'),(1,980,'2006-02-15 05:05:03'),(2,3,'2006-02-15 05:05:03'),(2,31,'2006-02-15 05:05:03'),(2,47,'2006-02-15 05:05:03'),(2,105,'2006-02-15 05:05:03'),(2,132,'2006-02-15 05:05:03'),(2,145,'2006-02-15 05:05:03'),(2,226,'2006-02-15 05:05:03'),(2,249,'2006-02-15 05:05:03'),(2,314,'2006-02-15 05:05:03'),(2,321,'2006-02-15 05:05:03'),(2,357,'2006-02-15 05:05:03'),(2,369,'2006-02-15 05:05:03'),(2,399,'2006-02-15 05:05:03'),(2,458,'2006-02-15 05:05:03'),(2,481,'2006-02-15 05:05:03'),(2,485,'2006-02-15 05:05:03'),(2,518,'2006-02-15 05:05:03'),(2,540,'2006-02-15 05:05:03'),(2,550,'2006-02-15 05:05:03'),(2,555,'2006-02-15 05:05:03'),(2,561,'2006-02-15 05:05:03'),(2,742,'2006-02-15 05:05:03'),(2,754,'2006-02-15 05:05:03'),(2,811,'2006-02-15 05:05:03'),(2,958,'2006-02-15 05:05:03'),(3,17,'2006-02-15 05:05:03'),(3,40,'2006-02-15 05:05:03'),(3,42,'2006-02-15 05:05:03'),(3,87,'2006-02-15 05:05:03'),(3,111,'2006-02-15 05:05:03'),(3,185,'2006-02-15 05:05:03'),(3,289,'2006-02-15 05:05:03'),(3,329,'2006-02-15 05:05:03'),(3,336,'2006-02-15 05:05:03'),(3,341,'2006-02-15 05:05:03'),(3,393,'2006-02-15 05:05:03'),(3,441,'2006-02-15 05:05:03'),(3,453,'2006-02-15 05:05:03'),(3,480,'2006-02-15 05:05:03'),(3,539,'2006-02-15 05:05:03'),(3,618,'2006-02-15 05:05:03'),(3,685,'2006-02-15 05:05:03'),(3,827,'2006-02-15 05:05:03'),(3,966,'2006-02-15 05:05:03'),(3,967,'2006-02-15 05:05:03'),(3,971,'2006-02-15 05:05:03'),(3,996,'2006-02-15 05:05:03'),(4,23,'2006-02-15 05:05:03'),(4,25,'2006-02-15 05:05:03'),(4,56,'2006-02-15 05:05:03'),(4,62,'2006-02-15 05:05:03'),(4,79,'2006-02-15 05:05:03'),(4,87,'2006-02-15 05:05:03'),(4,355,'2006-02-15 05:05:03'),(4,379,'2006-02-15 05:05:03'),(4,398,'2006-02-15 05:05:03'),(4,463,'2006-02-15 05:05:03'),(4,490,'2006-02-15 05:05:03'),(4,616,'2006-02-15 05:05:03'),(4,635,'2006-02-15 05:05:03'),(4,691,'2006-02-15 05:05:03'),(4,712,'2006-02-15 05:05:03'),(4,714,'2006-02-15 05:05:03'),(4,721,'2006-02-15 05:05:03'),(4,798,'2006-02-15 05:05:03'),(4,832,'2006-02-15 05:05:03'),(4,858,'2006-02-15 05:05:03'),(4,909,'2006-02-15 05:05:03'),(4,924,'2006-02-15 05:05:03'),(5,19,'2006-02-15 05:05:03'),(5,54,'2006-02-15 05:05:03'),(5,85,'2006-02-15 05:05:03'),(5,146,'2006-02-15 05:05:03'),(5,171,'2006-02-15 05:05:03'),(5,172,'2006-02-15 05:05:03'),(5,202,'2006-02-15 05:05:03'),(5,203,'2006-02-15 05:05:03'),(5,286,'2006-02-15 05:05:03'),(5,288,'2006-02-15 05:05:03'),(5,316,'2006-02-15 05:05:03'),(5,340,'2006-02-15 05:05:03'),(5,369,'2006-02-15 05:05:03'),(5,375,'2006-02-15 05:05:03'),(5,383,'2006-02-15 05:05:03'),(5,392,'2006-02-15 05:05:03'),(5,411,'2006-02-15 05:05:03'),(5,503,'2006-02-15 05:05:03'),(5,535,'2006-02-15 05:05:03'),(5,571,'2006-02-15 05:05:03'),(5,650,'2006-02-15 05:05:03'),(5,665,'2006-02-15 05:05:03'),(5,687,'2006-02-15 05:05:03'),(5,730,'2006-02-15 05:05:03'),(5,732,'2006-02-15 05:05:03'),(5,811,'2006-02-15 05:05:03'),(5,817,'2006-02-15 05:05:03'),(5,841,'2006-02-15 05:05:03'),(5,865,'2006-02-15 05:05:03'),(6,29,'2006-02-15 05:05:03'),(6,53,'2006-02-15 05:05:03'),(6,60,'2006-02-15 05:05:03'),(6,70,'2006-02-15 05:05:03'),(6,112,'2006-02-15 05:05:03'),(6,164,'2006-02-15 05:05:03'),(6,165,'2006-02-15 05:05:03'),(6,193,'2006-02-15 05:05:03'),(6,256,'2006-02-15 05:05:03'),(6,451,'2006-02-15 05:05:03'),(6,503,'2006-02-15 05:05:03'),(6,509,'2006-02-15 05:05:03'),(6,517,'2006-02-15 05:05:03'),(6,519,'2006-02-15 05:05:03'),(6,605,'2006-02-15 05:05:03'),(6,692,'2006-02-15 05:05:03'),(6,826,'2006-02-15 05:05:03'),(6,892,'2006-02-15 05:05:03'),(6,902,'2006-02-15 05:05:03'),(6,994,'20
COMMIT;

--
-- Dumping data for table film_category
--

SET AUTOCOMMIT=0;
INSERT INTO film_category VALUES (1,6,'2006-02-15 05:07:09'),(2,11,'2006-02-15 05:07:09'),(3,6,'2006-02-15 05:07:09'),(4,11,'2006-02-15 05:07:09'),(5,8,'2006-02-15 05:07:09'),(6,9,'2006-02-15 05:07:09'),(7,5,'2006-02-15 05:07:09'),(8,11,'2006-02-15 05:07:09'),(9,11,'2006-02-15 05:07:09'),(10,15,'2006-02-15 05:07:09'),(11,9,'2006-02-15 05:07:09'),(12,12,'2006-02-15 05:07:09'),(13,11,'2006-02-15 05:07:09'),(14,4,'2006-02-15 05:07:09'),(15,9,'2006-02-15 05:07:09'),(16,9,'2006-02-15 05:07:09'),(17,12,'2006-02-15 05:07:09'),(18,2,'2006-02-15 05:07:09'),(19,1,'2006-02-15 05:07:09'),(20,12,'2006-02-15 05:07:09'),(21,1,'2006-02-15 05:07:09'),(22,13,'2006-02-15 05:07:09'),(23,2,'2006-02-15 05:07:09'),(24,11,'2006-02-15 05:07:09'),(25,13,'2006-02-15 05:07:09'),(26,14,'2006-02-15 05:07:09'),(27,15,'2006-02-15 05:07:09'),(28,5,'2006-02-15 05:07:09'),(29,1,'2006-02-15 05:07:09'),(30,11,'2006-02-15 05:07:09'),(31,8,'2006-02-15 05:07:09'),(32,13,'2006-02-15 05:07:09'),(33,7,'2006-02-15 05:07:09'),(34,11,'2006-02-15 05:07:09'),(35,11,'2006-02-15 05:07:09'),(36,2,'2006-02-15 05:07:09'),(37,4,'2006-02-15 05:07:09'),(38,1,'2006-02-15 05:07:09'),(39,14,'2006-02-15 05:07:09'),(40,6,'2006-02-15 05:07:09'),(41,16,'2006-02-15 05:07:09'),(42,15,'2006-02-15 05:07:09'),(43,8,'2006-02-15 05:07:09'),(44,14,'2006-02-15 05:07:09'),(45,13,'2006-02-15 05:07:09'),(46,10,'2006-02-15 05:07:09'),(47,9,'2006-02-15 05:07:09'),(48,3,'2006-02-15 05:07:09'),(49,14,'2006-02-15 05:07:09'),(50,8,'2006-02-15 05:07:09'),(51,12,'2006-02-15 05:07:09'),(52,9,'2006-02-15 05:07:09'),(53,8,'2006-02-15 05:07:09'),(54,12,'2006-02-15 05:07:09'),(55,14,'2006-02-15 05:07:09'),(56,1,'2006-02-15 05:07:09'),(57,16,'2006-02-15 05:07:09'),(58,6,'2006-02-15 05:07:09'),(59,3,'2006-02-15 05:07:09'),(60,4,'2006-02-15 05:07:09'),(61,7,'2006-02-15 05:07:09'),(62,6,'2006-02-15 05:07:09'),(63,8,'2006-02-15 05:07:09'),(64,7,'2006-02-15 05:07:09'),(65,11,'2006-02-15 05:07:09'),(66,3,'2006-02-15 05:07:09'),(67,1,'2006-02-15 05:07:09'),(68,3,'2006-02-15 05:07:09'),(69,14,'2006-02-15 05:07:09'),(70,2,'2006-02-15 05:07:09'),(71,8,'2006-02-15 05:07:09'),(72,6,'2006-02-15 05:07:09'),(73,14,'2006-02-15 05:07:09'),(74,12,'2006-02-15 05:07:09'),(75,16,'2006-02-15 05:07:09'),(76,12,'2006-02-15 05:07:09'),(77,13,'2006-02-15 05:07:09'),(78,2,'2006-02-15 05:07:09'),(79,7,'2006-02-15 05:07:09'),(80,8,'2006-02-15 05:07:09'),(81,14,'2006-02-15 05:07:09'),(82,8,'2006-02-15 05:07:09'),(83,8,'2006-02-15 05:07:09'),(84,16,'2006-02-15 05:07:09'),(85,6,'2006-02-15 05:07:09'),(86,12,'2006-02-15 05:07:09'),(87,16,'2006-02-15 05:07:09'),(88,16,'2006-02-15 05:07:09'),(89,2,'2006-02-15 05:07:09'),(90,13,'2006-02-15 05:07:09'),(91,4,'2006-02-15 05:07:09'),(92,11,'2006-02-15 05:07:09'),(93,13,'2006-02-15 05:07:09'),(94,8,'2006-02-15 05:07:09'),(95,13,'2006-02-15 05:07:09'),(96,13,'2006-02-15 05:07:09'),(97,1,'2006-02-15 05:07:09'),(98,7,'2006-02-15 05:07:09'),(99,5,'2006-02-15 05:07:09'),(100,9,'2006-02-15 05:07:09'),(101,6,'2006-02-15 05:07:09'),(102,15,'2006-02-15 05:07:09'),(103,16,'2006-02-15 05:07:09'),(104,9,'2006-02-15 05:07:09'),(105,1,'2006-02-15 05:07:09'),(106,10,'2006-02-15 05:07:09'),(107,7,'2006-02-15 05:07:09'),(108,13,'2006-02-15 05:07:09'),(109,13,'2006-02-15 05:07:09'),(110,3,'2006-02-15 05:07:09'),(111,1,'2006-02-15 05:07:09'),(112,9,'2006-02-15 05:07:09'),(113,15,'2006-02-15 05:07:09'),(114,14,'2006-02-15 05:07:09'),(115,1,'2006-02-15 05:07:09'),(116,4,'2006-02-15 05:07:09'),(117,10,'2006-02-15 05:07:09'),(118,2,'2006-02-15 05:07:09'),(119,5,'2006-02-15 05:07:09'),(120,15,'2006-02-15 05:07:09'),(121,2,'2006-02-15 05:07:09'),(122,11,'2006-02-15 05:07:09'),(123,16,'2006-02-15 05:07:09'),(124,3,'2006-02-15 05:07:09'),(125,16,'2006-02-15 05:07:09'),(126,1,'2006-02-15 05:07:09'),(127,5,'2006-02-15 05:07:09'),(128,9,'2006-02-15 05:07:09'),(129,6,'2006-02-15 05:07:09'),(130,1,'2006-02-15 05:07:09'),(131,4,'2006-02-15 05:07:09'),(132,14,'2006-02-15 05:07:09'),(133,12,'2006-02-15 05:07:09'),(134,2,'2006-02-15 05:07:09'),(135,15,'2006-02-15 05:07:09'),(136,13,'2006-02-15 05:07:09'),(137,14,'2006-02-15 05:07:09
COMMIT;

--
-- Dumping data for table language
--

SET AUTOCOMMIT=0;
INSERT INTO language VALUES (1,'English','2006-02-15 05:02:19'),(2,'Italian','2006-02-15 05:02:19'),(3,'Japanese','2006-02-15 05:02:19'),(4,'Mandarin','2006-02-15 05:02:19'),(5,'French','2006-02-15 05:02:19'),(6,'German','2006-02-15 05:02:19');
COMMIT;

SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
