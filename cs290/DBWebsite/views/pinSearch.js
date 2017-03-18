console.log.bind(console)
console.log("pinSearch.js is starting");

var authClosure = getCodes();
document.addEventListener('DOMContentLoaded', checkAuth)

function checkAuth(){
		var codeSet = authClosure();

		getCodeExamples();
		if (! codeSet.authCode )
			getLogin();
		else
			getSearchPage();
}

function boardSearch(){
	var codeSet = authClosure();

	if (! codeSet.accessToken ) {
			document.getElementById('debugDisplay').textContent = "ERROR: access_token is not set";
			getLogin();
			return;
	}
	var page = new XMLHttpRequest();
	var postString='?access_token=' + codeSet.accessToken;
	URL =  "https://api.pinterest.com/v1/me/boards/" + postString;
	console.log("Staring boardSearch with URL " + URL);
	page.open("GET", URL);
	page.addEventListener('load', function() {
			console.log("Status:", page.status)
			if (page.status < 100 || page.status >= 400 ){
				console.log ("Board search request failed with error: ", page.statusText)
				console.log (page.responseText);
				console.log (postString);
				document.getElementById('debugDisplay').textContent = "Get Token request failed with error: " + page.statusText;
			}
			else {
				var boardData = JSON.parse(page.responseText);
				console.log("-------------- Begin token response:");
				console.log (boardData);
				console.log("-------------- End token response:");
				var fullString='<table>';
				boardData.data.forEach(function(datum){
						fullString += '<tr><td><a href="'	+ datum.url + '">' + datum.name + '</a></td></tr>';
				});
				fullString += '</table>'
				document.getElementById('Output').innerHTML = fullString;
			}
		});
	page.send(null);
	console.log(JSON.stringify(postString));
}

function bindButton() {
	var Actor = function pinSearch(){

		var qString = document.getElementById('pinSearchString').value;
		if ( ! qString || qString == "" ) return;
		//qString = "quilt"; // Testing
		var codeSet = authClosure();
	
		if (! codeSet.accessToken ) {
				document.getElementById('debugDisplay').textContent = "ERROR: access_token is not set";
				getLogin();
				return;
		}
		var page = new XMLHttpRequest();
		var postString =  '?access_token=' + codeSet.accessToken;
		postString += '&query=' + qString;
		URL =  "https://api.pinterest.com/v1/me/search/pins/" + postString;
		console.log("Starting pinSearch with URL " + URL);
		page.open("GET", URL);

		page.addEventListener('load', function() {
				console.log("Status:", page.status)
				if (page.status < 100 || page.status >= 400 ){
					console.log ("Pin search request failed with error: ", page.statusText)
					console.log (page.responseText);
					console.log (postString);
					document.getElementById('debugDisplay').textContent = "Pin Search request failed with error: " + page.statusText;
				}
				else {
					var pinData = JSON.parse(page.responseText);
					console.log("-------------- Begin token response:");
					console.log (pinData);
					console.log("-------------- End token response:");
					var fullString='<table>';
					pinData.data.forEach(function(datum){
							fullString += '<tr><td><a href="'	+ datum.url + '">' + datum.note + '</a></td></tr>';
					});
					fullString += '</table>'
					document.getElementById('Output').innerHTML = fullString;
				}
			});
		page.send(null);
		console.log(JSON.stringify(postString));
	}; 
	return Actor;
}

function getCodes(){
		var accessToken = undefined;
		var authCode=undefined;
		console.log("Starting checkAuth");
   	var  url = window.location.href;

		var getAuth = function(){
			console.log("Starting getAuth, authCode = " + authCode + ", accessToken = " + accessToken);
			if ( accessToken && authCode) {
				return {'accessToken':accessToken, 'authCode':authCode};
			}
			// This code is straight from stackoverflow
			// http://stackoverflow.com/questions/901115/how-can-i-get-query-string-values-in-javascript
			//
			var searchString='';
			if ( !authCode ) {
				searchString='code';
			}
			console.log("Starting getAuth, searchString = " + searchString);
    	searchString = searchString.replace(/[\[\]]/g, "\\$&");
    	var regex = new RegExp("[?&]" + searchString + "(=([^&#]*)|&|#|$)"),
        	results = regex.exec(url);
    	if (!results) {
				return {'accessToken':undefined, 'authCode':undefined};
			}
    	if (!results[2]) 
				return {'accessToken':undefined, 'authCode':undefined};
			else {
				if (!authCode) {
					authCode = results[2];
					console.log("authCode = " + authCode);
					// TODO: GET ACCESS TOKEN HERE
					accessToken = getToken(authCode);
					console.log("accessToken = " + accessToken);
				}
				else if (!accessToken) {
					accessToken = results[2];
					console.log("accessToken = " + accessToken);
					return true;
				}
				else {
					console.log("Have both auth and token");
				}
				//return {'accessToken':accessToken, 'authCode':authCode};
			}
		}

		var outer = function() {
			console.log("Starting outer closure");
			getAuth();
			console.log("Returning outer closure with " + authCode +","+accessToken);
			return {'accessToken':accessToken, 'authCode':authCode};
		}
		//getAuth();
		//return getAuth;
		return outer;
}

function getLogin() {
	console.log("Starting getLogin");
	var redirectTo="https://ec2-50-112-191-239.us-west-2.compute.amazonaws.com/site/pinSearch.html"
  var appID="4885666555337124863"
  var authURL = "http://api.pinterest.com/oauth/?response_type=code&redirect_uri=" + redirectTo + "&client_id=" + appID + "&scope=read_public,write_public&state=nada"
	var clickString='<h3><a href="' + authURL + '">Login</a> to Pinterest to test the API</h3>'

	document.getElementById('mainHeader').innerHTML = clickString;

	console.log("Set up login text with " + authURL);
}


function clearResults() {
		document.getElementById('Output').innerHTML = ""
}


function getCodeExamples() {
	document.getElementById('codeDisplay1').innerHTML = '<h3>Board Listing</h3><iframe frameborder=1 width="100%" height="300" src="//jsfiddle.net/abrasss/tpj8h20a/embedded/" allowfullscreen="allowfullscreen" frameborder="0"></iframe>'
	document.getElementById('codeDisplay2').innerHTML = '<h3>Pin Search</h3> <iframe frameborder=1 width="100%" height="300" src="//jsfiddle.net/abrasss/s613sLf4/embedded/js/" allowfullscreen="allowfullscreen" frameborder="0"></iframe>'
}

function getSearchPage() {
	paraOne="<h2>You are signed into Pinterest</H2><p>Here are two buttons you can click to test basic API functions. Each button is followed by example code.";
  paraTwo='<p>As you can see the GET requests are very simple. For example you can retrieve a list of the user\'s boards with this URL:'
  paraThree = '<p><code style="background-color:#eee;color:#333">https://api.pinterest.com/v1/me/boards/?access_token=####</code>'
  paraFour = '<p>Handling the data in the result takes more lines of code than making the request.<p><br></p>'

	document.getElementById('mainHeader').innerHTML = paraOne + paraTwo + paraThree + paraFour;

	document.getElementById('mainDisplay1').innerHTML = '<button class="btn btn-default" onclick="boardSearch();" role="button">List your boards&raquo;</button>';

	document.getElementById('mainDisplay2').innerHTML = '<p><input type="text" name="pinSearch" id="pinSearchString"><input type="submit" id="dataSend" value="Search your pins&raquo;">'

	document.getElementById('mainDisplay3').innerHTML = '<button class="btn btn-default" onclick="clearResults();" role="button"> Clear results&raquo;</button>';

	document.getElementById('dataSend').addEventListener('click', bindButton());
	document.getElementById('Output').innerHTML = "";
}

function getToken(authCode){
		var page = new XMLHttpRequest();
		var accessTokenTmp="unset";
		var postData ={
			'grant_type':'authorization_code',
			'code': authCode,
			'client_id':'4885666555337124863',
			'client_secret':'c1ee3d876de304922dc8f0f6a8ef408815dfc737d4cf99073ea90e40bbc79ca5'
		};
		var postString='?grant_type=authorization_code&code=' + authCode + '&client_id=4885666555337124863&client_secret=c1ee3d876de304922dc8f0f6a8ef408815dfc737d4cf99073ea90e40bbc79ca5';
		//page.open("POST", "https://www.httpbin.org/post");
		URL =  "https://api.pinterest.com/v1/oauth/token" + postString;
		page.open("POST", URL, false); // gah! synchronous!!
		//page.setRequestHeader("Content-Type", "application/json") // Pinterest doesn't allow

		page.addEventListener('load', function() {
				console.log("Status:", page.status)
				if (page.status < 100 || page.status >= 400 ){
					console.log ("Get Token request failed with error: ", page.statusText)
					console.log (page.responseText);
					console.log (postString);
					accessTokenTmp = null;
				}
				else {
					console.log("-------------- Begin token response:");
					console.log (page.responseText);
					var tmpObj=JSON.parse(page.responseText);
					console.log (tmpObj.access_token);
					console.log("-------------- End token response:");
					accessTokenTmp = tmpObj.access_token;
					//return page.responseText.access_token;
				}
		});
		page.send(postData);
		return accessTokenTmp;
}
console.log("pinSearch.js is done");

