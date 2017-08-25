var EPS = 0.0000001;

var Shape = {};

// Due to double rounding precision the value passed into the Math.acos
// function may be outside its domain of [-1, +1] which would return
// the value Double.NaN which we do not want.
function acossafe(x) {
  if (x >= +1.0) return 0;
  if (x <= -1.0) return Math.PI;
  return Math.acos(x);
}

Shape.Point = function (x, y) {
  this.x = x;
  this.y = y;
};

Shape.Point.prototype.dist = function (p) {
    return _dist(this.x, this.y, p.x, p.y);
  },

  // Rotates a point about a fixed point
  Shape.rotatePoint = function (fp, pt, a) {
    var x = pt.x - fp.x;
    var y = pt.y - fp.y;
    var xRot = x * cos(a) + y * sin(a);
    var yRot = y * cos(a) - x * sin(a);
    return new Shape.Point(fp.x + xRot, fp.y + yRot);
  };

Shape.Circle = function (x, y, r) {
  this.x = x;
  this.y = y;
  this.p = new Shape.Point(x, y);
  this.r = r;
};

Shape.Circle.prototype.overlap = function (c) {
  return this.p.dist(c.p) <= (this.r + c.r);
};

Shape.lineLineIntersection = function (l1, l2) {

  var p0 = new Shape.Point(l1.x1, l1.y1);
  var p1 = new Shape.Point(l1.x2, l1.y2);
  var p2 = new Shape.Point(l2.x1, l2.y1);
  var p3 = new Shape.Point(l2.x2, l2.y2);

  var s1, s2;
  s1 = {
    x: p1.x - p0.x,
    y: p1.y - p0.y
  };
  s2 = {
    x: p3.x - p2.x,
    y: p3.y - p2.y
  };

  var s10_x = p1.x - p0.x;
  var s10_y = p1.y - p0.y;
  var s32_x = p3.x - p2.x;
  var s32_y = p3.y - p2.y;

  var denom = s10_x * s32_y - s32_x * s10_y;

  if (denom == 0) {
    return false;
  }

  var denom_positive = denom > 0;

  var s02_x = p0.x - p2.x;
  var s02_y = p0.y - p2.y;

  var s_numer = s10_x * s02_y - s10_y * s02_x;

  if ((s_numer < 0) == denom_positive) {
    return false;
  }

  var t_numer = s32_x * s02_y - s32_y * s02_x;

  if ((t_numer < 0) == denom_positive) {
    return false;
  }

  if ((s_numer > denom) == denom_positive || (t_numer > denom) == denom_positive) {
    return false;
  }

  var t = t_numer / denom;

  return new Shape.Point(p0.x + (t * s10_x), p0.y + (t * s10_y));
}

Shape.circleCircleIntersectionPoints = function (c1, c2) {

  var r, R, d, cx, cy, Cx, Cy;
  if (c1.r < c2.r) {
    r = c1.r;
    R = c2.r;
    cx = c1.x;
    cy = c1.y;
    Cx = c2.x;
    Cy = c2.y;
  } else {
    r = c2.r;
    R = c1.r;
    Cx = c1.x;
    Cy = c1.y;
    cx = c2.x;
    cy = c2.y;
  }

  // Find the distance between two points.
  d = _dist(cx, cy, Cx, Cy);

  // There are an infinite number of solutions
  // Seems appropriate to also return null
  if (d < EPS && abs(R - r) < EPS) return [];

  // No intersection (circles centered at the 
  // same place with different size)
  else if (d < EPS) return [];

  var vx = cx - Cx,
    vy = cy - Cy;
  var x = (vx / d) * R + Cx,
    y = (vy / d) * R + Cy;
  var P = new Shape.Point(x, y);

  // Single intersection (kissing circles)
  if (abs((R + r) - d) < EPS || abs(R - (r + d)) < EPS) return [P];

  // No intersection. Either the small circle contained within 
  // big circle or circles are simply disjoint.
  if ((d + r) < R || (R + r < d)) return [];

  var C = new Shape.Point(Cx, Cy);
  var angle = acossafe((r * r - d * d - R * R) / (-2.0 * d * R));
  var pt1 = Shape.rotatePoint(C, P, +angle);
  var pt2 = Shape.rotatePoint(C, P, -angle);
  return [pt1, pt2];

};

// General formula for line:
// ax + by = c, a != 0
// y = (c - ax)/b
Shape.Line = function (a, b, c) {
  this.a = a;
  this.b = b;
  this.c = c;
  // Normalize
  if (abs(b) < EPS) {
    c /= a;
    a = 1;
    b = 0;
  } else {
    a = (abs(a) < EPS) ? 0 : a / b;
    c /= b;
    b = 1;
  }
};

// Given a line in standard form: ax + by = c and a circle with 
// a center at (x,y) with radius r this method finds the intersection
// of the line and the circle (if any). 
Shape.circleLineIntersection = function (circle, line) {

  var a = line.a,
    b = line.b,
    c = line.c;
  var x = circle.x,
    y = circle.y,
    r = circle.r;

  // Solve for the variable x with the formulas: ax + by = c (equation of line)
  // and (x-X)^2 + (y-Y)^2 = r^2 (equation of circle where X,Y are known) and expand to obtain quadratic:
  // (a^2 + b^2)x^2 + (2abY - 2ac + - 2b^2X)x + (b^2X^2 + b^2Y^2 - 2bcY + c^2 - b^2r^2) = 0
  // Then use quadratic formula X = (-b +- sqrt(a^2 - 4ac))/2a to find the 
  // roots of the equation (if they exist) and this will tell us the intersection points

  // In general a quadratic is written as: Ax^2 + Bx + C = 0
  // (a^2 + b^2)x^2 + (2abY - 2ac + - 2b^2X)x + (b^2X^2 + b^2Y^2 - 2bcY + c^2 - b^2r^2) = 0
  var A = a * a + b * b;
  var B = 2 * a * b * y - 2 * a * c - 2 * b * b * x;
  var C = b * b * x * x + b * b * y * y - 2 * b * c * y + c * c - b * b * r * r;

  // Use quadratic formula x = (-b +- sqrt(a^2 - 4ac))/2a to find the 
  // roots of the equation (if they exist).

  var D = B * B - 4 * A * C;
  var x1, y1, x2, y2;

  // Handle vertical line case with b = 0
  if (abs(b) < EPS) {

    // Line equation is ax + by = c, but b = 0, so x = c/a
    x1 = c / a;

    // No intersection
    if (abs(x - x1) > r) return [];

    // Vertical line is tangent to circle
    if (abs((x1 - r) - x) < EPS || abs((x1 + r) - x) < EPS)
      return [new Shape.Point(x1, y)];

    var dx = abs(x1 - x);
    var dy = sqrt(r * r - dx * dx);

    // Vertical line cuts through circle
    return [
      new Shape.Point(x1, y + dy),
      new Shape.Point(x1, y - dy)
    ];

    // Line is tangent to circle
  } else if (abs(D) < EPS) {

    x1 = -B / (2 * A);
    y1 = (c - a * x1) / b;

    return [new Shape.Point(x1, y1)];

    // No intersection
  } else if (D < 0) {

    return [];

  } else {

    D = sqrt(D);

    x1 = (-B + D) / (2 * A);
    y1 = (c - a * x1) / b;

    x2 = (-B - D) / (2 * A);
    y2 = (c - a * x2) / b;

    return [
      new Shape.Point(x1, y1),
      new Shape.Point(x2, y2)
    ];

  }

};

Shape.LineSegment = function (x1, y1, x2, y2) {
  var d = _dist(x1, y1, x2, y2);
  if (d < EPS) throw 'A point is not a line segment';
  this.x1 = x1;
  this.y1 = y1;
  this.x2 = x2;
  this.y2 = y2;
  this.p1 = new Shape.Point(x1, y1);
  this.p2 = new Shape.Point(x2, y2);
};

Shape.segmentToGeneralForm = function (x1, y1, x2, y2) {
  var a = y1 - y2;
  var b = x2 - x1;
  var c = x2 * y1 - x1 * y2;
  return new Shape.Line(a, b, c);
};

Shape.lineSegmentCircleIntersection = function (segment, circle) {

  var x1 = segment.x1,
    y1 = segment.y1,
    x2 = segment.x2,
    y2 = segment.y2;
  var line = Shape.segmentToGeneralForm(x1, y1, x2, y2);

  var pts = Shape.circleLineIntersection(circle, line);

  // No intersection
  if (pts.length === 0) return [];

  var pt1 = pts[0];
  var includePt1 = Shape.pointInRectangle(pt1, x1, y1, x2, y2);

  if (pts.length === 1) {
    if (includePt1) return [pt1];
    return [];
  }

  var pt2 = pts[1];
  var includePt2 = Shape.pointInRectangle(pt2, x1, y1, x2, y2);

  if (includePt1 && includePt2) return [pt1, pt2];
  if (includePt1) return [pt1];
  if (includePt2) return [pt2];
  return [];

};

// (x1,y1) is a top left corner, (x2,y2) is a bottom right corner
Shape.pointInRectangle = function (pt, x1, y1, x2, y2) {
  var x = min(x1, x2),
    X = max(x1, x2);
  var y = min(y1, y2),
    Y = max(y1, y2);
  return x - EPS <= pt.x && pt.x <= X + EPS &&
    y - EPS <= pt.y && pt.y <= Y + EPS;
};