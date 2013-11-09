function Process() {
	log("hello");
	var that = this;
	for (var key in that) {
		log(key);
	}
}