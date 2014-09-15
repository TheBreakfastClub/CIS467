var selectedPixel = {};
var selectedColor = "";
var colors = [];

var maxVal = 32;

for (var j = 0; j < maxVal; j++) {
	colors[j] = [];
    for (var i = 0; i < maxVal; i++) {
    	colors[j][i] = 97;
	};
};


function avgColors (x, y, num) {      

	var newColor = [0,0,0];

	for (var j = 0; j < num; j++) {    

	    for (var i = 0; i < num; i++) {
	    	newColor[0] = newColor[0] + colors[(x*num)+j][(y*num)+i][0];
	    	newColor[1] = newColor[1] + colors[(x*num)+j][(y*num)+i][1];
	    	newColor[2] = newColor[2] + colors[(x*num)+j][(y*num)+i][2];
		};
	};

	newColor[0] = Math.round(newColor[0]/(num*num)*8)/8;
	newColor[1] = Math.round(newColor[1]/(num*num)*8)/8;
	newColor[2] = Math.round(newColor[2]/(num*num)*8)/8;

	return newColor;
};

function makeBigPixel (x, y, hue, shade) {
	var pixel = {};

	pixel['x'] = x;
	pixel['y'] = y;
	pixel['color'] = "123456";

	pixel.pix = $('<div/>')
    	.addClass("singlePixel" + size);


	$(".pixalSmallx").append(pixel.pix);

	pixel.changeColor = function (value) {
		pixel['color'] = value;
		pixel.pix.css("background-color", value);
		// pixel.pix.css("background-color", "rgb("+(value[0]*256)+","+(value[1]*256)+","+(value[2]*256)+")");
		colors[x][y] = value;
	};



	pixel.setColor = function () {
		var value = avgColors(x, y, maxVal / size);
		pixel.pix.css("background-color", "rgb("+(value[0]*256)+","+(value[1]*256)+","+(value[2]*256)+")");
	};

	pixel.pix.click(function(e) {
		selectedPixel = pixel;
		$(".selected").toggleClass("selected", false);
		pixel.pix.toggleClass("selected", true);
		pixel.changeColor(selectedColor);

		// var print_area = $("#printout");
		// var print_string = "";
		// for (var j = 0; j < maxVal; j++) {
		// 	print_string += "['"+j+"' => "
		//     for (var i = 0; i < maxVal; i++) {
		//     	print_string += "{" + colors[j][i].toString() + "} ";
		// 	};
		// 	print_string += " *]"
		// };
		// console.log(print_string);
	})

	nums = colors[x][y];
	pixel.setColor();

	return pixel;
}

function makeSmallPixel (x, y, size) {
	var pixel = {};

	pixel['x'] = x;
	pixel['y'] = y;
	pixel['color'] = "123456";

	pixel.pix = $('<div/>')
    	.addClass("singlePixel" + size);


	$(".pixalSmallx").append(pixel.pix);

	pixel.changeColor = function (value) {
		pixel['color'] = value;
		pixel.pix.css("background-color", value);
		// pixel.pix.css("background-color", "rgb("+(value[0]*256)+","+(value[1]*256)+","+(value[2]*256)+")");
		colors[x][y] = value;
	};



	pixel.setColor = function () {
		var value = avgColors(x, y, maxVal / size);
		pixel.pix.css("background-color", "rgb("+(value[0]*256)+","+(value[1]*256)+","+(value[2]*256)+")");
	};

	// pixel.pix.click(function(e) {
	// 	selectedPixel = pixel;
	// 	$(".selected").toggleClass("selected", false);
	// 	pixel.pix.toggleClass("selected", true);
	// 	pixel.changeColor(selectedColor);

	// 	var print_area = $("#printout");
	// 	var print_string = "";
	// 	for (var j = 0; j < maxVal; j++) {
	// 		print_string += "['"+j+"' => "
	// 	    for (var i = 0; i < maxVal; i++) {
	// 	    	print_string += "{" + colors[j][i].toString() + "} ";
	// 		};
	// 		print_string += " *]"
	// 	};
	// 	console.log(print_string);
	// })

	nums = colors[x][y];
	pixel.setColor();

	return pixel;
}

function makeColor (hue, shade) {
	var colour = {};

	colour.col = $('<div/>').addClass("colorBox"+hue+shade).text("" + (100 - (shade * 100/8) - 3) + "%");

	$('#printout').append(colour.col);

	colour.getColor = function () {
		return "hsl(" + hue + ", 100%, " + (100 - (shade * 100/8) - 3) + "%)";
	};

	colour.col.click(function(e) {
		selectedColor = colour.getColor();
	})

	return colour;
}



function changeColor(input) {
	selectedColor = [Math.round((input.rgb[0]*8))/8, Math.round((input.rgb[1]*8))/8, Math.round((input.rgb[2]*8))/8];
}

function changeRes(val) {
	var box = $(".pixalSmallx");

	box.empty();

	for (var j = 0; j < val; j++) {
	    for (var i = 0; i < val; i++) {
			makeSmallPixel(j, i, val);
		};
	};

};

var hues = [0, 45, 85, 120, 145, 185, 210, 235, 260, 295, 315, 340];
var shades = [0, 1, 2, 3, 4, 5, 6]

$( document ).ready(function() {
    // console.log( "ready!" );
    var gridNum = 1;
    for (var j = 0; j < gridNum; j++) {
	    for (var i = 0; i < gridNum; i++) {
			makeSmallPixel(j, i, gridNum);    
		};
	};

	for (var j = 0; j < hues.length; j++) {
		$("#printout").append($('<p/>').text("Color: " + hues[j]));
	    for (var i = 0; i < shades.length; i++) {
	    	// $("#printout").append($('<div/>').addClass("colorBox"+hues[j]+shades[i]));
	    	makeColor(hues[j], shades[i]);
		};
		$("#printout").append($('<br/>'));
	};

	var radios = $("input:radio[name=res]");
	for(var i = 0, max = radios.length; i < max; i++) {
	    radios[i].onclick = function() {
	        changeRes(this.value)
	    }
	}
});
         