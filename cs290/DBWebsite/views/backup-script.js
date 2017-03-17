function newGetData(tableID, currentRow) {
	  console.log("inside newGetData function);
}
//console.log.bind(console)
//console.log("Homework assignment: AJAX Interactions")
//console.log("CS290-400-W14	abrasss@	Feb 19, 2017")
//console.log("File script.js is starting");


/*
function newDeleteRow(tableID, currentRow) {
	  console.log("inside newDeleteRow function);
    try {
        var table = document.getElementById(tableID);
        var rowCount = table.rows.length;
        for (var i = 0; i < rowCount; i++) {
            var row = table.rows[i];
            
            if (row==currentRow.parentNode.parentNode) {
                if (rowCount <= 1) {
                    alert("Cannot delete all the rows.");
                    break;
                }
                table.deleteRow(i);
                rowCount--;
                i--;
            }
        }
    } catch (e) {
        alert(e);
    }
    //getValues();
    //}
}
*/


/*
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
						tmpString += "<br><strong>Weather:	</strong>" + weatherObj.weather[0].description;
						if ( typeof(weatherObj.clouds) == "object" ) {
							tmpString += "<br><strong>Cloud cover: </strong>";
							Object.entries(weatherObj.clouds).forEach(function(x) { tmpString += x[1] + " percent"							})
						}
						tmpString += "<br><strong>Wind:</strong> speed " + weatherObj.wind.speed + " meters from " + weatherObj.wind.deg.toFixed(0) + " degrees";
						if ( typeof(weatherObj.rain) == "object" ) {
							tmpString += "<br><strong>Rainfall: </strong>";
							Object.entries(weatherObj.rain).forEach(function(x) { tmpString += x[0] + ":	" + x[1] + " inches"							})
						}
						if ( typeof(weatherObj.snow) == "object" ) {
							tmpString += "<br><strong>Snow: </strong>";
							Object.entries(weatherObj.snow).forEach(function(x) { tmpString += x[0] + ":	" + x[1] + " inches"							})
						}
						document.getElementById("weather").innerHTML = tmpString;
					}
				})
				req.send(null);
		})
}

*/
