using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;

[System.Serializable]
public class intSave 
{
    public int value;
    public intSave(){}
    public void saveIntData(int data, string namesave)
    {
        value = data;

        //Debug.Log("value:" + value);

        string sdata = JsonUtility.ToJson(this);
        string filepath = Application.persistentDataPath + "/" + namesave + ".json";

        Debug.Log(filepath);

        File.WriteAllText(filepath, sdata);

        //Debug.Log("salvato" + namesave);

    }

    public string loadIntData(string namesave)
    {
        string filepath = Application.persistentDataPath + "/" + namesave + ".json";
        if (!File.Exists(filepath)) return null;

        string sdata = File.ReadAllText(filepath);

        return sdata;

    }
}
