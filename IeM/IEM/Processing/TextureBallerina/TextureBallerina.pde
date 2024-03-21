
int l = 80;

void setup(){
  size(800,800);
  frameRate(24);
}

void draw(){
  background(mouseX,255,0);
  noStroke();
  for(int y = 0; y <= height; y += l){
    for(int x = 0; x <= width; x += l){
      println("Ciclo");
      fill(random(256),130);
      rect(x+random(-5,5), y+random(-5,5),l,l);
    }
  }
}
