var express = require('express');

var app = express();
var handlebars = require('express-handlebars').create({defaultLayout:'main'});
var bodyParser = require('body-parser');

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

app.engine('handlebars', handlebars.engine);
app.set('view engine', 'handlebars');
app.set('port', 5050);

// Boilerplate above

app.get('/',function(req,res){
  var getParams = [];
  for (var g in req.query){
    getParams.push({'name':g,'value':req.query[g]})
  }
  var getContext = {};
  getContext.dataList = getParams;
  res.render('get-loopback-improved', getContext);
});

app.post('/',function(req,res){
  var getParams = [];
 	var getContext = {};
  var postParams = [];
  var postContext = {};

	// First look for GET queries in the URL
  for (var g in req.query){
    getParams.push({'name':g,'value':req.query[g]})
  }
	if (getParams.length != 0 ) {
  	getContext.dataList = getParams;
	}
	// Then look for POST data
  for (var p in req.body){
    postParams.push({'name':p,'value':req.body[p]})
  }
  //console.log("Post:");
  //console.log(postParams);
  //console.log(req.body);
  postContext.dataList = postParams;
  postContext.urlData = getParams;
  res.render('post-loopback', postContext);
});

// Boilerplate below
app.use(function(req,res){
  res.status(404);
  res.render('404');
});

app.use(function(err, req, res, next){
  console.error(err.stack);
  res.type('plain/text');
  res.status(500);
  res.render('500');
});

app.listen(app.get('port'), function(){
  console.log('Express started on http://localhost:' + app.get('port') + '; press Ctrl-C to terminate.');
});
