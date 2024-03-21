using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CheckPoint : MonoBehaviour
{
    [SerializeField] SaveUI savingUI;

    private void Start()
    {
        savingUI = GameObject.Find("SavePanel").GetComponent<SaveUI>();
        if (GameManager.Instance.loadData)
        {
            Debug.Log("Loading Datas");
            SaveManager.Instance.load();
            GameManager.Instance.loadData = false;
        }
        if (GameManager.Instance.localData == true) Save();
    }

    public void Save()
    {
        savingUI.Show();
        SaveManager.Instance.save();
        //Debug.Log("Checkpoint Saving");
    }
}
