using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;


public class CoinManager :  MonoBehaviour
{

    //====================================  SINGLETON  ==========================================

    private static CoinManager _instance;
    [SerializeField] TextMeshProUGUI coinGui;

    public static CoinManager Instance
    {
        get
        {
            if (_instance == null)
            {
                _instance = GameObject.FindObjectOfType<CoinManager>();
                if (_instance == null) Debug.LogError("No Coin Manager");
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
    }


    //===========================================================================================

    [SerializeField] int my_coins = 0;
    [SerializeField] int MaxCoin = 999999999;

    public void load() {

        intSave i = new intSave();

        if (i.loadIntData("coins") != null)
        {
            i = JsonUtility.FromJson<intSave>(i.loadIntData("coins"));
            //Debug.Log("coin:" + i);
            setCoins(i.value);
        }
        else setCoins(0);


    }

    public void saveCoins()
    {
        intSave i = new intSave();
        i.saveIntData(my_coins, "coins");
    }

    private void Start()
    {
        //loadCoins();
    }

    public int getCoins() { return my_coins; }

    public void setCoins(int coins) { 
        my_coins = coins; 
        coinGui.text = "" + my_coins; 
    }
    public void addCoins(int coins) {
        if (my_coins + coins > MaxCoin) return;
        my_coins += coins;
        coinGui.text = "" + my_coins; 
    }
    public void pay(int coins) { 
        my_coins -= coins; 
        coinGui.text = "" + my_coins;
        saveCoins();
    }

}
