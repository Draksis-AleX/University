using UnityEngine;

// @kurtdekker
// Put this ON the UnityEngine.UI.Text object you're using to display score

public class GMShowScore : MonoBehaviour
{
	int lastScore;

	void UpdateToText()
	{
		lastScore = GM.Score;

		var text = GetComponent<UnityEngine.UI.Text>();

		// Be SURE this GameObject has a UnityEngine.UI.Text component on it!
		text.text = "Score:" + lastScore;
	}

	void Start()
	{
		UpdateToText();
	}
	void Update ()
	{
		if (GM.Score != lastScore)
		{
			UpdateToText();
		}
	}
}
