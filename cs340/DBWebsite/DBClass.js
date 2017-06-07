// vim: tabstop=2
// From https://www.codementor.io/codeforgeek/build-website-from-scratch-using-expressjs-and-bootstrap-du107sby7

//var path = __dirname + '/views/';
var site = __dirname + '/views/'; 
var bsdir = __dirname + '/'; 
var https = require("https");
var fs = require("fs");
var express = require("express");
var handlebars = require("express-handlebars").create({defaultLayout:'main'});
var bodyParser = require("body-parser");

var mysql=require('mysql');
var litpool = mysql.createPool({
	host : 'localhost',
	user : 'ec2-user',
	database : 'lit'
});
var bsgpool = mysql.createPool({
	host : 'localhost',
	user : 'ec2-user',
	database : 'bsg'
});

// 
// litJoinOne selects PRIMARY MOMENTS ONLY 
// and produces the following columns:
// 	bookID, bookTitle, O.genre, O.publication_date,
// 	authorName,
// 	M.description, M.date,
// 	L.address, L.street, L.city, L.country,
// 	bookCity, ## probably redundant now
// 	bookLocation
// 	characterName
// If you want to see all moments, use litJoinTwo
var litJoinOne = `(SELECT 
	O.id as bookID, O.title as bookTitle, O.genre, O.publication_date, 
	concat_ws (' ',A.title, A.fname, A.mnames,A.lname) as authorName, 
	M.description,M.date, 
	L.address, L.street,L.city, L.country,
	concat_ws (', ',L.city, L.country) as bookCity,
  concat_ws (', ',NULLIF(concat_ws(' ', L.address, L.street),' '),L.city, L.country) as bookLocation,
	concat_ws (' ', K.title,K.fname,K.lname) as characterName 
	from opus O 
	inner join opus_author OA on O.id = OA.oid 
	inner join author A on A.id = OA.aid 
	inner join (select * from moment where description='PRIMARY') M on O.id = M.oid 
	inner join location L on M.lid = L.id 
	inner join karacter_moment KM on M.id = KM.mid 
	inner join karacter K on K.id = KM.kid 
	)`;

var litJoinTwo = `(SELECT 
	M.id as momentID, 
	REPLACE(M.description,'PRIMARY', 'Primary location for book') as description,
	M.date,
	O.title as bookTitle,
	concat_ws (' ',A.title, A.fname, A.mnames,A.lname) as authorName,
	concat_ws (' ', K.title,K.fname,K.lname) as characterName,
	concat_ws (', ',NULLIF(concat_ws(' ', L.address, L.street),' '),L.city, L.country) as location
	from moment M
	inner join location L on M.lid = L.id
	inner join opus O on M.oid = O.id
	inner join karacter_moment KM on M.id = KM.mid
	inner join karacter K on K.id = KM.kid
	inner join opus_author OA on O.id = OA.oid
	inner join author A on A.id = OA.aid
	)`;

var app = express();
var router = express.Router();

var options = {
	// For https
	key: fs.readFileSync("keys/key.pem"),
	cert: fs.readFileSync("keys/cert.pem")
};

router.use(function (req,res,next) {
	// Logs every call; for debugging
	console.log(req.method + " " + req.path);
	next();
});

router.get("/index.html",function(req,res){
	res.send('Hello World!'); // For testing
	//res.sendFile(site + "index.html");
});

router.get("/lit",function(req,res,next){
	var context = {};
	res.render(site + "home.handlebars", context);
});

// This same server runs the BSG database 
// from an earlier assignment.
router.get("/bsg",function(req,res,next){
	var context = {};

	bsgpool.query("SELECT id AS people_id,fname,lname,IFNULL(homeworld,'unknown') as homeworld,IFNULL(age,'unknown') as age FROM bsg_people ORDER BY lname,fname ASC;", 
	function (err,rows,fields)
	{
		if (err) {
			next(err);
			return;
		}
		context.textresults = JSON.stringify(rows);
		context.results = JSON.parse(context.textresults);
		context.history = context["results"].length;
		res.render(site + "bsg.handlebars", context);
		//console.log(context);
	});
});

router.get("/delete",function(req,res){  // TODO DELETE
	var context = {}
	var change = null;

	//console.log ("Delete requested");
	//console.log("Req.body: ", req.body, "Req.params:", req.params);
	if ( req.query.id ) {
		var itemID = req.query.id;
		var change='DELETE FROM workouts WHERE id = '.concat('"', itemID, '";');
		//console.log("change is ", change);
		pool.query(change, function (err,rows,fields)
		{
			if (err) {
				//next(err);
				console.log(err);
				res.status(500)
					.send("Database Error");
			}
			else {
				res.status(200)
					.send("OK");
			}
		});
	}
});


router.get("/update",function(req,res){  // TODO DELETE
	var context = {}
	var change = null;

	//console.log ("Update requested");
	//console.log("Req.body: ", req.body, "Req.params:", req.params);
	if ( req.query.id ) {
		var newName = req.query.name;
		var newReps = req.query.reps;
		var newWeight = req.query.weight;
		var newDate = req.query.date;
		var newLbs = req.query.lbs;
		change='UPDATE workouts SET '.concat('name="', newName, '", reps="',newReps, '", weight="' ,newWeight,'", date="',newDate,'", lbs="', newLbs, '" WHERE id="',req.query.id,'";');
		//console.log("change is ", change);
		pool.query(change, function (err,rows,fields)
		{
			if (err) {
				//next(err);
				console.log(err);
				res.status(500)
					.send("Database Error");
			}
			else {
				//console.log("Sending OK");
				res.status(200)
					.send("OK");
			}
		});
		/*
		res.status(200)
			.send("OK");
		*/
	}
});

router.get("/getitem",function(req,res){  // TODO DELETE
	var context = {}
	var change = null;

	//console.log ("GetItem requested");
	//console.log("Req.body: ", req.body, "Req.params:", req.params);
	if ( req.query.id ) {
		var itemID = req.query.id;
		var change='SELECT id,name,reps,weight,lbs, DATE_FORMAT(date,"%Y-%m-%d") AS date FROM workouts WHERE id = '.concat('"', itemID, '";');
		//console.log("change is ", change);
		pool.query(change, function (err,rows,fields)
		{
			if (err) {
				//next(err);
				console.log(err);
				res.status(500)
					.send("Database Error");
			}
			else {
				res.status(200)
					.send(rows);
			}
		});
	}
});

router.get("/AddOneBook",function(req,res){
	console.log("In AddOneBook, Req.query: ", req.query);

	var authorFname = '';
	var authorMnames = '';
	var authorLname = '';
	var authorTitle = '';
	var bookTitle = '';
	var locCity = '';
	var locCountry = '';

	if ( req.query.authorFname ) 
		{ authorFname = authorFname.concat("'",req.query.authorFname, "'"); } else { authorFname = null;}
	if ( req.query.authorLname ) 
		{ authorLname = authorLname.concat("'",req.query.authorLname, "'"); } else { authorLname = null;}
	if ( req.query.authorMnames ) 
		{ authorMnames = authorMnames.concat("'",req.query.authorMnames, "'"); } else { authorMnames = null;}
	if ( req.query.authorTitle ) 
		{ authorTitle = authorTitle.concat("'",req.query.authorTitle, "'"); } else { authorTitle = null;}
	if ( req.query.title ) 
		{ bookTitle = bookTitle.concat("'",req.query.title, "'"); } else { bookTitle = null;}
	if ( req.query.city ) 
		{ locCity = locCity.concat("'",req.query.city, "'"); } else { locCity = null;}
	if ( req.query.country ) 
		{ locCountry = locCountry.concat("'",req.query.country, "'"); } else { locCountry = null;}


	console.log("authorFname = ", authorFname);
	console.log("authorLname = ", authorLname);
	console.log("authorMnames = ", authorMnames);
	console.log("authorTitle = ", authorTitle);
	console.log("bookTitle = ", bookTitle);
	console.log("locCity = ", locCity);
	console.log("locCountry = ", locCountry);
	//Author first, then location, then opus (book), then opus_author and moment <phew!>
	// ON unique: update
	var DBcmd_1='';
	DBcmd_1 = DBcmd_1.concat("INSERT INTO author (fname,mnames,lname,title) VALUE (");
	DBcmd_1 = DBcmd_1.concat(authorFname,",",authorMnames,",",authorLname,",",authorTitle);
	DBcmd_1 = DBcmd_1.concat(") ON DUPLICATE KEY UPDATE id=id;");
	console.log("DBcmd_1 = ", DBcmd_1);

	var DBcmd_2='';
	DBcmd_2 = DBcmd_2.concat("INSERT INTO location (city,country) VALUE (");
	DBcmd_2 = DBcmd_2.concat(locCity,",",locCountry);
	DBcmd_2 = DBcmd_2.concat(") ON DUPLICATE KEY UPDATE id=id;");
	console.log("DBcmd_2 = ", DBcmd_2);

	var DBcmd_3='';
	DBcmd_3 = DBcmd_3.concat("INSERT INTO opus (title) VALUE (");
	DBcmd_3 = DBcmd_3.concat(bookTitle);
	DBcmd_3 = DBcmd_3.concat(") ON DUPLICATE KEY UPDATE id=id;");
	console.log("DBcmd_3 = ", DBcmd_3);

	var DBcmd_4='';
	DBcmd_4 = DBcmd_4.concat("INSERT INTO opus_author (oid,aid) VALUE (");
	DBcmd_4 = DBcmd_4.concat("(SELECT id FROM opus WHERE title=", bookTitle,"),");
	// UGH  need to special case NULLS
	DBcmd_4 = DBcmd_4.concat("(SELECT id FROM author WHERE fname");
	if ( authorFname == null )
		{ DBcmd_4 = DBcmd_4.concat("is NULL AND lname"); }
		else
		{ DBcmd_4 = DBcmd_4.concat("=", authorFname," AND lname"); }
	if ( authorLname == null )
		{ DBcmd_4 = DBcmd_4.concat("is NULL LIMIT 1)"); }
		else
		{ DBcmd_4 = DBcmd_4.concat("=", authorLname," LIMIT 1)"); }
	DBcmd_4 = DBcmd_4.concat(") ON DUPLICATE KEY UPDATE oid=oid;");
	console.log("DBcmd_4 = ", DBcmd_4);

	var DBcmd_5='';
	DBcmd_5 = DBcmd_5.concat("INSERT INTO moment (oid,lid,description) VALUE (");
	DBcmd_5 = DBcmd_5.concat("(SELECT id FROM opus WHERE title=", bookTitle,"),");
	// UGH  need to special case NULLS  WTF
	DBcmd_5 = DBcmd_5.concat("(SELECT id FROM location WHERE address is NULL AND street is NULL AND city");
	if ( locCity == null )
		{ DBcmd_5 = DBcmd_5.concat("is NULL AND country"); }
		else
		{ DBcmd_5 = DBcmd_5.concat("=", locCity," AND country"); }
	if ( locCountry == null )
		{ DBcmd_5 = DBcmd_5.concat("is NULL LIMIT 1)"); }
		else
		{ DBcmd_5 = DBcmd_5.concat("=", locCountry," LIMIT 1),"); } 
		// Must use limit 1 here because mysql has a bug that allows multiple null-column 'unique' keys
	DBcmd_5 = DBcmd_5.concat("'PRIMARY'");
	DBcmd_5 = DBcmd_5.concat(") ON DUPLICATE KEY UPDATE oid=oid;");
	console.log("DBcmd_5 = ", DBcmd_5);

	/* ************************************************** */

	var returnString=''
	litpool.query(DBcmd_1, function (err,rows,fields)
	{
		if (err) {
			console.log('DBcmd_1:',err);
			res.status(500).send(err);
			return;
		}
		//console.log("DBcmd_1 returned: ", context);
		//returnString = returnString.concat(context);

		// We must go deeper...
		litpool.query (DBcmd_2, function(err,rows,fields)
		{
			if (err) {
				console.log('DBcmd_2:',err);
				res.status(500).send(err);
				return;
			}
			////console.log("DBcmd_2 returned: ", context);
			//returnString = returnString.concat(context);

			// and deeper...
			litpool.query (DBcmd_3, function(err,rows,fields)
			{
				if (err) {
					console.log('DBcmd_3:',err);
					res.status(500).send(err);
					return;
				}
				//console.log("DBcmd_3 returned: ", context);
				//returnString = returnString.concat(context);
		
				// why are we doing this again?
				litpool.query (DBcmd_4, function(err,rows,fields)
				{
					if (err) {
						console.log('DBcmd_4:',err);
						res.status(500).send(err);
						return;
					}
					//console.log("DBcmd_4 returned: ", context);
					//returnString = returnString.concat(context);

					// next time I'm building my db with one giant table
					litpool.query (DBcmd_5, function(err,rows,fields)
					{
						if (err) {
							console.log('DBcmd_5:',err);
							res.status(500).send(err);
							return;
						}
						//console.log("DBcmd_5 returned: ", context);
						//returnString = returnString.concat(context);

						res.status(200).send(returnString)
					});
				});
			});
		});
	});
});

router.get("/SearchInBooks",function(req,res){
	var context = {}
	var DBquery = null;
	var addAnd = false;

	//console.log("Req.query: ", req.query);
	var searchTitle = req.query.title;
	var searchAuthor = req.query.author;
	var searchLocation = req.query.location;
	var searchCharacter = req.query.character;
	var useDB = req.query.db;
	//
	if ( ! useDB )
	{
		useDB = litJoinOne; // The default
	}

	console.log ("useDB is ", useDB);
	var DBquery='';
	if ( useDB == 'litJoinOne' ) {
		console.log ("clause ONE");
	 	DBquery='SELECT * FROM (SELECT dbjoin.bookID, dbjoin.bookTitle, dbjoin.authorName, dbjoin.bookLocation, group_concat(dbjoin.characterName) as Characters '; 
		DBquery = DBquery.concat('FROM ', eval(useDB),' dbjoin GROUP BY bookID');
	}
	else if ( useDB == 'litJoinTwo' ) {
		console.log ("clause TWO");
	 	DBquery='SELECT * FROM (SELECT dbjoin.momentID, dbjoin.location as bookLocation, dbjoin.description, dbjoin.bookTitle, dbjoin.authorName, group_concat(dbjoin.characterName) as Characters '; 
		DBquery = DBquery.concat('FROM', eval(useDB), ' dbjoin GROUP BY momentID ')
	}
	else {
		console.log ("clause THREE");
		// an error, really
	}
	DBquery = DBquery.concat(' ORDER BY bookTitle) allFields WHERE')

	if ( ! (searchTitle || searchAuthor||searchLocation||searchCharacter )) 
	{ 
				console.log("Error: No search terms found in SearchInBooks request");
				return;
	}
	if ( searchTitle ) 
	{ 
		DBquery = DBquery.concat(' bookTitle like "%',searchTitle,'%"'); 
		addAnd = true;
	}
	if ( searchAuthor ) 
	{ 
		if (addAnd) {DBquery = DBquery.concat(' AND ');}
		DBquery = DBquery.concat(' authorName like "%',searchAuthor,'%"'); 
		addAnd = true;
	}
	if ( searchLocation ) 
	{ 
		if (addAnd) {DBquery = DBquery.concat(' AND ');}
		DBquery = DBquery.concat(' bookLocation like "%',searchLocation,'%"'); 
		addAnd = true;
	}
	if ( searchCharacter ) 
	{ 
		if (addAnd) {DBquery = DBquery.concat(' AND ');}
		DBquery = DBquery.concat(' Characters like "%',searchCharacter,'%"'); 
		addAnd = true;
	}
	//DBquery = DBquery.concat('GROUP BY bookID');
	DBquery = DBquery.concat(';');
	
	console.log ("Running SearchInBook");
	console.log(searchTitle, searchAuthor, searchLocation,searchCharacter);
	console.log("Query is: ", DBquery);

	if (DBquery ) {
		litpool.query(DBquery, function (err,rows,fields)
		{
			if (err) {
				//next(err);
				console.log(err);
				return;
			}
			context.textresults = JSON.stringify(rows);
			context.results = JSON.parse(context.textresults);
			console.log("mySQL returned: ", context);
			//res.render(site + "searchResults.handlebars", context);
			res.status(200).send(context)
			//res.send(site + "searchResults.handlebars", context);
		});
		//TODO: eliminate the need to render the entire page
		//use res.send
		//return;
	}
});

router.get("/addExercise",function(req,res){  // TODO DELETE
	var context = {}
	var change = null;

	//console.log("Req.query: ", req.query);
	var newName = req.query.name;
	var newReps = req.query.reps;
	var newWeight = req.query.weight;
	var newDate = req.query.date;
	var newLbs = req.query.lbs;
	//
	change='INSERT INTO workouts (name, reps,weight,date,lbs ) VALUES ("'.concat(newName, '", "' , newReps , '", "' , newWeight , '", "' , newDate , '", "' , newLbs , '");');
	//console.log ("New item entered");
	//console.log(newName, newReps, newWeight, newDate, newLbs);
	//console.log("change is ", change);

	if (change ) {
		pool.query(change, function (err,rows,fields)
		{
			if (err) {
				//next(err);
				console.log(err);
				return;
			}
			context.textresults = JSON.stringify(rows);
			context.results = JSON.parse(context.textresults);
			//console.log("mySQL returned: ", context);
			res.send(context.textresults);
		});
		//TODO: eliminate the need to render the entire page
		//use res.send
		//return;
	}
});

router.post("/",function(req,res){
	var context = {}
	var change = null;

	//console.log("Req.body: ", req.body);
	if ( req.body['newExercise'] ) {
		var newName = req.body.exercise;
		var newReps = req.body.reps;
		var newWeight = req.body.weight;
		var newDate = req.body.date;
		var newKilos = req.body.kilos;
		var lbs = 'true';
		if ( newKilos ) { lbs='false'; }
		//TODO: Add to the database here
		change='INSERT INTO workouts (name, reps,weight,date,lbs ) VALUES ("'.concat(newName, '", "' , newReps , '", "' , newWeight , '", "' , newDate , '", "' , lbs , '");');
		//console.log ("New item entered");
		//console.log(newName, newReps, newWeight, newDate, newKilos);
		//console.log("change is ", change);
	}

	else if ( req.body['editButton'] ) {
		//console.log ("Edit requested");
		//console.log(req.body);
		var editItem = req.body.editButton;
	}

	if (change ) {
		pool.query(change, function (err,rows,fields)
		{
			if (err) {
				//next(err);
				console.log(err);
				return;
			}
			context.textresults = JSON.stringify(rows);
			context.results = JSON.parse(context.textresults);
			context.history = context["results"].length;
			//console.log("mySQL returned: ", context);
		});
		//TODO: eliminate the need to render the entire page
		//use res.send
		//return;
	}


	query =	"SELECT id,name,reps,weight,lbs, DATE_FORMAT(date,'%Y-%m-%d') AS date FROM workouts ORDER BY date DESC;" 
	pool.query(query, function (err,rows,fields)
	{
		if (err) {
			//next(err);
			console.log(err);
			return;
		}
		context.textresults = JSON.stringify(rows);
		context.results = JSON.parse(context.textresults);
		context.history = context["results"].length;
		//console.log("mySQL returned: ", context);
		res.render(site + "home.handlebars", context);
	});
});

router.get("/test",function(req,res){
	var context={ handlebars:"Yes"};
	pool.query("SELECT id,name,reps,weight,lbs, DATE_FORMAT(date,'%Y-%m-%d') AS date FROM workouts ORDER BY date DESC;", 
	function (err,rows,fields)
	{
		if (err) {
			//next(err);
			console.log(err);
			return;
		}
		context.textresults = JSON.stringify(rows);
		context.results = JSON.parse(context.textresults);
		console.log(context);
		res.render(site + "test.handlebars", context);
	});
});

router.get("/about",function(req,res){
	res.sendFile(site + "about.html");
});

router.get("/contact",function(req,res){
	res.sendFile(site + "contact.html");
});

router.get("/site/:file",function(req,res){
	console.log("Did I even get here?")
	res.sendFile(site + req.params.file);
});

router.get("/script.js",function(req,res){
	res.sendFile(site + "script.js");
});

router.get("/style.css",function(req,res){
	res.sendFile(site + "style.css");
});
router.get("/bootstrap.min.css",function(req,res){
	res.sendFile(bsdir + "node_modules/bootstrap/dist/css/bootstrap.min.css");
});
router.get("/bootstrap.min.js",function(req,res){
	res.sendFile(bsdir + "node_modules/bootstrap/dist/js/bootstrap.min.js");
});
router.get("/bootstrap.min.css.map",function(req,res){
	res.sendFile(bsdir + "node_modules/bootstrap/dist/css/bootstrap.min.css.map");
});
router.get("/jumbotron.css",function(req,res){
	res.sendFile(bsdir + "node_modules/jumbotron/public/css/jumbotron.css");
});

app.use(function(err, req, res,next) {
	console.error(err.stack);
	console.log(err);
	//req.status(500).send('Something broke!');
});
/**/

app.use(bodyParser.urlencoded({extended: false}));
app.use(bodyParser.json());
app.engine('handlebars', handlebars.engine);
app.use("/",router);
app.use("*",function(req,res){
	res.status(404);
	res.sendFile(site + "404.html");
});


app.listen(4000, function() {
	console.log("Listening at Port 4000");
});

/*
var appSecure = https.createServer(options, app).listen(443);
console.log("Listening at Port 443");
*/

