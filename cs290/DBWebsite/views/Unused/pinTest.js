console.log.bind(console)
console.log("PDK.js is starting");


function pinTest(){
	var pins = [];
	PDK.request('/boards/curiosityhacked/family-friendly-hackermakerspaces-for-kids-and-fam/pins/', function (response) { // Make sure to change the board_id
  	if (!response || response.error) {
    	alert('Error occurred');
  	} else {
    	pins = pins.concat(response.data);
    	if (response.hasNext) {
      	response.next(); // this will recursively go to this same callback
    	}
  	}
	});	
}

//PDK.me('boards', { fields: Const.PIN_FIELDS }, callback);


//pinTest();
