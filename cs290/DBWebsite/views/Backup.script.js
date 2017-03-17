function clientEditRow(baseURL, elementID, dbID) {
	  console.log("inside clientEditRow function, variables:", elementID, ",",dbID);
		
		var hostPort = "http://";
		if (baseURL.port) { hostPort = baseURL.hostname.concat(':', baseURL.port); }
		else { hostPort = baseURL.hostname; }
		var URL = hostPort.concat(baseURL.pathname);
		console.log(URL);

		var cmdResponseText =  sendCommand(URL+ "edit",{id:dbID});
		
}

function clientModifyRow(command,baseURL, elementID, dbID) {
	if ( ! (command == "edit" || command == "delete" )) {
		console.log ("Bad command:", command);
		return;
	}	
	var protocol = "http://";
	if (baseURL.port) { hostPort = protocol.concat(baseURL.hostname,':', baseURL.port); }
	else { hostPort = protocol.concat(baseURL.hostname); }
	var URL = hostPort.concat(baseURL.pathname);
	console.log(URL);

	var cmdResponseText = sendCommand(URL + command,{id:dbID});
		
	console.log("Reponse Text is:", cmdResponseText);
}


function clientDeleteRow(baseURL, elementID, dbID) {
	  console.log("inside clientDeleteRow function, variables:", baseURL, elementID,",", dbID);

		var protocol = "http://";
		if (baseURL.port) { hostPort = protocol.concat(baseURL.hostname,':', baseURL.port); }
		else { hostPort = protocol.concat(baseURL.hostname); }
		var URL = hostPort.concat(baseURL.pathname);
		console.log(URL);

		sendCommand(URL+ "delete",{id:dbID});
		
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
	connection.open("GET", sendString,true);
	connection.send(null);
	connection.addEventListener('load', function () {
		console.log("Request status:", connection.status);
		if ( connection.status < 400 )
			return connection.responseText;
		else
			return undefined;
	});
}
