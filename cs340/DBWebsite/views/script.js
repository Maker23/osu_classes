/* ************************************************ */
function listAllTables(baseURL, item) {
	console.log("*** In clientListBooks");
	console.log ("    baseURL: ", baseURL);
	console.log ("    Item: ", item);
	//TODO, for debugging
}


/* ******************************************************* */
function createAuthorMenu(baseURL, elementList) {
	console.log("*** In clientListAuthors");
	console.log ("    elementList: ", elementList);


  // Send a query to the Database to list all authors
	var command = 'GetAuthorNames';
	var protocol = "http://";
	if (baseURL.port) { hostPort = protocol.concat(baseURL.hostname,':', baseURL.port); }
	else { hostPort = protocol.concat(baseURL.hostname); }
	var URL = hostPort.concat('/',command);
	console.log("URL=", URL);

	console.log("Opening get request with:", URL);

	// Open the connection and send the request
	var connection = new XMLHttpRequest();
	connection.open("GET", URL);
	connection.send(null);

	connection.addEventListener('load', function () {
		console.log("Request status:", connection.status);
		if ( connection.status < 400 ) {

			// https://stackoverflow.com/questions/8605516/default-select-option-as-blank
			var menuHTML = '<option selected value=""> -- choose an author or enter a new author below -- </option>'; 
			var menuElement = '';
			var response = JSON.parse(connection.responseText);
			console.log("Request returned:", connection.responseText);
			console.log("response is:", response);
  		// Parse the context; build an inner HTML
			for ( rownum in response.results ) {
				authorID = response.results[rownum].id;
				authorName = response.results[rownum].authorName;
				console.log("found author id:", authorID, "  name:", authorName);
				menuHTML = menuHTML.concat ('<option value="',authorID,'">',authorName,"</option>\n");
			}
			console.log("menuHTML is:", menuHTML);

			elementList.forEach( function (menuName) {
				menuElement = document.getElementById(menuName);
			  menuElement.innerHTML = menuHTML;
			});

  		// Foreach element in elementList: set innerHTML to that
			//document.getElementById('addBookForm').reset();
			return;
		}
		else {
			// This Should Never Happen (tm)
			console.log("Error in createAuthorMenu, ", connection.responseText);
			return undefined;
		}
	});
}

/* ******************************************************* */
function createBookMenu(baseURL, elementList) {
	console.log("*** In createBookMenu");
	console.log ("    baseURL: ", baseURL);
	console.log ("    elementList: ", elementList);


  // Send a query to the Database to list all book titles
	var command = 'GetBookTitles';
	var protocol = "http://";
	if (baseURL.port) { hostPort = protocol.concat(baseURL.hostname,':', baseURL.port); }
	else { hostPort = protocol.concat(baseURL.hostname); }
	var URL = hostPort.concat('/',command);
	console.log("URL=", URL);

	console.log("Opening get request with:", URL);

	// Open the connection and send the request
	var connection = new XMLHttpRequest();
	connection.open("GET", URL);
	connection.send(null);

	connection.addEventListener('load', function () {
		console.log("Request status:", connection.status);
		if ( connection.status < 400 ) {

			// https://stackoverflow.com/questions/8605516/default-select-option-as-blank
			var menuHTML = '<option selected value=""> -- choose a book -- </option>'; 
			var menuElement = '';
			var response = JSON.parse(connection.responseText);
			console.log("Request returned:", connection.responseText);
			console.log("response is:", response);
  		// Parse the context; build an inner HTML
			for ( rownum in response.results ) {
				bookID = response.results[rownum].id;
				bookTitle = response.results[rownum].title;
				console.log("found book id:", bookID, "  title:", bookTitle);
				menuHTML = menuHTML.concat ('<option value="',bookID,'">',bookTitle,"</option>\n");
			}
			console.log("menuHTML is:", menuHTML);

			elementList.forEach( function (menuName) {
				menuElement = document.getElementById(menuName);
			  menuElement.innerHTML = menuHTML;
			});

  		// Foreach element in elementList: set innerHTML to that
			//document.getElementById('addBookForm').reset();
			return;
		}
		else {
			// This Should Never Happen (tm)
			console.log("Error in createBookMenu, ", connection.responseText);
			return undefined;
		}
	});
}

/* ******************************************************* */
function createLocationMenu(baseURL, oid, elementList) {
	console.log("*** In createLocationMenu");
	console.log ("    baseURL: ", baseURL);
	console.log ("    oid: ", oid);
	console.log ("    elementList: ", elementList);

  // Send a query to the Database to list all book titles
	var command = 'GetLocations';
	command += '?' + 'oid=' + oid;
	var protocol = "http://";
	if (baseURL.port) { hostPort = protocol.concat(baseURL.hostname,':', baseURL.port); }
	else { hostPort = protocol.concat(baseURL.hostname); }
	var URL = hostPort.concat('/',command);
	console.log("URL=", URL);

	console.log("Opening get request with:", URL);

	// Open the connection and send the request
	var connection = new XMLHttpRequest();
	connection.open("GET", URL);
	connection.send(null);

	connection.addEventListener('load', function () {
		console.log("Request status:", connection.status);
		if ( connection.status < 400 ) {

			// https://stackoverflow.com/questions/8605516/default-select-option-as-blank
			var menuHTML = '<option selected value=""> -- choose a book event  -- </option>'; 
			var menuElement = '';
			var response = JSON.parse(connection.responseText);
			console.log("Request returned:", connection.responseText);
			console.log("response is:", response);
  		// Parse the context; build an inner HTML
			for ( rownum in response.results ) {
				momentID = response.results[rownum].mid;
				momentDescription = response.results[rownum].description;
				console.log("found moment id:", momentID, "  description:", momentDescription);
				menuHTML = menuHTML.concat ('<option value="',momentID,'">',momentDescription,"</option>\n");
			}
			console.log("menuHTML is:", menuHTML);

			elementList.forEach( function (menuName) {
				menuElement = document.getElementById(menuName);
			  menuElement.innerHTML = menuHTML;
			});

			return;
		}
		else {
			// This Should Never Happen (tm)
			console.log("Error in createLocationMenu, ", connection.responseText);
			return undefined;
		}
	});
}

/* ******************************************************* */
function createCharacterList(baseURL, mid, elementList) {
	console.log("*** In createCharacterList");
	console.log ("    baseURL: ", baseURL);
	console.log ("    mid: ", mid);
	console.log ("    elementList: ", elementList);

  // Send a query to the Database to list all book titles
	var command = 'GetCharacters';
	command += '?' + 'mid=' + mid;
	var protocol = "http://";
	if (baseURL.port) { hostPort = protocol.concat(baseURL.hostname,':', baseURL.port); }
	else { hostPort = protocol.concat(baseURL.hostname); }
	var URL = hostPort.concat('/',command);
	console.log("URL=", URL);

	console.log("Opening get request with:", URL);

	// Open the connection and send the request
	var connection = new XMLHttpRequest();
	connection.open("GET", URL);
	connection.send(null);

	connection.addEventListener('load', function () {
		console.log("Request status:", connection.status);
		if ( connection.status < 400 ) {
			var listHTML = '';
			var menuElement = '';
			var response = JSON.parse(connection.responseText);
			console.log("Request returned:", connection.responseText);
			console.log("response is:", response);
  		// Parse the context; build an inner HTML
			if ( response.results.length == 0 )
			{
				console.log("No characters returned by URL in createCharacterList");
			}
			else
			{
				listHTML = listHTML.concat ('<b>Characters already in this book event:</b>');
			}
			for ( rownum in response.results ) {
				characterID = response.results[rownum].characterID;
				characterName = response.results[rownum].characterName;
				console.log("found character id:", characterID, "  name:", characterName);
				listHTML = listHTML.concat ('<br>',characterName,'\n');
			}
			console.log("listHTML is:", listHTML);

			elementList.forEach( function (menuName) {
				menuElement = document.getElementById(menuName);
			  menuElement.innerHTML = listHTML;
			});

			return;
		}
		else {
			// This Should Never Happen (tm)
			console.log("Error in createCharacterList, ", connection.responseText);
			return undefined;
		}
	});
}

/* ******************************************************* */
function createCharacterMenu(baseURL, oid, mid, elementList) {
	console.log("*** In createCharacterMenu");
	console.log ("    baseURL: ", baseURL);
	console.log ("    oid: ", oid);
	console.log ("    mid: ", mid);
	console.log ("    elementList: ", elementList);

  // Send a query to the Database to list all book titles
	var command = 'GetCharacters';
	command += '?' + 'oid=' + oid;
	command += '&' + 'mid=' + mid;
	var protocol = "http://";
	if (baseURL.port) { hostPort = protocol.concat(baseURL.hostname,':', baseURL.port); }
	else { hostPort = protocol.concat(baseURL.hostname); }
	var URL = hostPort.concat('/',command);
	console.log("URL=", URL);

	console.log("Opening get request with:", URL);

	// Open the connection and send the request
	var connection = new XMLHttpRequest();
	connection.open("GET", URL);
	connection.send(null);

	connection.addEventListener('load', function () {
		console.log("Request status:", connection.status);
		if ( connection.status < 400 ) {
			// https://stackoverflow.com/questions/8605516/default-select-option-as-blank
			var menuHTML = '';
			var menuElement = '';
			var response = JSON.parse(connection.responseText);
			console.log("Request returned:", connection.responseText);
			console.log("response is:", response);
  		// Parse the context; build an inner HTML
			if ( response.results.length == 0 )
			{
				console.log("No characters returned by URL in createCharacterMenu");
			}
			else
			{
				menuHTML = menuHTML.concat('<select style="width:100%">'); 
				menuHTML = menuHTML.concat('<option selected value=""> -- choose a character or enter a new one below -- </option>'); 
			}
			
			for ( rownum in response.results ) {
				characterID = response.results[rownum].characterID;
				characterName = response.results[rownum].characterName;
				console.log("found character id:", characterID, "  name:", characterName);
				menuHTML = menuHTML.concat ('<option value="',characterID,'">',characterName,"</option>\n");
			}
			if ( response.results.length != 0 )
				{menuHTML = menuHTML.concat('</select>');}
			console.log("menuHTML is:", menuHTML);

			elementList.forEach( function (menuName) {
				menuElement = document.getElementById(menuName);
			  menuElement.innerHTML = menuHTML;
			});
			return;
		}
		else {
			// This Should Never Happen (tm)
			console.log("Error in createCharacterMenu, ", connection.responseText);
			return undefined;
		}
	});
}

/* ******************************************************* */
function clientAddBooks(baseURL, item) {
	console.log("*** In clientAddBooks");
	console.log ("    baseURL: ", baseURL);
	console.log ("    Item: ", item);
	// Expect:
	// title
	// authorMenuChoice
	// authorFname
	// authorLname
	// authorMnames
	// authorTitle
	// city
	// country
	if ( item.title == "" || ! item.title ) 
	{
		window.alert("Error: Book must have a title");
		return;
	}
	if ( item.authorMenuChoice != "" )
	{
		// Retrieve author name from the DB
	}
	else if (	( item.authorFname == "" || ! item.authorFname )
			||( item.authorLname == "" || ! item.authorLname ))
	{
		window.alert("Error: Book author must have a first AND last name");
		return;
	}
	if (	( item.city == "" || ! item.city )
			||( item.country == "" || ! item.country ))
	{
		window.alert("Error: Book must have a primary location, city and/or country");
		return;
	}

	var command = 'AddOneBook';
	var protocol = "http://";
	if (baseURL.port) { hostPort = protocol.concat(baseURL.hostname,':', baseURL.port); }
	else { hostPort = protocol.concat(baseURL.hostname); }
	var URL = hostPort.concat('/',command);
	console.log("URL=", URL);
	var connection = new XMLHttpRequest();
	var sendString = URL;
	var firstArg = true;
	// Construct the query string for the GET request
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

	// Open the connection and send the request
	connection.open("GET", sendString);
	connection.send(null);

	connection.addEventListener('load', function () {
		console.log("Request status:", connection.status);
		if ( connection.status < 400 ) {
			//Yay
			console.log("Request returned:", connection.responseText);
			console.log("Resetting form... supposedly");
			document.getElementById('addBookForm').reset();
			window.alert("'" + item.title + "' added successfully");
			return;
		}
		else {
			// Don't clear the form
			console.log("Error, ", connection.responseText);
			window.alert("Error, " + connection.responseText);
			return undefined;
		}
	});
}

/* ******************************************************* */
function clientAddLocation(baseURL, item) {
	console.log("*** In clientAddLocation");
	console.log ("    baseURL: ", baseURL);
	console.log ("    Item: ", item);
	// Expect:
	// bookMenuChoice
	// locationDescription
	// locationCountry
	// locationCity
	// locationStreet
	// locationAddress
	// TODO: ADD CHARACTERS!!!!
	if ( item.locationDescription == "" || ! item.locationDescription ) 
	{
		window.alert("Error: Location must have a description");
		return;
	}
	if ( item.bookMenuChoice == "" || ! item.bookMenuChoice )
	{
		window.alert("Error: Location must have a book");
		return;
	}
	if (	( item.locationCity == "" || ! item.locationCity )
			||( item.locationCountry == "" || ! item.locationCountry ))
	{
		window.alert("Error: Location must have a city and country");
		return;
	}

	var command = 'AddLocation';
	var protocol = "http://";
	if (baseURL.port) { hostPort = protocol.concat(baseURL.hostname,':', baseURL.port); }
	else { hostPort = protocol.concat(baseURL.hostname); }
	var URL = hostPort.concat('/',command);
	console.log("URL=", URL);
	var sendString = URL;
	var firstArg = true;
	// Construct the query string for the GET request
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

	// Open the connection and send the request
	var connection = new XMLHttpRequest();
	connection.open("GET", sendString);
	connection.send(null);

	connection.addEventListener('load', function () {
		console.log("Request status:", connection.status);
		if ( connection.status < 400 ) {
			//Yay
			console.log("Request returned:", connection.responseText);
			console.log("Resetting form... supposedly");
			document.getElementById('addBookForm').reset();
			window.alert("'" + item.title + "' added successfully");
			return;
		}
		else {
			// Don't clear the form
			console.log("Error, ", connection.responseText);
			window.alert("Error, " + connection.responseText);
			return undefined;
		}
	});
}

/* ******************************************************* */
function clientSearchBooks(baseURL, item) {
	console.log ("*** In clientSearchBooks");
	console.log ("    baseURL: ", baseURL);
	//console.log ("    elementID: ", elementID);
	console.log ("    Item: ", item);

	// Integrity check of the data
	if (	( item.title == "" || ! item.title )
			&&( item.author == "" || ! item.author )
			&&( item.location == "" || ! item.location )
			&&( item.description == "" || ! item.description )
			&&( item.character == "" || ! item.character ))
	{ 
		window.alert("Error: No search terms were entered. Enter at least one of Title, Author, Location, or Character. To view the entire database use 'List All Books'");
		return;
	}


	// Set up the connection to the server
	var command = 'SearchInBooks';
	if ( item.location != "" || item.location || item.description !="" || item.description) {
		item.db = 'litJoinTwo';
	}
	else {
		item.db = 'litJoinOne';
	}
	var protocol = "http://";
	if (baseURL.port) { hostPort = protocol.concat(baseURL.hostname,':', baseURL.port); }
	else { hostPort = protocol.concat(baseURL.hostname); }
	//var URL = hostPort.concat(baseURL.pathname, command);
	var URL = hostPort.concat('/',command);
	console.log("URL=", URL);
	var connection = new XMLHttpRequest();
	var sendString = URL;
	var firstArg = true;
	// Construct the query string for the GET request
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

	// Open the connection and send the request
	connection.open("GET", sendString);
	connection.send(null);
	
	// Parse the return information
	connection.addEventListener('load', function () {
		console.log("Request status:", connection.status);
		if ( connection.status < 400 ) {
			console.log("Request returned:", connection.responseText);
		
			var parentElement = document.getElementById('ResultsGoHere');

			// Get the new item ID from the database update
			var response = JSON.parse(connection.responseText);
			console.log ("Response: ", response)
			if ( response.results.length == 0) {
				parentElement.innerHTML = "<h2>No Search results found</h2>";
				return;
			}

			if (  ( item.db == 'litJoinOne' && ! response.results[0].bookID ) 
       	 || ( item.db == 'litJoinTwo' && ! response.results[0].momentID ))
			{
				window.alert ("Unknown database error:", connection.responseText);
				return;
			}
			/// TODO TURN this whole thing into a TABLE, then maybe with clickable text?
			//  Maybe have a 'create table' subroutine....
			//
			
			if ( item.db == 'litJoinOne' ){
				var ResultColumns = {
					'bookTitle':'Title',
					'authorName':'Author',
					'bookLocation':'Primary Location',
					'Characters':'Characters'
				};
			}
			else if ( item.db == 'litJoinTwo' ){
				var ResultColumns = {
					'bookLocation':'Location',
					'description':'Event Description',
					'bookTitle':'Book Title',
					'authorName':'Book Author',
					'Characters':'Characters appearing'
				};
			}

	
			parentElement.innerHTML = "<h2>Search results:<h2>";
			var table = document.createElement("table");	
			table.id = 'ResultsTable';
			parentElement.append(table);
			var cell = null; // declare a local variable
			var newRow = null;

			newRow = document.createElement("tr");
			Object.keys(ResultColumns).forEach(function(value,key)
			{
					cell = document.createElement("th");
					cell.className='borderth';
					cell.textContent = ResultColumns[value];
					newRow.append(cell);
			});
			table.append(newRow);

			console.log("response.results is:", response.results);
			response.results.forEach(function (line,index)
				{
					var newText="";
					console.log("In loop, item is:", line);
					console.log("line.bookTitle is:", line.bookTitle);
					// var dataRow = "dataRow" + line.id;
					newRow = document.createElement("tr");
					newRow.id = 'row'.concat(line.bookID); 

					Object.keys(ResultColumns).forEach(function(value,key)
					{
						cell = document.createElement("td");
						cell.className='bordertd';
						cell.textContent = line[value];
						newRow.append(cell);
					});
					
					//newText = newText.concat(line.title, line.genre, line.publication_date);
					//newRow.textContent = newText;
					console.log("Should have set text to:", newText);
					//parentElement.insertBefore(newRow,parentElement.childNodes[0]);
					table.append(newRow);
					document.getElementById(newRow.id).style.border="1px solid black";
				});
			return;	
		}
		else {
			console.log("Error, ", connection.responseText);
			return undefined;
		}
	});
}


/* ************************************************ */
function clientDeleteRow(baseURL, elementID, dbID) {
	
	console.log("*** In clientDeleteRow, elementID:", elementID, ", item.id:", dbID);
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


/* ************************************************ */
function clientUpdateRow(baseURL, elementID, item) {
	console.log("*** In clientUpdateRow, elementID:", elementID, ", item.id:", item.id);
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
	}

	for (key in newValues ) {
		//console.log ("key is", key, " value is", newValues[key]);
		newValues[key] = document.getElementById(newValues[key]).value;
		//console.log ("key is", key, " value is", newValues[key]);
	}
	var kilos = document.getElementById("kilosChecked"+ item.id).checked;
	if ( kilos == true ) {
		newValues['lbs'] = '0';
	}
	else {
		newValues['lbs'] = '1';
	}	
	console.log ("key is lbs value is", newValues['lbs']);

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

/* ************************************************ */
function clientGetItem(baseURL, elementID, dbID) {

	console.log("*** In clientGetItem, elementID:", elementID, ", dbID", dbID);
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
				'lbs':"lbs" + dbID
			}
		
			var newHtml = "";
			for (key in textfieldIDs) {
				newHtml += '<div class="col-sm-2" style="border-style:solid;border-width:thin" >' + itemData[key];

				if ( key == 'weight' ) {
					if ( itemData['lbs'] == 0 || itemData['lbs'] == 'false' ) {
						newHtml += ' kg';
					}
					else {
						newHtml += ' lbs';
					}
				}
				newHtml += '</div>\n';
			}
			kilosID = "kilosChecked" + dbID;
  		newHtml += '<input type="checkbox" name="kilos" value="1" id="' + kilosID + '" style="display:none" '
			if ( itemData['lbs'] == 0 || itemData['lbs'] == 'false' ) {
				newHtml += ' checked="checked" ';
			}
  		newHtml += '>';
			
			console.log("newHTML is:", newHtml);

			var dataRow = "dataRow" + dbID;
			var dataFields = "dataFields" + dbID;
			var dataButtons = "dataButtons" + dbID;
			console.log (dataFields, dataButtons);
			document.getElementById(dataFields).innerHTML = newHtml;

			var buttonDiv = document.getElementById(dataButtons);
			var buttonIDedit = "edit" + dbID;
			var buttonIDremove = "remove" + dbID;

			if ( buttonDiv === null ) {

				// If this is a new row, create new buttons and attach listeners
				newButtonDiv = document.createElement("div");
				newButtonDiv.id = dataButtons;
				newButtonDiv.className = "col-sm-4";
				parentDiv = document.getElementById (elementID);
				parentDiv.appendChild(newButtonDiv);

				editButton = document.createElement("button");
				editButton.id = buttonIDedit;
				editButton.name = "editButton";
				editButton.value = dbID;
				editButton.type = "button";
				editButton.textContent = "Edit";


				removeButton = document.createElement("button");
				removeButton.id = buttonIDremove;
				removeButton.name = "removeButton";
				removeButton.value = dbID;
				removeButton.textContent = "Delete";
				removeButton.style.marginLeft = "4px";

				newButtonDiv.appendChild(editButton);
				newButtonDiv.appendChild(removeButton);

				console.log(">>> Ataching click", dataRow, itemData);
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
				}
			else
			{
				//Not a new row?  OK, just
				//update the event handler with the new itemData
				var buttonIDedit = "edit" + dbID;
				var handlerID = "editHandler" + dbID;

				// Delete the editButton because we can't remove the eventListener
				// if the function is anonymous 
				// So drastic... found this bug right before deadline,
				// didn't have time to make it work another way :(
				var children = buttonDiv.childNodes;
				var removed=false;
				console.log("    Children = ", children);
				for ( var child of children)
				{
					if (child.type == "button" && child.id == buttonIDedit)
					{
						console.log("    Removing child button = ", child);
						buttonDiv.removeChild(child);
						removed=true;
					}
				}
				if (removed) {
					// Re-create and attach the edit button with the new itemData
				
					editButton = document.createElement("button");
					editButton.id = buttonIDedit;
					editButton.name = "editButton";
					editButton.value = dbID;
					editButton.type = "button";
					editButton.textContent = "Edit";
	
					buttonDiv.insertBefore(editButton,buttonDiv.childNodes[0]);
					
  				document.getElementById(buttonIDedit).addEventListener('click',
						clientEditRow.bind(
							null,
							baseURL,
							dataRow,
							itemData), false);
				}	
				// Make the buttons visible again
				buttonDiv.style.display = "inline";
			}
			return;
		}
		else{
			console.log("Error, ", connection.responseText);
			return undefined;
		}
	});
}

/* ************************************************ */
function clientEditRow(baseURL, elementID, item) {

	console.log("*** In client Edit Row");
	console.log("   baseURL:", baseURL);
	console.log("   elementID:", elementID);
	console.log("   item:", item);	 // This is an array of the row's key:value pairs

	// Store the current state of the html, for cancelling
	var dataFields = "dataFields" + item.id;
	var dataButtons = "dataButtons" + item.id;
	var currentHtml = document.getElementById(dataFields).innerHTML;

	// Get the DOM id's so we can query the current values
	var currentName = "name" + item.id;
	var currentReps = "reps" + item.id;
	var currentWeight = "weight" + item.id;
	var currentDate = "date" + item.id;

	// Create new DOM id's which will be the form field names
	var exerciseID = "exerciseEntered" + item.id;
	var repsID = "repsEntered" + item.id;
	var weightID = "weightEntered" + item.id;
	var dateID = "dateEntered" + item.id;
	var kilosID = "kilosChecked" + item.id;
	var formButtons = "formButtons" + item.id;

	// Build the form HTML
	var newHtml = "";
	newHtml += '<input class="col-sm-2" type="text" name="exercise" id=' + exerciseID + ' value="';
	newHtml += item.name + '">';
  newHtml += '<input class="col-sm-2" type="number" min="1" name="reps" id=' + repsID + ' value="';
	newHtml += item.reps + '">';
  newHtml += '<input class="col-sm-2" type="number" min="0" name="weight" id=' + weightID + ' value="';
	newHtml += item.weight + '">';
  newHtml += '<input class="col-sm-2" type="date" name="date" id=' + dateID + ' value="';
	newHtml += item.date + '">';
  newHtml += '</div><div class="col-sm-4" id="' + formButtons  +'" style="display:inline"><input type="checkbox" name="kilos" value="1" id=' + kilosID + ' style="margin-right:30px" '
	var kiloTruth = document.getElementById(kilosID).checked;
	if ( kiloTruth ){
		// If the weight is in kilograms, show the checkbox as 'checked'
		if ( kiloTruth == true ) {
			newHtml += ' checked="checked" ';
		}
	}
  newHtml += '>'

	// Add the two form-specific buttons
	var buttonIDupdate = "update" + item.id;
	var buttonIDcancel = "cancel" + item.id;
  newHtml += '<input type="button" id="'+ buttonIDupdate +'" name="update" value="Update">';
  newHtml += '<input type="button" id="'+ buttonIDcancel + '" name="cancel" value="Cancel">';

	// Replace the data line with the form line
	document.getElementById(dataFields).innerHTML = newHtml;
	// Hide the data buttons ("edit" and "delete") while the form is active
	document.getElementById(dataButtons).style.display = "none";

	// Event listeners for the form buttons
  document.getElementById(buttonIDupdate).addEventListener('click', function() {
    clientUpdateRow(baseURL, elementID, item)});
  document.getElementById(buttonIDcancel).addEventListener('click', function() {
    clientCancelEdit(baseURL, elementID, item, currentHtml)});
}

/* ************************************************ */
function clientCancelEdit(baseURL, elementID, item, currentHtml) {

	console.log("*** In clientCancelEdit");
	console.log("     elementID:", elementID, ", item.id:",  item.id);
	var dataFields = "dataFields" + item.id;
	var dataButtons = "dataButtons" + item.id;
	var formButtons = "formButtons" + item.id;

	// Just swap back the original data row, make the data buttons
	// visible again, hide the form buttons
	document.getElementById(dataFields).innerHTML = currentHtml;
	document.getElementById(dataButtons).style.display = "inline";
	if ( document.getElementById(formButtons) ) {
		document.getElementById(formButtons).style.display = "none";
	}
}
