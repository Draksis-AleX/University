using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.InputSystem;

public class GameManager : MonoBehaviour
{
    public GameData gameData;
    GameObject deathUI;

    //====================================  SINGLETON  ==========================================

    private static GameManager _instance;
    public bool localData = false;
    public bool loadData = false;

    public static GameManager Instance
    {
        get
        {
            if (_instance == null)
            {
                _instance = GameObject.FindObjectOfType<GameManager>();
                if (_instance == null) Debug.LogError("No GameManager in scene");
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
        Init();
        load();
    }

    private void Init()
    {
        gameData = new GameData();
    }

    private void Update()
    {
        if (gameData.count_time) gameData.run_time += Time.unscaledDeltaTime;
    }

    //========================== RESTART RUN ==========================================

    public void runRestart()
    {
        StartCoroutine(LoadScene(1));
    }

    public void restartRun()
    {
        RankingManager.Instance.saveRun(gameData.run_start_date, gameData.run_start_time, gameData.wavesCompleted, ScoreManager.Instance.getScore(), gameData.run_time);
        deathUI = GameObject.Find("DeathUI").transform.GetChild(0).gameObject;
        deathUI.GetComponent<PlayerDeath>().ShowUI(ScoreManager.Instance.getScore(), gameData.run_time);
        Debug.Log("Score: " + ScoreManager.Instance.getScore() + " run_time: " + gameData.run_time);
        ScoreManager.Instance.resetScore();
        CoinManager.Instance.load();
        Init();
        save("StartingHangar");

        resetLife();
        resetWaves();

        gameData.count_time = false;
        gameData.run_time = 0;
        gameData.first_arena = true;
        gameData.wavesCompleted = 0;
    }

    void resetLife()
    {
        PlayerManager.Instance.GetComponent<PlayerHealthManager>().reset();
        PlayerManager.Instance.GetComponent<PlayerShieldManager>().reset();
        VolumeManager.Instance.setVignetteIntensity((float)0);
    }

    void resetWaves()
    {
        gameData.wavesNumber = 1;
        gameData.wave_enemies_number = 3;
    }

    private IEnumerator LoadScene(int sceneIndex)
    {
        // Start loading the scene
        AsyncOperation asyncLoadLevel = SceneManager.LoadSceneAsync(sceneIndex, LoadSceneMode.Single);

        // Wait until the level finish loading
        while (!asyncLoadLevel.isDone)
            yield return null;

        restartRun();
    }

    //=================================================================================

    public void EnteredArena() {
        gameData.tookPowerUp = false;
        gameData.completedArena = false;
        ScoreManager.Instance.StartTimer();
        if (gameData.first_arena)
        {
            Debug.Log("Starting New Run");
            gameData.run_start_date = System.DateTime.Now.ToString("dd/MM/yyyy");
            gameData.run_start_time = System.DateTime.Now.ToString("hh:mm");
            gameData.first_arena = false;
            gameData.count_time = true;
        }
    }

    public void DefeatedArena()
    {
        gameData.arenaDefeated++;
        ScoreManager.Instance.StopTimer(gameData.wavesNumber);
        gameData.wavesNumber = (int)Mathf.Ceil(gameData.wavesNumber * 1.5f);
        gameData.completedArena = true;
    }


    public void save(string scene) {
        gameData.scene = scene;
        gameData.saveData("game");
    }

    public void save()
    {
        gameData.saveData("game");
    }

    public void load() {
        if (gameData.loadData("game") != null)
        {
            gameData = JsonUtility.FromJson<GameData>(gameData.loadData("game"));
        }
        else Init();
    }
}
