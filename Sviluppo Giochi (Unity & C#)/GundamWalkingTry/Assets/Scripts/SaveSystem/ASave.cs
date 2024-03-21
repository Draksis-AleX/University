using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;

[System.Serializable]
public abstract class ASave
{

    public void saveData(string namesave)
    {

        string sdata = JsonUtility.ToJson(this);
        string filepath = Application.persistentDataPath + "/" + namesave + ".json";

        Debug.Log(filepath);

        File.WriteAllText(filepath, sdata);

        //Debug.Log("salvato" + namesave);
    }

    public string loadData(string namesave)
    {

        string filepath = Application.persistentDataPath + "/" + namesave + ".json";
        if (!File.Exists(filepath)) return null;

        string sdata = File.ReadAllText(filepath);

        //Debug.Log(sdata);

        return sdata;

    }
}

