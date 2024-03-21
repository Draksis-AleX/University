
size (1000,1000);

background(255);

stroke(0);
strokeWeight(ceil(width/250));
fill(0,0,0,0);
line(0,height/2,width,height/2);

ellipseMode(RADIUS);
int radius = width/18;
int x=width/10;
for(int i = 0; i<8; i++){
  circle(x,height/2,radius);
  x+=width/18;
  radius+=width/18;
}
