console.log.bind(console)
console.log("Homework assignment: AJAX Interactions")
console.log("CS290-400-W14  abrasss@  Feb 19, 2017")
console.log("File script.js is starting");


document.addEventListener('DOMContentLoaded', attachForms)

function attachForms(){
	attachWeather();
	attachHttpBin();
}
function attachWeather(){
	document.getElementById('dataSubmit').addEventListener('click',
		function getWeather(event){
			  event.preventDefault();
			  var weatherLocation = document.getElementById('locationEntered').value;
			  document.getElementById("location").textContent = "Weather for " + weatherLocation;
			  
			  var URL = "http://api.openweathermap.org/data/2.5/weather";
			  var appID = "fa7d80c48643dfadde2cced1b1be6ca1" // real
			  var sendString = URL + "?q=" + weatherLocation + "&appid=" + appID;
			  
			  var req = new XMLHttpRequest();
			  req.open("GET", sendString);
			  
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
					  document.getElementById("location").textContent = "Weather for " + weatherObj.name + " at " + currentTime;
					  
					  var tmpString = "<p>"
					  var tempF = ((weatherObj.main.temp * 9 / 5) - 459.67).toFixed(1);
					  tmpString += "<br><strong>Temp: </strong>" + tempF + " F";
					  tmpString += "<br><strong>Weather:  </strong>" + weatherObj.weather[0].description;
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

function attachHttpBin(){
	document.getElementById('httpBinSubmit').addEventListener('click',
		function getFormData(event){
			event.preventDefault();
			document.getElementById("httpBinResponse").innerHTML = ""; // reset in case of previous errors

			var page = new XMLHttpRequest();
			var formData = {nameText:null, radio1:null};
			formData.nameText = document.getElementById('nameText').value;
			if (document.querySelector('input[name="radio1"]:checked')) {
				// thank you stack overflow! parsing radio buttons correctly is hard
				formData.radio1 = document.querySelector('input[name="radio1"]:checked').value; 
			}
			else {
				document.getElementById("httpBinResponse").innerHTML = "<strong>FORM ERROR:</strong> You must select your favorite color";
				return; // No form data for you
			}
			page.open("POST", "https://www.httpbin.org/post");
			page.setRequestHeader("Content-Type", "application/json")
			page.addEventListener('load', function() {
				  console.log("Status:", page.status)
				  if (page.status < 100 || page.status >= 400 ){
					  console.log ("Web request failed with error: ", page.statusText)
				  }
				  else {
					  console.log (page.responseText);
					  document.getElementById("httpBinResponse").innerHTML = "<h3>httpbin returns:</h3><pre>" + JSON.stringify(JSON.parse(page.responseText),null,2) + "</pre>";
				  }
			});
			var myObj = JSON.stringify(formData); // for debugging
			page.send(JSON.stringify(formData));
		})
}
console.log("File script.js complete")
