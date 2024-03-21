//
// @kurtdekker
//
// ULTRA-simple fully-static GameManager for simple arcade-style games.
//
// Usage:
//	- at start of game call GM.InitGame()
//	- when you earn points, call GM.AddPoints(1234);
//	- when you want to display score, get it from GM.Score (see GMShowScore.cs below)
//	- when you want to display lives, get it from GM.Lives
//
// To persistently store high scores, see https://pastebin.com/VmngEK05
//

public static class GM
{
	public static int Score;
	public static int Lives;
	
	// TODO: go nuts if you want to add more stuff like health and wave and coins, etc.!

	public static void InitGame()
	{
		Score = 0;
		Lives = 4;
	}

	public static void AddScore( int points)
	{
		Score += points;
	}
}