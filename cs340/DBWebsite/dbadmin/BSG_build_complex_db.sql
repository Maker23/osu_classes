-- MySQL dump 10.13  Distrib 5.1.69, for redhat-linux-gnu (x86_64)
--
-- Host: mysql.eecs.oregonstate.edu    Database: CS275
-- ------------------------------------------------------
-- Server version	5.1.67-community-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `bsg_cert`
--

DROP TABLE IF EXISTS `bsg_cert`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `bsg_cert` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `title` varchar(255) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `bsg_cert`
--

LOCK TABLES `bsg_cert` WRITE;
/*!40000 ALTER TABLE `bsg_cert` DISABLE KEYS */;
INSERT INTO `bsg_cert` VALUES (1,'Raptor'),(2,'Viper'),(3,'Mechanic'),(4,'Command');
/*!40000 ALTER TABLE `bsg_cert` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `bsg_cert_people`
--

DROP TABLE IF EXISTS `bsg_cert_people`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `bsg_cert_people` (
  `cid` int(11) NOT NULL DEFAULT '0',
  `pid` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`cid`,`pid`),
  KEY `pid` (`pid`),
  CONSTRAINT `bsg_cert_people_ibfk_1` FOREIGN KEY (`cid`) REFERENCES `bsg_cert` (`id`),
  CONSTRAINT `bsg_cert_people_ibfk_2` FOREIGN KEY (`pid`) REFERENCES `bsg_people` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `bsg_cert_people`
--

LOCK TABLES `bsg_cert_people` WRITE;
/*!40000 ALTER TABLE `bsg_cert_people` DISABLE KEYS */;
INSERT INTO `bsg_cert_people` VALUES (2,2),(4,2),(4,3),(2,4),(4,6),(1,7),(3,8),(3,9),(1,12),(1,14);
/*!40000 ALTER TABLE `bsg_cert_people` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `bsg_people`
--

DROP TABLE IF EXISTS `bsg_people`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `bsg_people` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `fname` varchar(255) NOT NULL,
  `lname` varchar(255) DEFAULT NULL,
  `homeworld` int(11) DEFAULT NULL,
  `age` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `homeworld` (`homeworld`),
  CONSTRAINT `bsg_people_ibfk_1` FOREIGN KEY (`homeworld`) REFERENCES `bsg_planets` (`id`) ON DELETE SET NULL ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=15 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `bsg_people`
--

LOCK TABLES `bsg_people` WRITE;
/*!40000 ALTER TABLE `bsg_people` DISABLE KEYS */;
INSERT INTO `bsg_people` VALUES (1,'William','Adama',3,61),(2,'Lee','Adama',3,30),(3,'Laura','Roslin',3,NULL),(4,'Kara','Thrace',3,NULL),(5,'Gaius','Baltar',3,NULL),(6,'Saul','Tigh',NULL,71),(7,'Karl','Agathon',1,NULL),(8,'Galen','Tyrol',1,32),(9,'Callandra','Henderson',NULL,NULL),(10,'TestPerson',NULL,1,NULL),(11,'Samuel','Anders',19,NULL),(12,'Margaret','Edmondson',NULL,NULL),(13,'Brendan','Costanza',NULL,36),(14,'Sharon','Valerii',23,NULL);
/*!40000 ALTER TABLE `bsg_people` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `bsg_planets`
--

DROP TABLE IF EXISTS `bsg_planets`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `bsg_planets` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  `population` bigint(20) DEFAULT NULL,
  `language` varchar(255) DEFAULT NULL,
  `capital` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=24 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `bsg_planets`
--

LOCK TABLES `bsg_planets` WRITE;
/*!40000 ALTER TABLE `bsg_planets` DISABLE KEYS */;
INSERT INTO `bsg_planets` VALUES (1,'Gemenon',2800000000,'Old Gemenese','Oranu'),(2,'Leonis',2600000000,'Leonese','Luminere'),(3,'Caprica',4900000000,'Caprican','Caprica City'),(7,'Sagittaron',1700000000,NULL,'Tawa'),(16,'Aquaria',25000,NULL,NULL),(17,'Canceron',6700000000,NULL,'Hades'),(18,'Libran',2100000,NULL,NULL),(19,'Picon',1400000000,NULL,'Queestown'),(20,'Scorpia',450000000,NULL,'Celeste'),(21,'Tauron',2500000000,'Tauron','Hypatia'),(22,'Virgon',4300000000,NULL,'Boskirk'),(23,'Troy',NULL,NULL,NULL);
/*!40000 ALTER TABLE `bsg_planets` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `bsg_ship_assignment`
--

DROP TABLE IF EXISTS `bsg_ship_assignment`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `bsg_ship_assignment` (
  `pid` int(11) NOT NULL,
  `cid` int(11) NOT NULL,
  `sid` int(11) NOT NULL,
  PRIMARY KEY (`pid`,`cid`,`sid`),
  KEY `sid` (`sid`),
  KEY `cid` (`cid`,`sid`),
  CONSTRAINT `bsg_ship_assignment_ibfk_2` FOREIGN KEY (`cid`, `sid`) REFERENCES `bsg_ship_instance` (`class`, `id`),
  CONSTRAINT `bsg_ship_assignment_ibfk_1` FOREIGN KEY (`pid`) REFERENCES `bsg_people` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `bsg_ship_assignment`
--

LOCK TABLES `bsg_ship_assignment` WRITE;
/*!40000 ALTER TABLE `bsg_ship_assignment` DISABLE KEYS */;
INSERT INTO `bsg_ship_assignment` VALUES (1,1,1),(2,2,1),(8,1,1),(9,1,1),(13,3,3),(13,3,87),(2,4,121),(12,3,179),(2,4,289),(5,4,289),(4,5,316),(12,3,621),(13,3,621),(2,4,1104),(3,5,2343),(13,5,2343),(11,5,3203),(13,4,7242),(1,5,8757),(11,5,8757);
/*!40000 ALTER TABLE `bsg_ship_assignment` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `bsg_ship_class`
--

DROP TABLE IF EXISTS `bsg_ship_class`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `bsg_ship_class` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(1000) NOT NULL,
  `variant` varchar(1000) DEFAULT NULL,
  `LOA` int(11) DEFAULT NULL,
  `crew_capacity` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `bsg_ship_class`
--

LOCK TABLES `bsg_ship_class` WRITE;
/*!40000 ALTER TABLE `bsg_ship_class` DISABLE KEYS */;
INSERT INTO `bsg_ship_class` VALUES (1,'Battlestar','Galactica',4720,5000),(2,'Battlestar','Pegasus',5872,1750),(3,'Raptor',NULL,28,10),(4,'Viper','Mk II',28,1),(5,'Viper','Mk VII',32,1),(6,'Colonial One',NULL,277,150),(7,'Astral Queen',NULL,NULL,1500),(8,'Gemenon Traveler',NULL,197,NULL);
/*!40000 ALTER TABLE `bsg_ship_class` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `bsg_ship_instance`
--

DROP TABLE IF EXISTS `bsg_ship_instance`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `bsg_ship_instance` (
  `id` int(11) NOT NULL,
  `class` int(11) NOT NULL,
  `operational` tinyint(1) DEFAULT NULL,
  `based_in_id` int(11) DEFAULT NULL,
  `based_in_class` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`,`class`),
  KEY `class` (`class`),
  KEY `based_in_id` (`based_in_id`,`based_in_class`),
  CONSTRAINT `bsg_ship_instance_ibfk_2` FOREIGN KEY (`based_in_id`, `based_in_class`) REFERENCES `bsg_ship_instance` (`id`, `class`),
  CONSTRAINT `bsg_ship_instance_ibfk_1` FOREIGN KEY (`class`) REFERENCES `bsg_ship_class` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `bsg_ship_instance`
--

LOCK TABLES `bsg_ship_instance` WRITE;
/*!40000 ALTER TABLE `bsg_ship_instance` DISABLE KEYS */;
INSERT INTO `bsg_ship_instance` VALUES (1,1,1,NULL,NULL),(1,2,1,NULL,NULL),(1,3,0,1,1),(2,3,1,1,1),(3,3,0,1,1),(24,5,1,1,1),(27,3,1,1,1),(42,3,0,1,1),(87,3,1,1,1),(121,4,1,1,1),(124,3,1,1,1),(179,3,1,1,2),(289,4,0,1,1),(305,3,0,1,1),(312,5,1,1,2),(313,5,1,1,2),(316,5,1,1,2),(372,5,1,1,2),(412,5,1,1,2),(613,5,1,1,2),(621,3,0,1,1),(861,3,1,1,2),(923,3,1,1,2),(1104,4,1,1,1),(2220,4,1,1,1),(2276,5,1,1,1),(2306,5,0,NULL,NULL),(2343,5,0,NULL,NULL),(3021,5,0,NULL,NULL),(3203,5,0,NULL,NULL),(3266,4,1,1,1),(3621,5,0,NULL,NULL),(3642,5,0,NULL,NULL),(4267,4,0,1,1),(7242,4,1,1,1),(7961,5,1,1,1),(8754,4,0,1,1),(8757,5,1,1,1);
/*!40000 ALTER TABLE `bsg_ship_instance` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2013-10-28  0:25:27
