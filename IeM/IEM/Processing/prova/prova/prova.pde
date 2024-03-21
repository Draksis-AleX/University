/*int d;

size(1000, 700);

d = width/4;

stroke(0);
strokeWeight(3);
background(255);
line(0,height/2,width,height/2);
//noStroke();
fill(255,0,0,100);
ellipse(width/2,height/2,d,d); //ellipse(x_centro, y_centro, diamtro_h, diametro_v)
fill(0,255,0,150);
ellipse(width/2,height/2+d/2,d,d);*/

/*size(500,500);

rect(50,60,80,80);
ellipse(50,60,80,80);

ellipseMode(CORNER);
rect(150,60,80,80);
ellipse(150,60,80,80);

ellipseMode(CORNERS);
ellipse(0,height/2,width, height);*/

color c1 = color(204,104,0);
color c2 = #FFCC00;

size(800, 400);

noStroke();

fill(c1);
rect(25, 0, 50, height);

fill(c2);
rect(100, 0, 50, height);

color c3 = get(120,50);

fill(c3);
rect(175, 0, 50, height);

triangle(175,20,175,height-20,width-20,height/2); //triangle(xp1,yp1,xp2,yp2,xp3,yp3)
