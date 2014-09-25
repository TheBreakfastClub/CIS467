

var selectedPixel = {};
var selectedColor = [255,255,255];
var selectedHue = 0;
var smallArray = [];
var bigArray = [];
var maxVal = 32;
var opacity = 1;
var solidity = 1;

$( document ).ready(function() {
    var gridNum = maxVal;
    convertOld();

    for (var a = 0; a < gridNum; a++) {
        smallArray[a] = [];
        for (var b = 0; b < gridNum; b++) {
            smallArray[a][b] = makeShiftPixel(a, b, gridNum);
        }
    }

    for (var c = 0; c < gridNum; c++) {
        bigArray[c] = [];
        for (var d = 0; d < gridNum; d++) {
            bigArray[c][d] = makeColorPixel(c, d);
        }
    }

    var radios1 = $("input:radio[name=res]");
    var max = radios1.length;
    for(var e = 0; e < max; e++) {
        radios1[e].onclick = function() {
            changeRes(this.value);
        }
    }

    var radios2 = $("input:radio[name=alg]");
    max = radios2.length;
    for(var f = 0; f < max; f++) {
        radios2[f].onclick = function() {
            changeAlg(this.value);
        }
    }

    var radios3 = $("input:radio[name=solid]");
    max = radios3.length;
    for(f = 0; f < max; f++) {
        radios3[f].onclick = function() {
            changeSolid(this.value);
        }
    }


    makeCurrentColor(selectedColor);
});

function convertOld() {
    var tempOld = [];

    for (var j = 0; j < maxVal; j++) {

        for (var i = 0; i < maxVal; i++) {
            tempOld = colorArray[j][i];
            if (tempOld[0] == 255 && tempOld[1] == 255 && tempOld[2] == 255) {
                colorArray[j][i] = [255,255,255, 0, 0];
            } else if (tempOld[0] == 256 && tempOld[1] == 256 && tempOld[2] == 256) {
                colorArray[j][i] = [255,255,255, 0, 0];
            } else {
                colorArray[j][i] = [tempOld[0],tempOld[1],tempOld[2], 1, 1];
            }
            // bigArray[j][i] = makeColorPixel(j, i);
        }
    }
}

function printArray() {
    $("p.printout").empty();
    var print = "[";

    for (var j = 0; j < maxVal; j++) {
        if (j !== 0) {
            print = print + ",";
        }
        print = print + "[";
        var i=0;
        for (; i < maxVal; i++) {
            if (i !== 0) {
                print = print + ",";
            }

            print = print + "[" +  colorArray[j][i] + "]";
        }
        print = print + "]";
    }
    print = print + "]";

    $("p.printout").text(print);
}

function changeRes(val) {
    var box = $(".pixalSmallx");

    box.empty();

    for (var j = 0; j < val; j++) {
        for (var i = 0; i < val; i++) {
            makeShiftPixel(j, i, val);
        }
    }
}

function changeSolid (value) {
    solidity = value;
}

function clearBoard() {
    $(".pixalBigx").empty();

    for (var j = 0; j < maxVal; j++) {

        for (var i = 0; i < maxVal; i++) {
            colorArray[j][i] = [255,255,255,0,0];
            bigArray[j][i] = makeColorPixel(j, i);
        }
    }
    printArray();
}

function setColorArray (x, y) {
    colorArray[x][y] = [selectedColor[0],selectedColor[1],selectedColor[2], opacity, solidity];
}

function refactorColors() {
    $(".usedColors").empty();

    var color_list = {};
    var colorString = "";

    for (var j = 0; j < maxVal; j++) {
        for (var i=0; i < maxVal; i++) {
            colorString = "[" +  colorArray[j][i] + "]";
            if (!(colorString in color_list)) {
                color_list[colorString] = makeUsedColor(colorArray[j][i]);
            }
        }
    }
}

function selectOpacity (value) {
    opacity = parseInt($(value).text);
}


function selectColor(color) {
    selectedColor = [Math.round((color.rgb[0]*255)/8)*8, Math.round((color.rgb[1]*255)/8)*8, Math.round((color.rgb[2]*255)/8)*8, opacity];
    makeUsedColor(selectedColor);
    makeCurrentColor(selectedColor);
}