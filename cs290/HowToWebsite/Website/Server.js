// vim: tabstop=2
// From https://www.codementor.io/codeforgeek/build-website-from-scratch-using-expressjs-and-bootstrap-du107sby7

//var path = __dirname + '/views/';
var site = __dirname + '/site/'; 
var bsdir = __dirname + '/'; 
var https = require("https");
var fs = require("fs");
var express = require("express");
//var app = express();
var router = express.Router();

var options = {
	key: fs.readFileSync("keys/key.pem"),
	cert: fs.readFileSync("keys/cert.pem")
};

router.use(function (req,res,next) {
	console.log("/" + req.method + req.path);
	next();
});

router.get("/index.html",function(req,res){
	//res.send('Hello Woorld!'); // For testing :)
	res.sendFile(site + "index.html");
});

router.get("/",function(req,res){
	res.sendFile(site + "main.html");
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
	res.sendFile(bsdir + "node_modules/bootstrap/dist/css/jumbotron.css");
});




var app = express();
app.use("/",router);
app.use("*",function(req,res){
	res.sendFile(site + "404.html");
});
/**/


app.listen(80, function() {
	console.log("Listening at Port 80");
});

var appSecure = https.createServer(options, app).listen(443);
console.log("Listening at Port 443");

