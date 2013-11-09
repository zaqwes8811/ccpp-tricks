function Process() {
	var that = this;
	for (var key in that) {
		log(key);
	}
	
	log(that.options.toString());
	
	log("MSG: Show options");
	
	for (var fields in that.options) {
		log(fields);
	}
}