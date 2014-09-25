var pixelAlg = avgWithSurroundColors;

function changeAlg(value) {
    if (value == 1) {
        pixelAlg = avgWithSurroundColors;
    } else if (value == 2) {
        pixelAlg = avgWithoutSurroundColors;
    } else {
        pixelAlg = minColors;
    }
}

function mixColors (x, y, num) {
    return pixelAlg(x, y, num);
}

function avgWithSurroundColors(x, y, num) {
    var newColor = [0,0,0,0];
    var counter = 0;

    for (var j = 0; j < num; j++) {

        for (var i = 0; i < num; i++) {
            newColor[0] = newColor[0] + colorArray[(x*num)+j][(y*num)+i][0];
            newColor[1] = newColor[1] + colorArray[(x*num)+j][(y*num)+i][1];
            newColor[2] = newColor[2] + colorArray[(x*num)+j][(y*num)+i][2];
            newColor[3] = newColor[3] + colorArray[(x*num)+j][(y*num)+i][3];
            counter++;
        }
    }

    newColor[0] = Math.round(newColor[0]/(counter)/8)*8;
    newColor[1] = Math.round(newColor[1]/(counter)/8)*8;
    newColor[2] = Math.round(newColor[2]/(counter)/8)*8;
    // newColor[3] = Math.round(newColor[3]/(counter)/8)*8;

    return newColor;
}

function avgWithoutSurroundColors(x, y, num) {
    var newColor = [0,0,0,0];
    var counter = 0;

    for (var j = 0; j < num; j++) {

        for (var i = 0; i < num; i++) {
            if (colorArray[(x*num)+j][(y*num)+i][4]) {
                newColor[0] = newColor[0] + colorArray[(x*num)+j][(y*num)+i][0];
                newColor[1] = newColor[1] + colorArray[(x*num)+j][(y*num)+i][1];
                newColor[2] = newColor[2] + colorArray[(x*num)+j][(y*num)+i][2];
                newColor[3] = newColor[3] + colorArray[(x*num)+j][(y*num)+i][3];
                counter++;
            }
        }
    }

    newColor[0] = Math.round(newColor[0]/(counter)/8)*8;
    newColor[1] = Math.round(newColor[1]/(counter)/8)*8;
    newColor[2] = Math.round(newColor[2]/(counter)/8)*8;
    // newColor[3] = Math.round(newColor[3]/(counter)/8)*8;

    return newColor;
}

function maxColors (x, y, num) {
    console.log("max");

    var newColor = 0;

    for (var j = 0; j < num; j++) {

        for (var i = 0; i < num; i++) {
            if (colorArray[(x*num)+j][(y*num)+i] > newColor) {
                newColor = colorArray[(x*num)+j][(y*num)+i];
            }
        }
    }

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
        }
    }

    return newColor;
}