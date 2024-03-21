using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyHealth : MonoBehaviour
{

    [SerializeField] int defaultHealtPoints = 100;
    int healthPoints;
    [SerializeField] GameObject coinPrefab;
    [SerializeField] private GameObject effect;

    private void Start()
    {
        healthPoints = defaultHealtPoints;
        transform.GetComponentInChildren<HealthBar>().setMaxHealth(healthPoints);
    }

    public void takeDamage(int damageAmount)
    {
        //Debug.Log("Enemy health: " + healthPoints + " -> " + (healthPoints - damageAmount));
        healthPoints -= damageAmount;
  
        transform.GetComponentInChildren<HealthBar>().setHealth(healthPoints);

        GetComponent<EnemySimpleMovement>().setTriggered();

        if (healthPoints <= 0)
        {
            Instantiate(effect, this.transform.position, Quaternion.identity);
            AudioMenager.Instance.PlayEffect("EnemyExplosion");
            dropCoins();
            ScoreManager.Instance.moreScore(defaultHealtPoints);
            EnemyWaveSpawner.Instance.EnemyDeath();
            Destroy(this.gameObject);

        }
    }

    private void dropCoins()
    {
        int min_n_coins = defaultHealtPoints / 20;
        int variability = Mathf.CeilToInt(min_n_coins / 2);
        int n_coins = Random.Range(min_n_coins, min_n_coins + variability);

        //Debug.Log("Coins Dropped: " + n_coins);

        for(int i = 0; i < n_coins; i++)
        {
            var coin = Instantiate(coinPrefab, transform.position, Quaternion.identity);
            coin.GetComponent<CoinFollow>().dropCoins(this.transform.position);
        }
    }

    public void incHealt(int healt)
    {
        defaultHealtPoints += healt;
    }
}
