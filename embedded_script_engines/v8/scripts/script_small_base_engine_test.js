database.temp = 44
database.idx_oned_etv_ = 2
database.var_char = 33

/*
log("JS log: "+database.temp)
log("idx_oned_etv_ = " + database.idx_oned_etv_)
log("uchar = " + database.var_char)*/

database.ibRadioMode_=5
if (database.ibRadioMode_ === 5) {
	database.ibRadioMode_=6
}
//log(database.ibRadioMode_)

var time = 0
function Process() {
	log("time = " + time)
	if (time === 0) {
		database.ibRadioMode_ = 66;
	}
	time = time + 1;
}

log(database.ibRadioMode_);
//log("gel")