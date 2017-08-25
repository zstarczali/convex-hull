function _dist(x1, y1, z1, x2) {
    var ret = _hypot(z1 - x1, x2 - y1);
    //console.log("_dist(" + x1 + "," + y1 + "," + z1 + "," + x2 + ")=" + ret)

    // In the case of 2d: z1 means x2 and x2 means y2
    return ret;
};

// Calculate the length of the hypotenuse of a right triangle
// This won't under- or overflow in intermediate steps
// https://en.wikipedia.org/wiki/Hypot
function _hypot(x, y) {

    // Otherwise use the V8 implementation
    // https://github.com/v8/v8/blob/8cd3cf297287e581a49e487067f5cbd991b27123/src/js/math.js#L217
    var length = arguments.length;
    var args = [];
    var max = 0;
    for (var i = 0; i < length; i++) {
        var n = arguments[i];
        n = +n;
        /*         if (n === Infinity || n === -Infinity) {
                    return Infinity;
                } */
        n = Math.abs(n);
        if (n > max) {
            max = n;
        }
        args[i] = n;
    }

    if (max === 0) {
        max = 1;
    }
    var sum = 0;
    var compensation = 0;
    for (var j = 0; j < length; j++) {
        var m = args[j] / max;
        var summand = m * m - compensation;
        var preliminary = sum + summand;
        compensation = (preliminary - sum) - summand;
        sum = preliminary;
    }
    var ret = Math.sqrt(sum) * max;
    //console.log("_hypot(" + x + "," + y + ")=" + ret);

    return ret;
};