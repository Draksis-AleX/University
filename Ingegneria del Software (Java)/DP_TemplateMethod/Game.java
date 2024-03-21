public abstract class Game {
    abstract void initialize();
    abstract void startPlay();
    abstract void endPlay();
    public void enjoy() { System.out.println("Enjoy the Game!"); }
 
    //template method
    public final void play(){
 
        //initialize the game
        initialize();
 
        //start game
        startPlay();

        //enjoy the game (default implementation)
        enjoy();
 
        //end game
        endPlay();
    }
 }