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
var pool = mysql.createPool({
	host : 'localhost',
	user : 'ec2-user',
	database : 'workouts'
});

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
	//res.send('Hello World!'); // For testing
	res.sendFile(site + "index.html");
});

router.get("/",function(req,res){
	var context = {};

	pool.query("SELECT id,name,reps,weight,lbs, DATE_FORMAT(date,'%Y-%m-%d') AS date FROM workouts ORDER BY date DESC;", 
	function (err,rows,fields)
	{
		if (err) {
			next(err);
			return;
		}
		context.textresults = JSON.stringify(rows);
		context.results = JSON.parse(context.textresults);
		context.history = context["results"].length;
		//console.log(context);
		res.render(site + "home.handlebars", context);
	});
});

router.get("/delete",function(req,res){
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


router.get("/update",function(req,res){
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

router.get("/getitem",function(req,res){
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

router.get("/addExercise",function(req,res){
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
	res.sendFile(site + "404.html");
});


app.listen(3000, function() {
	console.log("Listening at Port 3000");
});

/*
var appSecure = https.createServer(options, app).listen(443);
console.log("Listening at Port 443");
*/

