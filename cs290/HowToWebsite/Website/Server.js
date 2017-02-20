// From https://www.codementor.io/codeforgeek/build-website-from-scratch-using-expressjs-and-bootstrap-du107sby7

//var path = __dirname + '/views/';
var path = __dirname + '/'; 
var express = require("express");
var app = express();
var router = express.Router();

router.use(function (req,res,next) {
  console.log("/" + req.method + req.path);
  next();
});

router.get("/",function(req,res){
  //res.send('Hello Woorld!');
  res.sendFile(path + "index.html");
});

router.get("/about",function(req,res){
  res.sendFile(path + "about.html");
});

router.get("/contact",function(req,res){
  res.sendFile(path + "contact.html");
});

router.get("/script.js",function(req,res){
  res.sendFile(path + "script.js");
});

app.use("/",router);

/*
app.get('/', function(req,res){
  res.send('Hello WOrld!');
});
*/

app.use("*",function(req,res){
  res.sendFile(path + "404.html");
});


app.listen(3000,function(){
  console.log("Live at Port 3000");
});
