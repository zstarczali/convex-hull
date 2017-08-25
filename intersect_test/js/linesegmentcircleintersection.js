class Circle extends Shape.Circle {
  constructor(x, y, r) {
    super(x, y, r);
    this.v = p5.Vector.random2D();
  }
}

Circle.prototype.display = function () {
  noFill();
  strokeWeight(2);
  ellipse(this.x, this.y, this.r);
  // this.x += this.v.x;
  // this.y += this.v.y;
  if (this.x - this.r > width) this.x = -this.r;
  else if (this.x + this.r < 0) this.x = width + this.r;
  if (this.y + this.r < 0) this.y = height + this.r;
  else if (this.y - this.r > height) this.y = -this.r;
};

class LineSegment extends Shape.LineSegment {
  constructor(x1, y1, x2, y2) {
    super(x1, y1, x2, y2);
  }
}

LineSegment.prototype.display = function () {
  strokeWeight(2);
  line(this.x1, this.y1, this.x2, this.y2);
};

var W = window.innerWidth,
  H = window.innerHeight;
var lines = [];
var circles = [];

var xIn, yIn, rIn, x1In, y1In, x2In, y2In;
var xText, yText, rText, x1Text, y1Text, x2Text, y2Text;
var lineSubmit, circleSubmit, randomBtn, edgeCaseButton1, clrButton;

function createLineSegment() {
  var x1 = int(x1In.value());
  var y1 = int(y1In.value());
  var x2 = int(x2In.value());
  var y2 = int(y2In.value());
  if (!isNaN(x1) && !isNaN(y1) && !isNaN(x2) && !isNaN(y2)) {
    var segment = new LineSegment(x1, y1, x2, y2);
    lines.push(segment);
  }
}

function createCircle() {
  var x = int(xIn.value());
  var y = int(yIn.value());
  var r = int(rIn.value());
  console.log(x, y, r);
  if (!isNaN(x) && !isNaN(y) && !isNaN(r)) {
    var circle = new Circle(x, y, r);
    circle.v.x = circle.v.y = 0;
    circles.push(circle);
    console.log("Added: ", circle, circles);
  }
  // xIn.value('');
  // yIn.value('');
  // rIn.value('');
}

function setup() {

  xText = createP('Circle x: ');
  xText.position(15, 20);
  yText = createP('Circle y: ');
  yText.position(15, 50);
  rText = createP('Circle r: ');
  rText.position(15, 80);
  circleSubmit = createButton('Create circle');
  circleSubmit.position(60, 110);
  circleSubmit.mousePressed(createCircle);
  x1Text = createP('Line x1: ');
  x1Text.position(15, 140);
  y1Text = createP('Line y1: ');
  y1Text.position(15, 170);
  x2Text = createP('Line x2: ');
  x2Text.position(15, 200);
  y2Text = createP('Line y2: ');
  y2Text.position(15, 230);
  lineSubmit = createButton('Create line segment');
  lineSubmit.position(60, 270);
  lineSubmit.mousePressed(createLineSegment);
  xIn = createInput();
  xIn.position(80, 20);
  yIn = createInput();
  yIn.position(80, 50);
  rIn = createInput();
  rIn.position(80, 80);
  x1In = createInput();
  x1In.position(80, 140);
  y1In = createInput();
  y1In.position(80, 170);
  x2In = createInput();
  x2In.position(80, 200);
  y2In = createInput();
  y2In.position(80, 230);

  createCanvas(W, H);
  ellipseMode(RADIUS);
  textSize(25);

  // testCase1();
  addRandomCircles(10);
  addRandomLineSegments(20);

  randomBtn = createButton('Randomize');
  randomBtn.position(60, 300);
  randomBtn.mousePressed(genRandom);

  randomLinesBtn = createButton('Randomize Lines');
  randomLinesBtn.position(60, 330);
  randomLinesBtn.mousePressed(genRandomLines);

  
  randomCirclesBtn = createButton('Randomize Circles');
  randomCirclesBtn.position(60, 360);
  randomCirclesBtn.mousePressed(genRandomCircles);

  edgeCaseButton1 = createButton('Display edge cases');
  edgeCaseButton1.position(60, 390);
  edgeCaseButton1.mousePressed(testCase1);

  clrButton = createButton('Clear screen');
  clrButton.position(60, 420);
  clrButton.mousePressed(clearScreen);

}

function clearScreen() {
  circles = [];
  lines = [];
}

function testCase1() {

  clearScreen();

  circles.push(new Circle(250, 100, 50));
  circles.push(new Circle(330, 300, 30));
  lines.push(new LineSegment(300, 30, 300, 500));

  var x = 300,
    y = 600,
    r = 100;
  var xx = 20,
    yy = 650;
  circles.push(new Circle(x, y, r));
  for (var i = 0; i < 5; i++) {
    var x1 = random(x - r, x + r);
    var y1;
    if (random() < 0.5) y1 = y + sqrt(r * r - pow(x - x1, 2));
    else y1 = y - sqrt(r * r - pow(x - x1, 2));
    lines.push(new LineSegment(xx, yy, x1, y1));
  }

  circles.push(new Circle(310, 30, 10));
  x = W / 2;
  y = H / 2;
  r = random(150, 250);
  circles.push(new Circle(x, y, r));
  for (i = 0; i < 10; i++) {
    var x1 = random(x - r, x + r);
    var y1 = y - sqrt(r * r - pow(x - x1, 2));
    var x2 = random(x - r, x + r);
    var y2 = y + sqrt(r * r - pow(x - x2, 2));
    lines.push(new LineSegment(x1, y1, x2, y2));
  }

}

function genRandom() {
  clearScreen();
  addRandomCircles(10);
  addRandomLineSegments(10);
}

function genRandomLines() {
  clearScreen();
  addRandomLineSegments(20);
}

function genRandomCircles() {
  clearScreen();
  addRandomCircles(20);
}

function addRandomCircles(n) {
  while (n-- > 0) {
    var r = random(10, 300);
    var x = random(200 + r, W - r);
    var y = random(r + 50, H - r);
    circles.push(new Circle(x, y, r));
  }
}

function addRandomLineSegments(n) {
  while (n-- > 0) {
    var x1 = random(100, W);
    var y1 = random(0, H);
    var x2 = random(100, W);
    var y2 = random(0, W);
    lines.push(new LineSegment(x1, y1, x2, y2));
  }
}

function draw() {

  background(0, 255, 0);

  for (var i = 0; i < circles.length; i++) circles[i].display();
  for (i = 0; i < lines.length; i++) {
    lines[i].display();
  }

  for (i1 = 0; i1 < lines.length; i1++) {
    for (i2 = 0; i2 < lines.length; i2++) {
      if (i1 !== i2) {
        var pts = Shape.lineLineIntersection(lines[i1], lines[i2]);
        if (pts) displayPoint(pts);
      }
    }
  }

  for (i1 = 0; i1 < circles.length; i1++) {
    for (i2 = 0; i2 < circles.length; i2++) {
      if (i1 !== i2) {
        var pts = Shape.circleCircleIntersectionPoints(circles[i1], circles[i2]);
        for (var k = 0; k < pts.length; k++) {
          displayPoint(pts[k]);
        }
      }
    }
  }

  for (i = 0; i < circles.length; i++) {
    for (var j = 0; j < lines.length; j++) {
      var pts = Shape.lineSegmentCircleIntersection(lines[j], circles[i]);
      for (var k = 0; k < pts.length; k++) {
        displayPoint(pts[k]);
      }
    }
  }

  displayFrameRate();
}

function displayFrameRate() {
  text("FPS: " + frameRate().toFixed(0), 20, height - 20);
}

function displayPoint(p) {
  fill(255);
  strokeWeight(2);
  ellipse(p.x, p.y, 4);
}