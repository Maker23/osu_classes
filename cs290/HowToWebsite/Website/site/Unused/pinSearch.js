console.log.bind(console)
console.log("Homework assignment:HowTo Guide")
console.log("CS290-400-W14  abrasss@  Mar 2, 2017")
console.log("pinSearch.js file is loading");


document.addEventListener('DOMContentLoaded', attachSearch)


function attachSearch(){
	document.getElementById('dataSubmit').addEventListener('click',
		function getPin(event){
			  event.preventDefault();
			  var searchTerms = document.getElementById('searchTerms').value;
			  document.getElementById("searchResult").textContent = "Pins for " + searchTerms;
			  
          var redirectTo="https://ec2-50-112-191-239.us-west-2.compute.amazonaws.com/pinSearch.html"
          var appID="4885666555337124863"
          var URL = "htredirectTo://api.pinterest.com/oauth/?response_type=code&redirect_uri=" + redirectTo + "&client_id=" + appID + "&scope=read_public,write_public&state=nada"
			  
			 		var req = new XMLHttpRequest();
			  	req.open("GET", URL);
				  console.log("Web request sent to " + URL);
			  
			  req.addEventListener('load', function() {
				  console.log("Status:", req.status)
				  if (req.status < 100 || req.status >= 400 ){
					  console.log ("Web request failed with error: ", req.statusText)
				  }
				  else {
					  console.log("Web request successful")
					  console.log(JSON.parse(req.responseText))
					  var weatherObj = JSON.parse(req.responseText)
					  var currentTime = new Date()
						.toString();
					  document.getElementById("location").textContent = "Pins for " + weatherObj.name + " at " + currentTime;
					  
					  var tmpString = "<p>"
					  var tempF = ((weatherObj.main.temp * 9 / 5) - 459.67).toFixed(1);
					  tmpString += "<br><strong>Temp: </strong>" + tempF + " F";
					  tmpString += "<br><strong>Pins:  </strong>" + weatherObj.weather[0].description;
					  if ( typeof(weatherObj.clouds) == "object" ) {
						  tmpString += "<br><strong>Cloud cover: </strong>";
						  Object.entries(weatherObj.clouds).forEach(function(x) { tmpString += x[1] + " percent"						  })
					  }
					  tmpString += "<br><strong>Wind:</strong> speed " + weatherObj.wind.speed + " meters from " + weatherObj.wind.deg.toFixed(0) + " degrees";
					  if ( typeof(weatherObj.rain) == "object" ) {
						  tmpString += "<br><strong>Rainfall: </strong>";
						  Object.entries(weatherObj.rain).forEach(function(x) { tmpString += x[0] + ":  " + x[1] + " inches"						  })
					  }
					  if ( typeof(weatherObj.snow) == "object" ) {
						  tmpString += "<br><strong>Snow: </strong>";
						  Object.entries(weatherObj.snow).forEach(function(x) { tmpString += x[0] + ":  " + x[1] + " inches"						  })
					  }
					  document.getElementById("weather").innerHTML = tmpString;
				  }
			  })
			  req.send(null);
		})
}

console.log("pinSearch.js file is done");
