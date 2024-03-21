using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerManager : MonoBehaviour
{
    private static PlayerManager _instance;

    public static PlayerManager Instance
    {
        get
        {
            if (_instance == null)
            {
                //_instance = GameObject.FindObjectOfType<PlayerManager>();
                if (_instance == null) Debug.LogError("No Player in scene");
            }
            return _instance;
        }
    }

    private void Awake()
    {

        Debug.Log("Awake Player");

        if (_instance == null)
        {
            _instance = this;
            GameObject.DontDestroyOnLoad(this.gameObject);
        }
        else
        {
            Debug.Log("Destroyed Player");
            GameObject.Destroy(this.gameObject);
        }
    }
}
