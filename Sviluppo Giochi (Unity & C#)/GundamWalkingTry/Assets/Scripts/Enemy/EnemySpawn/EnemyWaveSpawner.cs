using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class EnemyWaveSpawner : MonoBehaviour
{
    //================================== SINGLETON ========================================
    public static EnemyWaveSpawner Instance
    {
        get
        {
            if (_instance == null)
            {
                _instance = GameObject.FindObjectOfType<EnemyWaveSpawner>();
                if (_instance == null) Debug.LogError("No EnemyManager in scene");
            }
            return _instance;
        }
    }

    private void Awake()
    {
        if (_instance == null)
        {
            _instance = this;
        }
        else
        {
            GameObject.Destroy(this.gameObject);
        }
    }

    //================================ WAVE CLASS ======================================
    [System.Serializable]
    public class Wave{
        [SerializeField] [NonReorderable] public GameObject[] enemyType;
        [SerializeField] [NonReorderable] public GameObject[] enemySpawner;

        public Wave(int waveSize, int enemyTypes)
        {
            this.enemySpawner = new GameObject[waveSize];
            this.enemyType = new GameObject[enemyTypes];
            if (enemyType.Length == 3)
            {
                this.enemyType[0] = (GameObject)Resources.Load("Prefabs/Entities/aku");
                this.enemyType[1] = (GameObject)Resources.Load("Prefabs/Entities/aku-verde");
                this.enemyType[2] = (GameObject)Resources.Load("Prefabs/Entities/aku-blu");
            }
        }

        public void Start() {
        
            for (int i = 0; i < enemySpawner.Length; i++) {;
                //Debug.Log("RandEnemyType: "+Random.Range(0, enemyType.Length));
                enemySpawner[i] = enemyType[Random.Range(0, enemyType.Length)];
            }
            
        }
        public GameObject[] getEnemySpawnList(){
            return enemySpawner;
        }

        public void setWaveSize(int size)
        {
            enemySpawner = new GameObject[size];
        }

        public void setTypesSize(int size)
        {
            enemyType = new GameObject[size];
        }
    }

    //============================== MAIN CLASS =========================================

    [SerializeField][NonReorderable] Wave[] waves;
    [SerializeField] GameObject _EnemySpawnPoints;
    private static EnemyWaveSpawner _instance;
    [SerializeField] private GameObject effect;
    [SerializeField] float dist;
    [SerializeField] WaveInfo WaveInfoPanel;
    [SerializeField] int enemy_count_limit = 30; 

    int currentWave = 0;
    int enemyKilled = 0;

    void Start()
    {
        WaveInfoPanel = GameObject.Find("WaveInfoPanel").GetComponent<WaveInfo>();
        setupWaves();
        spawnWaves();
    }

    void spawnWaves(){

        int SpawnCounter = _EnemySpawnPoints.transform.childCount;
        //Debug.Log("PropsSP Counter: " + SpawnCounter);

        bool[] spawnStatus = new bool[SpawnCounter];
        int enemyID = 0;

        StartCoroutine(WaveInfoPanel.setWave(currentWave));
        ScoreManager.Instance.updateWaveScore(waves[currentWave].getEnemySpawnList().Length);

        for (int i = 0; i < waves[currentWave].getEnemySpawnList().Length; i++){

            do
            {
                enemyID = Random.Range(0, SpawnCounter);
            } while (spawnStatus[enemyID] == true || Vector3.Distance(_EnemySpawnPoints.transform.GetChild(enemyID).transform.position, PlayerManager.Instance.transform.position) <= dist);

            spawnStatus[enemyID] = true;

            Vector3 effecLoc = _EnemySpawnPoints.transform.GetChild(enemyID).transform.position;
            effecLoc.y = effecLoc.y + 1;
            effecLoc.z = effecLoc.z + -1;

            Instantiate(effect, effecLoc , Quaternion.identity);
            GameObject new_enemy = Instantiate(waves[currentWave].getEnemySpawnList()[i], _EnemySpawnPoints.transform.GetChild(enemyID).transform.position, Quaternion.identity);
            if (GameManager.Instance.gameData.arenaDefeated > 3)
            {
                new_enemy.GetComponent<EnemyHealth>().incHealt(25 * (GameManager.Instance.gameData.arenaDefeated - 3));
            }
            //StartCoroutine(waves[currentWave].getEnemySpawnList()[i].GetComponent<EnemyNavMeshMovement>().trigger(effect.GetComponent<ParticleSystem>().main.duration));
            //Debug.Log("distanza:" + Vector3.Distance(_EnemySpawnPoints.transform.GetChild(enemyID).transform.position, PlayerManager.Instance.transform.position));

        }

    }

    void setupWaves()
    {
        waves = new Wave[GameManager.Instance.gameData.wavesNumber];
        WaveInfoPanel.setMaxWave(GameManager.Instance.gameData.wavesNumber);
        int EnemyNumber = GameManager.Instance.gameData.wave_enemies_number * (int)Mathf.Ceil(GameManager.Instance.gameData.wavesNumber * 0.8f);
        if (EnemyNumber >= enemy_count_limit) EnemyNumber = enemy_count_limit;
        for (int i = 0; i < waves.Length; i++)
        {
            waves[i] = new Wave(EnemyNumber, 3);
            EnemyNumber = (int)Mathf.Ceil(EnemyNumber * 1.2f);
            if (EnemyNumber >= enemy_count_limit) EnemyNumber = enemy_count_limit;
            waves[i].Start();
        }
    }

    public void EnemyDeath() {

        enemyKilled++;

        if (enemyKilled >= waves[currentWave].getEnemySpawnList().Length)
        {
            GameManager.Instance.gameData.wavesCompleted++;
            if(currentWave + 1 < waves.Length)
            {
                enemyKilled = 0;
                currentWave++;
                spawnWaves();
            }
            else
            {
                endWaves();
            }
        }
    }

    void endWaves()
    {
        //Debug.Log("Waves Ended");
        AudioMenager.Instance.PlayEffect("EndWave");
        GameManager.Instance.DefeatedArena();
        StartCoroutine(WaveInfoPanel.setWave(currentWave + 1));
    }
}
