function clientAddExercise(baseURL, elementID, item) {
	console.log ("In clientAddExercise");
	console.log ("elementID: ", elementID);
	console.log ("Item: ", item);

	if ( item.name == "" || ! item.name ) { 
		window.alert("Error: Exercise name cannot be empty");
		return;
	}
	if ( Number(item.reps) < 1 ) { 
		window.alert("Error: Exercise reps must be 1 or greater");
		return;
	}
	if ( item.weight == "" ||  Number(item.weight) < 0 ) { 
		window.alert("Error: Exercise weight must be 0 or greater");
		return;
	}
	if ( item.date == "" || ! item.date ) { 
		window.alert("Error: Exercise date must be set");
		return;
	}
	if ( item.kilos == false ) { item['lbs'] = 1; }
	else{ item['lbs'] = 0; }
	delete item.kilos;


	// Set up and open a connection to the server
	var command = 'addExercise';
	var protocol = "http://";
	if (baseURL.port) { hostPort = protocol.concat(baseURL.hostname,':', baseURL.port); }
	else { hostPort = protocol.concat(baseURL.hostname); }
	var URL = hostPort.concat(baseURL.pathname, command);
	console.log("URL=", URL);
	var connection = new XMLHttpRequest();
	var sendString = URL;
	var firstArg = true;
	for ( key in item ) {
		if ( ! firstArg ) {
			sendString += "&";
		}
		else {
			sendString += "?";
			firstArg = false;
		}
		sendString += key + '=' + item[key];
	}
	console.log("Opening get request with:", sendString);
	connection.open("GET", sendString);
	connection.send(null);
	connection.addEventListener('load', function () {
		console.log("Request status:", connection.status);
		if ( connection.status < 400 ) {
			console.log("Request returned:", connection.responseText);
			var response = JSON.parse(connection.responseText);
			if ( ! response.insertId ){
				window.alert ("Unknown database error:", connection.responseText);
				return;
			}
			// Retrieve the row we just updated
			// TODO: Get back the new item ID from the database update
			// Create a new HTML element with that iD, and prepend it
			// to currentHTML.  Then call clientGetItem to set the innerHTML
			// for that new element
			
			var dataRow = "dataRow" + response.insertId;
			// Store the existing data so we can add to it.
			//var newHtml = '<div class="row" id="'  + dataRow + '"> </div>';
			//newHtml += currentHtml;
			newRow = document.createElement("div");
			newRow.id = dataRow;
			newRow.className = "row";
			var historyList = document.getElementById(elementID);
			historyList.insertBefore(newRow,historyList.childNodes[0]);
			//document.getElementById(elementID).innerHTML = newHtml;
			clientGetItem(baseURL, dataRow, response.insertId);
			document.getElementById('entryForm').reset();
			return;	
		}
		else {
			console.log("Error, ", connection.responseText);
			return undefined;
		}
	});

}

/* ************************************************************* */

function clientDeleteRow(baseURL, elementID, dbID) {
	var protocol = "http://";
	var command = 'delete';
	if (baseURL.port) { hostPort = protocol.concat(baseURL.hostname,':', baseURL.port); }
	else { hostPort = protocol.concat(baseURL.hostname); }
	var URL = hostPort.concat(baseURL.pathname, command);
	console.log("URL=", URL);

	var connection = new XMLHttpRequest();
	var sendString = URL;
	sendString += "?" + 'id=' + dbID;
	console.log("Opening get request with:", sendString);
	connection.open("GET", sendString);
	connection.send(null);
	connection.addEventListener('load', function () {
		console.log("Request status:", connection.status);
		if ( connection.status < 400 ) {
			console.log("Reponse Text is:", connection.responseText);
			document.getElementById(elementID).innerHTML = "";
		}
		else {
			console.log("Error, ", connection.responseText);
			return undefined;
		}
	});
}

function clientUpdateRow(baseURL, elementID, item) {
	console.log("Unbelievably - in clientUpdateRow");
	var protocol = "http://";
	var command = 'update';
	if (baseURL.port) { hostPort = protocol.concat(baseURL.hostname,':', baseURL.port); }
	else { hostPort = protocol.concat(baseURL.hostname); }
	var URL = hostPort.concat(baseURL.pathname, command);
	console.log("URL=", URL);
	var connection = new XMLHttpRequest();
	var sendString = URL;
	var firstArg = true;

	/*
	var exerciseID = "exerciseEntered" + item.id;
	var repsID = "repsEntered" + item.id;
	var weightID = "weightEntered" + item.id;
	var dateID = "dateEntered" + item.id;
	var kilosID = "kilosChecked" + item.id;
	*/
	var	newValues = {
		'name':"exerciseEntered" + item.id,
		'reps':"repsEntered" + item.id,
		'weight':"weightEntered" + item.id,
		'date':"dateEntered" + item.id,
		'kilos':"kilosChecked" + item.id
	}

	for (key in newValues ) {
		console.log ("key is", key, " value is", newValues[key]);
		newValues[key] = document.getElementById(newValues[key]).value;
		console.log ("key is", key, " value is", newValues[key]);
	}

	for ( key in item ) {
		if ( ! firstArg ) {
			sendString += "&";
		}
		else {
			sendString += "?";
			firstArg = false;
		}
		if (newValues[key]) {
			sendString += key + '=' + newValues[key];
		}
		else {
			sendString += key + '=' + item[key];
		}
	}

	// Now open the connection and send the request to update the datbase
	// using the new values from the page's input boxes
	console.log("Opening get request with:", sendString);
	connection.open("GET", sendString);
	connection.send(null);
	connection.addEventListener('load', function () {
		console.log("Request status:", connection.status);
		if ( connection.status < 400 ) {
			// Retrieve the row we just updated
			clientGetItem(baseURL, elementID, item.id);
			return;	
		}
		else {
			console.log("Error, ", connection.responseText);
			return undefined;
		}
	});
	
}

function clientGetItem(baseURL, elementID, dbID)
{
	URL = hostPort.concat(baseURL.pathname, 'getitem');
	sendString = URL + '?' + 'id=' + dbID;
	console.log("Opening get request with:", sendString);
	var connection = new XMLHttpRequest();
	connection.open("GET", sendString);
	connection.send(null);
	connection.addEventListener('load', function () {
		console.log ("GetItem connection returned");
		if ( connection.status < 400 ) {
			console.log("Response Text is:", connection.responseText);
	
			itemData = JSON.parse(connection.responseText)[0];
			console.log("Data is:", itemData);

			var	textfieldIDs = {
				'name':"exerciseEntered" + dbID,
				'reps':"repsEntered" + dbID,
				'weight':"weightEntered" + dbID,
				'date':"dateEntered" + dbID,
			}
			var radioIDs = {
				'lbs':"kilosChecked" + dbID
			}
		
			var newHtml = "";
			for (key in textfieldIDs) {
				newHtml += '<div class="col-sm-2" style="border-style:solid;border-width:thin" >' + itemData[key];

				if ( key == 'weight' ) {
					if ( radioIDs['lbs'] ) {
						if ( radioIDs['lbs'] == 0 || radioIDs['lbs'] == 'false' ) {
							newHtml += ' kg';
						}
						else {
							newHtml += ' lbs';
						}
					}
				}
				newHtml += '</div>\n';
			}
			console.log("newHTML is:", newHtml);
			var buttonIDedit = "edit" + dbID;
			var buttonIDremove = "remove" + dbID;
			var dataRow = "dataRow" + dbID;
			newHtml += '<div class="col-sm-4">';
		  newHtml += '<input type="hidden" name=rowKey value="' + dataRow + '">\n';
      newHtml += '<button type="button" id="' + buttonIDedit + '" name="editButton" value=' + dbID +'>Edit</button>\n';
      newHtml += '<button type="button" id="' + buttonIDremove + '" name="removeButton" value=' + dbID + '>Delete</button>\n';
			newHtml += '</div>';

			document.getElementById(elementID).innerHTML = newHtml;
  		document.getElementById(buttonIDedit).addEventListener('click', function() {
				clientEditRow(
					baseURL,
					dataRow,
					itemData)}, false);

  		document.getElementById(buttonIDremove).addEventListener('click', function() {
    		clientDeleteRow(
      		baseURL,
      		dataRow,
					dbID)}, false);

			return;
		}
		else{
		
			console.log("Error, ", connection.responseText);
			return undefined;
		}
	});
}

function clientEditRow(baseURL, elementID, item) {
	console.log("In client Edit Row");
	console.log("baseURL:", baseURL);
	console.log("elementID:", elementID);
	console.log("item:", item);	 // This is an array of the row's key:value pairs

	// Store the current state of the html, for cancelling
	var currentHtml = document.getElementById(elementID).innerHTML;

	var exerciseID = "exerciseEntered" + item.id;
	var repsID = "repsEntered" + item.id;
	var weightID = "weightEntered" + item.id;
	var dateID = "dateEntered" + item.id;
	var kilosID = "kilosChecked" + item.id;


	var newHtml = "";
	newHtml += '<input class="col-sm-2" type="text" name="exercise" id=' + exerciseID + ' value="';
	newHtml += item.name + '">';
  newHtml += '<input class="col-sm-2" type="number" min="1" name="reps" id=' + repsID + ' value="';
	newHtml += item.reps + '">';
  newHtml += '<input class="col-sm-2" type="number" min="0" name="weight" id=' + weightID + ' value="';
	newHtml += item.weight + '">';
  newHtml += '<input class="col-sm-2" type="date" name="date" id=' + dateID + ' value="';
	newHtml += item.date + '">';
  newHtml += '<div class="col-sm-4"><input type="radio" name="kilos" value="1" id=' + kilosID + ' style="margin-right:30px" '
	if ( item.lbs != 1 && item.lbs != 'true' ) {
		newHtml += ' checked="checked" ';
	}
  newHtml += '>'

	var buttonIDupdate = "update" + item.id;
	var buttonIDcancel = "cancel" + item.id;
  newHtml += '<input type="button" id="'+ buttonIDupdate +'" name="update" value="Update">';
  newHtml += '<input type="button" id="'+ buttonIDcancel + '" name="update" value="Cancel">';

	document.getElementById(elementID).innerHTML = newHtml;
  document.getElementById(buttonIDupdate).addEventListener('click', function() {
    clientUpdateRow(location, elementID, item)});
  document.getElementById(buttonIDcancel).addEventListener('click', function() {
    clientCancelEdit(location, elementID, item, currentHtml)});
	
}

function clientCancelEdit(baseURL, elementID, item, currentHtml) {
	document.getElementById(elementID).innerHTML = currentHtml;
	// Need to reattach listeners here... sigh
	var buttonIDedit = "edit" + item.id;
	var buttonIDremove = "remove" + item.id;
	var dataRow = "dataRow" + item.id;
  document.getElementById(buttonIDedit).addEventListener('click', function() {
		clientEditRow(
			location,
			dataRow,
			item)}, false);

  document.getElementById(buttonIDremove).addEventListener('click', function() {
    clientDeleteRow(
      location,
      dataRow,
			item.id)}, false);

}


function sendCommand (path, params) {
	
	var connection = new XMLHttpRequest();
	var sendString = path;
	sendString += "?";
	var firstArg = true;

	for (key in params) {
		if (params.hasOwnProperty(key)) {
			if ( ! firstArg ) {
				sendString += "&";
			}
			else {
				firstArg = false;
			}
			sendString += "" + key + "=" + params[key];
		}
	}

	console.log("Opening get request with:", sendString);
	connection.open("GET", sendString);
	connection.send(null);
	connection.addEventListener('load', function () {
		console.log("Request status:", connection.status);
		if ( connection.status < 400 )
			return connection.responseText;
		else
			return undefined;
	});
}
