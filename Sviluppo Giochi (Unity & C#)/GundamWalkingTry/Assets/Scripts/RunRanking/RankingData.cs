using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;

[System.Serializable]
public class RankingData
{
    [System.Serializable]
    public struct RunEntry
    {
        public int id;
        public string date;
        public string time;
        public int waves;
        public string time_played;
        public int score;
    }

    string filename = "ranking";
    
    [SerializeField] public List<RunEntry> run_list;
    int runlimit = 6;

    public RankingData()
    {
        run_list = new List<RunEntry>();
    }

    public void addEntry(RunEntry entry)
    {
        if(run_list.Count >= runlimit)
        {
            if(entry.score.CompareTo(run_list[runlimit-1].score) >= 0)
            {
                run_list.RemoveAt(runlimit-1);
                run_list.Add(entry);
            }
        }
        else run_list.Add(entry);

        run_list.Sort(SortByScore);
        string run_list_string = JsonUtility.ToJson(this);
        string filepath = Application.persistentDataPath + "/" + filename + ".json";
        Debug.Log(filepath);
        File.WriteAllText(filepath, run_list_string);
    }

    static int SortByScore(RunEntry r1, RunEntry r2)
    {
        return r2.score.CompareTo(r1.score);
    }

    
}
