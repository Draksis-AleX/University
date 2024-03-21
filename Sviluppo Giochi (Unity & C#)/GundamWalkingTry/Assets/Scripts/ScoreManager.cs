using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class ScoreManager : MonoBehaviour
{
    [SerializeField] int score = 0;
    [SerializeField] int base_waveScore = 100;
    private static ScoreManager _instance;
    int waveScore = 0;
    ScoreInfo scoreInfo;
    float timer = 0;
    bool measureTime = false;
    bool locked = false;
    private int max_score = 999999999;
    
    //[SerializeField] TextMeshProUGUI scoreGUI;

    public static ScoreManager Instance
    {
        get
        {
            if (_instance == null)
            {
                _instance = GameObject.FindObjectOfType<ScoreManager>();
                if (_instance == null) Debug.LogError("No score Manager");
            }
            return _instance;
        }
    }

    private void Awake()
    {
        if (_instance == null)
        {
            _instance = this;
            GameObject.DontDestroyOnLoad(this.gameObject);
        }
        else
        {
            GameObject.Destroy(this.gameObject);
        }

        scoreInfo = GameObject.Find("ScorePanel").GetComponent<ScoreInfo>();
    }

    private void Start()
    {
        //loadScore();
        scoreInfo.updateScore(score);
    }

    private void Update()
    {
        if (measureTime) timer += Time.unscaledDeltaTime;
    }

    //=======================================================================

    public int getScore() { return score; }

    public void moreScore(int bonus) {
        if (score + bonus > max_score) return;
        score += 5 * bonus;
        scoreInfo.updateScore(score);
    }

    public void lessScore(int malus){
        score -= 1 * malus;
        if (score <= 0) score = 0;
        scoreInfo.updateScore(score);
    }

    public void resetScore() { 
        score = 0;
        scoreInfo.updateScore(score);
        save();
    }

    //=========================================== ARENA TIMER SCORE =============================

    public void updateWaveScore(int n_enemies)
    {
        waveScore += n_enemies * base_waveScore;
    }

    public void StartTimer()
    {
        measureTime = true;
    }

    public void StopTimer(int waves_number)
    {
        measureTime = false;
        //Debug.Log("Completation Time: " + timer);
        //Debug.Log("Score: ((" + waves_number + " * 3) * " + waveScore + ")/(" + timer + "/100)");
        //Debug.Log("Score added: " + (int)Mathf.Ceil(((waves_number * 3) * waveScore) / (timer / 100)));
        moreScore((int)Mathf.Ceil(((waves_number * 3) / (timer / 100)))) ;
        waveScore = 0;
        timer = 0;
    }

    //======================================= SAVE SCORE =====================================================

    public void load()
    {
        intSave i = new intSave();

        if (i.loadIntData("score") != null)
        {
            i = JsonUtility.FromJson<intSave>(i.loadIntData("score"));
            //Debug.Log("score:" + i);
            score = i.value;
        }
        else score = 0;
        scoreInfo.updateScore(score);
    }

    public void save()
    {
        intSave i = new intSave();
        i.saveIntData(score, "score");
    }

}
