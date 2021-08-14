function getRandomizer(bottom, top) {
    return function () {
        return Math.floor(Math.random() * (1 + top - bottom)) + bottom;
    }
}

//delay function
function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

async function getRealTimeValue() {
	var rollpulse = getRandomizer(60,100);
	var rollsp02= getRandomizer(80, 100);
	

    for (var i = 0; i < 1000; i++) {
        let newtemp = {
            pulse: rollpulse(),
			Sp02:rollsp02()
        }
        console.log(newtemp);

        firebase.database().ref().update(newtemp);
        await sleep(2000);

    }
}
//call the defined function for temperature
getRealTimeValue();

