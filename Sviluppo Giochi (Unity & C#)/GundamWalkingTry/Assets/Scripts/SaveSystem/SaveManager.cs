using System.Collections;
using UnityEngine.SceneManagement;
using System.Collections.Generic;
using UnityEngine;

public class SaveManager : MonoBehaviour
{
    [SerializeField] ScoreManager _scoreManager;
    [SerializeField] CoinManager _coinManager;
    [SerializeField] PlayerHealthManager _playerHealthManager;
    [SerializeField] PlayerShieldManager _playerShieldManager;
    [SerializeField] Shooting _shooting;
    [SerializeField] GameManager _gameManager;

    private static SaveManager _instance;
    public static SaveManager Instance
    {
        get
        {
            if (_instance == null)
            {
                _instance = GameObject.FindObjectOfType<SaveManager>();
                if (_instance == null) Debug.LogError("No saveManager in scene");
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


    private void Start()
    {
        _gameManager = GameObject.Find("GameManager").GetComponent<GameManager>();
    }

    public void save() {

        //Debug.Log("salvo informazioni");

        _scoreManager.save();
        _coinManager.saveCoins();
        _playerHealthManager.save();
        _playerShieldManager.save();
        _shooting.save();
        _gameManager.save(SceneManager.GetActiveScene().name);
    }

    public void load()
    {
        //Debug.Log("Loading data");
        _gameManager.load();
        _scoreManager.load();
        _coinManager.load();
        _playerHealthManager.load();
        _playerShieldManager.load();
        _shooting.load();
        GameManager.Instance.localData = true;
    }

}
