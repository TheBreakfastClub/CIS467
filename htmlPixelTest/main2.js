var selectedPixel = {};
var selectedColor = 0;
var selectedHue = 0;
var smallArray = [];
var bigArray = [];
var colorArray = [];
var maxVal = 32;
var pixelAlg = avgColors;

for (var j = 0; j < maxVal; j++) {
	colorArray[j] = [];
    for (var i = 0; i < maxVal; i++) {
    	colorArray[j][i] = Math.random() *100;
	};
};


$( document ).ready(function() {
    var gridNum = maxVal;

    for (var j = 0; j < gridNum; j++) {
    	smallArray[j] = [];
	    for (var i = 0; i < gridNum; i++) {
			smallArray[j][i] = makeShiftPixel(j, i, gridNum);
		};
	};

	for (var j = 0; j < gridNum; j++) {
    	bigArray[j] = [];
	    for (var i = 0; i < gridNum; i++) {
			bigArray[j][i] = makeColorPixel(j, i);
		};
	};

	var radios = $("input:radio[name=res]");
	for(var i = 0, max = radios.length; i < max; i++) {
	    radios[i].onclick = function() {
	        changeRes(this.value);
	    };
	}

	var radios = $("input:radio[name=alg]");
	for(var i = 0, max = radios.length; i < max; i++) {
	    radios[i].onclick = function() {
	        changeAlg(this.value);
	    };
	}
});

function changeAlg(value) {
	if (value == 1) {
		pixelAlg = avgColors;
	} else if (value == 2) {
		pixelAlg = maxColors;
	} else {
		pixelAlg = minColors;
	}
}

function selectHue() {
    selectedHue = parseInt(document.getElementById("myHue").value);
    for (var j = 0; j < smallArray.length; j++) {
	    for (var i = 0; i < smallArray[j].length; i++) {
			smallArray[j][i].changeHue();
		};
	};

    for (var j = 0; j < bigArray.length; j++) {
	    for (var i = 0; i < bigArray[j].length; i++) {
			bigArray[j][i].changeColor(bigArray[j][i]['color']);
		};
	};
}

function selectShade() {
    selectedColor = parseInt(document.getElementById("myColor").value);
}

function selectedColor () {
	selectedColor = parseInt($("#myColor").val());
};

function mixColors (x, y, num) {
	return pixelAlg(x, y, num);
}

function avgColors (x, y, num) {
	console.log("avg");
	var newColor = 0;

	for (var j = 0; j < num; j++) {

	    for (var i = 0; i < num; i++) {
	    	newColor = newColor + colorArray[(x*num)+j][(y*num)+i];
		};
	};

	// newColor = newColor/(num*num);
	newColor = Math.round(newColor/(num*num));
	return newColor;
};

function maxColors (x, y, num) {
	console.log("max");

	var newColor = 0;

	for (var j = 0; j < num; j++) {

	    for (var i = 0; i < num; i++) {
	    	if (colorArray[(x*num)+j][(y*num)+i] > newColor) {
	    		newColor = colorArray[(x*num)+j][(y*num)+i];
	    	}
		};
	};

	return newColor;
}

function minColors (x, y, num) {
	console.log("min");

	var newColor = 100;

	for (var j = 0; j < num; j++) {

	    for (var i = 0; i < num; i++) {
	    	if (colorArray[(x*num)+j][(y*num)+i] < newColor) {
	    		newColor = colorArray[(x*num)+j][(y*num)+i];
	    	}
		};
	};

	return newColor;
}

function changeRes(val) {
	var box = $(".pixalSmallx");

	box.empty();

	for (var j = 0; j < val; j++) {
	    for (var i = 0; i < val; i++) {
			makeShiftPixel(j, i, val);
		};
	};
};

function printArray() {
	// $("p.printout").empty();
	// var print = "["

	// for (var j = 0; j < maxVal; j++) {
	// 	print = print + "[";
	//     for (var i = 0; i < maxVal; i++) {
	// 		if (i != 0) {
	// 			print = print + ",";
	// 		}
	// 		print = print + colorArray[j][i];
	// 	};
	// 	print = print + "]";
	// };
	// print = print + "]";

	// $("p.printout").text(print);
}



function makeShiftPixel (x, y, size) {
	var pixel = {};	

	pixel.value = mixColors(x, y, maxVal / size);
	pixel.pix = $('<div/>')
    	.addClass("singlePixel" + size)
    	.css("background-color", "hsl("+selectedHue+", 100%, "+pixel.value+"%)");

	$(".pixalSmallx").append(pixel.pix);

	pixel.changeShade = function (value) {
		pixel.value = value;
		pixel.pix.css("background-color", "hsl("+selectedHue+", 100%, "+value+"%)");
	};

	pixel.changeHue = function () {
		pixel.pix.css("background-color", "hsl("+selectedHue+", 100%, "+pixel.value+"%)");
	};

	return pixel;
};

function makeColorPixel (x, y) {
	var pixel = {};

	pixel.pix = $('<div/>')
    	.addClass("singlePixel" + maxVal);

	$(".pixalBigx").append(pixel.pix);

	pixel.changeColor = function (value) {
		pixel['color'] = value;
		pixel.pix.css("background-color", "hsl("+selectedHue+", 100%, "+value+"%)");
		smallArray[x][y].changeShade(value);
		colorArray[x][y] = value;
	};


	pixel.pix.click(function(e) {
		selectedPixel = pixel;
		$(".selected").toggleClass("selected", false);
		pixel.pix.toggleClass("selected", true);
		pixel.changeColor(selectedColor);
		printArray();

		// var print_area = $("#printout");
		// var print_string = "";
		// for (var j = 0; j < maxVal; j++) {
		// 	print_string += "['"+j+"' => "
		//     for (var i = 0; i < maxVal; i++) {
		//     	print_string += "{" + colorArray[j][i].toString() + "} ";
		// 	};
		// 	print_string += " *]"
		// };
	});

	pixel.changeColor(colorArray[x][y]);

	return pixel;
};