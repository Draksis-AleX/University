using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class ScoreInfo : MonoBehaviour
{
    [SerializeField] TextMeshProUGUI text;

    public void updateScore(int score)
    {
        text.text = score.ToString("000000000");
    }
}
