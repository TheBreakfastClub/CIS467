var mDown = false;

function makeShiftPixel (x, y, size) {
    var pixel = {};

    pixel.value = mixColors(x, y, maxVal / size);
    // console.log(pixel.value);
    pixel.pix = $('<div/>')
        .addClass("singlePixel" + size)
        .css("background-color", "rgba("+pixel.value[0]+","+pixel.value[1]+","+pixel.value[2]+","+pixel.value[3]+")");

    $(".pixalSmallx").append(pixel.pix);

    pixel.changeColor = function (value) {
        pixel.pix.css("background-color", "rgba("+value[0]+","+value[1]+","+value[2]+","+opacity+")");
    };

    return pixel;
}

function makeCurrentColor (color) {
    var currentColor = {};

    currentColor.pix = $('<div/>')
        .addClass("usedColor")
        .css("background-color", "rgba("+color[0]+","+color[1]+","+color[2]+","+opacity+")")
        .text("rgba("+color[0]+","+color[1]+","+color[2]+","+opacity+")");

    $(".currentColor").empty();
    $(".currentColor").append(currentColor.pix);

    currentColor.pix.click(function (e) {
        selectedColor = color;
    });

    return currentColor;
}

function makeUsedColor (color) {
    var usedColor = {};

    var close_box = $('<div/>')
        .addClass("usedColorClose")
        .text("X");

    close_box.click(function(e) {
        close_box.parent().remove();
    });

    usedColor.pix = $('<div/>')
        .addClass("usedColor")
        .css("background-color", "rgba("+color[0]+","+color[1]+","+color[2]+","+color[3]+")")
        .text("rgba("+color[0]+","+color[1]+","+color[2]+","+color[3]+")")
        .append(close_box);

    $(".usedColors").append(usedColor.pix);

    usedColor.pix.click(function (e) {
        selectedColor = color;
    });

    return usedColor;
}


function makeColorPixel (x, y) {
    var pixel = {};

    pixel.solid = 0;

    pixel.pix = $('<div/>')
        .addClass("singlePixel" + maxVal);

    $(".pixalBigx").append(pixel.pix);

    pixel.changeColor = function (value) {
        pixel['color'] = value;
        pixel.pix.css("background-color", "rgba("+value[0]+","+value[1]+","+value[2]+","+value[3]+")");
        smallArray[x][y].changeColor(value);
        // setColorArray(x,y);
    };


    // pixel.pix.click(function(e) {
    //     selectedPixel = pixel;
    //     $(".selected").toggleClass("selected", false);
    //     pixel.pix.toggleClass("selected", true);
    //     pixel.changeColor(selectedColor);
    //     printArray();

    // });

    pixel.pix.mouseover(function (e) {
        if (mDown) {
            pixel.changeColor(selectedColor);
            setColorArray(x, y);
        }
    });

    pixel.pix.mousedown(function (e) {
        mDown = true;
        pixel.changeColor(selectedColor);
        setColorArray(x, y);
        
    });

    pixel.pix.mouseup(function (e) {
        mDown = false;
        printArray();
    });

    pixel.changeColor(colorArray[x][y]);

    return pixel;
}