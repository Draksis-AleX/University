using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
using TMPro;

public class RankingWindow : Window
{
    [SerializeField] public GameObject blur;
    string filename = "ranking";
    [SerializeField] GameObject runPanel;

    RankingData rd;

    public void OnEnable()
    {
        AudioMenager.Instance.PlayEffect("OpenUI");
        WindowManager.Instance.setDiplayEmpty(false);
        Time.timeScale = 0f;

        string filepath = Application.persistentDataPath + "/" + filename + ".json";
        if (!File.Exists(filepath)) return;

        string json_string = File.ReadAllText(filepath);
        rd = JsonUtility.FromJson<RankingData>(json_string);

        //Debug.Log("run_list: " + rd.run_list);
        int index = 0;

        foreach (RankingData.RunEntry run in rd.run_list)
        {
            //Debug.Log("Run Entry from Ranking Window: [ #" + run.id + " | " + run.date + " | " + run.time + " | " + run.waves + " | " + run.score + " | " + run.time_played + " ] ");
            runPanel.transform.GetChild(index).Find("ID").GetComponent<TextMeshProUGUI>().text = run.id.ToString();
            runPanel.transform.GetChild(index).Find("Data").GetComponent<TextMeshProUGUI>().text = run.date.ToString();
            runPanel.transform.GetChild(index).Find("Time").GetComponent<TextMeshProUGUI>().text = run.time.ToString();
            runPanel.transform.GetChild(index).Find("Waves").GetComponent<TextMeshProUGUI>().text = run.waves.ToString();
            runPanel.transform.GetChild(index).Find("TimePlayed").GetComponent<TextMeshProUGUI>().text = run.time_played.ToString();
            runPanel.transform.GetChild(index).Find("Score").GetComponent<TextMeshProUGUI>().text = run.score.ToString();
            index++;
        }
    }

    override public void other()
    {
        blur.GetComponent<CanvasGroup>().alpha = 0;
    }
}
