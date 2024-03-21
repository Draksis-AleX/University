using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ExampleGameController : MonoBehaviour
{
	public void StartNewGame()
	{
		GM.InitGame();
	}

	public void EarnSomePoints()
	{
		GM.AddScore( Random.Range( 1, 1000));
	}
}
