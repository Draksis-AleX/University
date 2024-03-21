
ArrayList<Quadrotto> squares = new ArrayList<Quadrotto>();

int maxDim = 500;
int minDim = 100;
int n_quadrotti = 3;

class Quadrotto {

  int lato;
  int x;
  int y;
  int speed;
  color col;
  color border_col;
  
  Quadrotto(){
  
    lato = int(random(minDim,maxDim));
    x = int(random(0,width-lato));
    y = int(random(0,height-lato));
    speed = 1;
    int r = int(random(0,256));
    int g = int(random(0,256));
    int b = int(random(0,256));
    col = color(r, g, b);
    border_col = color(255 - r, 255 - g, 255 - b);
    
  }
  
  Quadrotto(int lato, int x, int y){
   
    this.lato = lato;
    this.x = x;
    this.y = y;
    speed = 1;
    int r = int(255);
    int g = int(0);
    int b = int(0);
    col = color(r, g, b);
    border_col = color(255 - r, 255 - g, 255 - b);
    println("[New Quadrotto] x: " + this.x + " - y: " + this.y + " - Lato: " + this.lato);
    
  }
  
  void display() {
    
    fill(col);
    strokeWeight(2);
    stroke(border_col);
    rect(x,y,lato,lato);
    
  }
  
  void move() {
  
    int dir = int(random(0,4));
    
    switch(dir) {
    
      case 0:
        x += speed;
        break;
      case 1:
        x -= speed;
        break;
      case 2:
        y += speed;
        break;
      case 3:
        y -= speed;
        break;
      
    }
  
  }
  
}

void setup(){
  
  size(1200, 750);
  
  for(int i = 0; i < n_quadrotti; i++){
    Quadrotto q = new Quadrotto();
    squares.add(q);
  }
  
  frameRate(30);
  
}

void draw(){

  background(255);
  for(int i = 0; i < n_quadrotti; i++){
    Quadrotto q = squares.get(i);
    q.display();
    q.move();
  }
  
  checkCollision();
  checkLimits();
  
}

void checkCollision(){

  for(int i = 0; i < n_quadrotti; i++){
    Quadrotto q1 = squares.get(i);
    
    //println("q1: sx["+ start_x_q1 + "] fx["+ final_x_q1 + "] sy["+ start_y_q1 + "] fy["+ final_y_q1 + "]");
      
    for(int j = 0; j < n_quadrotti; j++){
      
      Quadrotto q2 = squares.get(j);
      
      //println("q2: sx["+ start_x_q2 + "] fx["+ final_x_q2 + "] sy["+ start_y_q2 + "] fy["+ final_y_q2 + "]");
      if (i != j && q1.x < q2.x + q2.lato &&
        q1.x + q1.lato > q2.x &&
        q1.y < q2.y + q2.lato &&
        q1.lato + q1.y > q2.y){
          println("Collision");
          squares.remove(q1);
          squares.remove(q2);
          
          int new_x = int(((q1.x + q1.lato/2) + (q2.x + q2.lato/2)) / 2);
          int new_y = int(((q1.y + q1.lato/2) + (q2.y + q2.lato/2)) / 2);
          int new_lato = int((q1.lato + q2.lato) / 2);
          
          println("First center : " + (q1.x + q1.lato/2) + " - " + (q1.y + q1.lato/2));
          println("Second center : " + (q2.x + q2.lato/2) + " - " + (q2.y + q2.lato/2));
          println("New center : " + int(((q1.x + q1.lato/2) + (q2.x + q2.lato/2)) / 2) + " - " + int(((q1.y + q1.lato/2) + (q2.y + q2.lato/2)) / 2));
          println("First lato : " + q1.lato + " Second lato : " + q2.lato + " New lato : " + int((q1.lato + q2.lato) / 2));
          
          Quadrotto q_child = new Quadrotto(new_lato, new_x - new_lato/2, new_y - new_lato /2);
          squares.add(q_child);
          n_quadrotti--;
        }  
      } 
    }
  } 
  
  
void checkLimits(){

  for(int i = 0; i < n_quadrotti; i++){
  
     Quadrotto q1 = squares.get(i);
     
     if(q1.x < 0 || q1.x + q1.lato > width || q1.y < 0 || q1.y + q1.lato > height) {
     
       squares.remove(q1);
       n_quadrotti--;
       println("Limite superato!");
       
     }
    
  }

}
