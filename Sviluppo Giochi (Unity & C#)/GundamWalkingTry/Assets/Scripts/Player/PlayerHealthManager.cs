using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerHealthManager : MonoBehaviour
{
    
    [SerializeField] int defaultHealth = 200;
    [SerializeField] GameObject healthBar;
    [SerializeField] float PU_effect_multiplier = 1;
    [SerializeField] int damageIgnoreProbability = 0;
    [SerializeField] int currentHealth;
    private bool died = false;

    float maxVignetteIntensity = 0.4f;

    private void Awake()
    {
        Debug.Log("PlayerHealthManager Awake");
    }

    private void loadAll() {

        HealthData h = new HealthData();

        if (h.loadData("health") != null)
        {
            h = JsonUtility.FromJson<HealthData>(h.loadData("health"));
            defaultHealth = h.defaultHealth;
            PU_effect_multiplier = h.PU_effect_multiplier;
            damageIgnoreProbability = h.damageIgnoreProbability;
            currentHealth = h.currentHealth;

        }
        else reset();
    }


    private void loadPerm() {

        HealthData h = new HealthData();

        if (h.loadData("health") != null)
        {
            h = JsonUtility.FromJson<HealthData>(h.loadData("health"));
            defaultHealth = h.defaultHealth;
            PU_effect_multiplier = h.PU_effect_multiplier;
            damageIgnoreProbability = h.damageIgnoreProbability;

        }

        reset();
    }

    public void save()
    {
        HealthData h = new HealthData();

        h.defaultHealth = defaultHealth;
        h.PU_effect_multiplier = PU_effect_multiplier;
        h.damageIgnoreProbability = damageIgnoreProbability;
        h.currentHealth = currentHealth;

        h.saveData("health");
    }

    private void Start()
    {
        
        healthBar = HUDManager.Instance.gameObject.transform.Find("Health Bar").gameObject;

        //if (GameManager.Instance.gameData.scene == "Checkpoints") loadAll();
        //else loadPerm();
    }

    public void load()
    {
        if (GameManager.Instance.gameData.scene == "Corridoio #1") loadAll();
        else loadPerm();
        healthBar.GetComponent<HealthBar>().setMaxHealth(defaultHealth);
        healthBar.GetComponent<HealthBar>().setHealth(currentHealth);
    }

    public void takeDamage(int damage)
    {
        if(damageIgnoreProbability != 0)
        {
            int extractedNumber = Random.Range(0, 100);
            if (extractedNumber < damageIgnoreProbability) return;
        }

        currentHealth -= damage;
        ScoreManager.Instance.lessScore(damage);

        healthBar.GetComponent<HealthBar>().setHealth(currentHealth);
        if(currentHealth <= defaultHealth / 2)
        {
            double vignette_intensity = maxVignetteIntensity - ((((float)currentHealth)/((float)(defaultHealth+1)/2f))*maxVignetteIntensity);
            //Debug.Log(maxVignetteIntensity + " - (" + currentHealth + " / " + defaultHealth / 2 + ") * 0.4 = " + vignette_intensity);
            VolumeManager.Instance.setVignetteIntensity((float)vignette_intensity);
            if(currentHealth <= 0)
            {
                Die();
            }
        }
    }

    public void addMaxHealth(int health)
    {
        defaultHealth += health;
        healthBar.GetComponent<HealthBar>().setMaxHealth(defaultHealth);

        save();
    }

    public void heal(int health)
    {
        currentHealth += Mathf.CeilToInt(health * PU_effect_multiplier);
        if (currentHealth > defaultHealth) currentHealth = defaultHealth;

        double vignette_intensity = maxVignetteIntensity - ((((float)currentHealth) / ((float)(defaultHealth + 1) / 2f)) * maxVignetteIntensity);
        //Debug.Log(maxVignetteIntensity + " - (" + currentHealth + " / " + defaultHealth / 2 + ") * 0.4 = " + vignette_intensity);
        VolumeManager.Instance.setVignetteIntensity((float)vignette_intensity);

        healthBar.GetComponent<HealthBar>().setHealth(currentHealth);

        //save();
    }

    public void setPUMultiplier(float multiplier){ this.PU_effect_multiplier = multiplier; }
    public void setDIProbability(int prob) { damageIgnoreProbability = prob; }

    public int getDefaultHealth() {
        return defaultHealth;
    }
    private void Die()
    {
        if (!died)
        {
            this.gameObject.GetComponent<Shooting>().resetDamage();
            this.gameObject.GetComponent<PlayerShieldManager>().resetMaxShield();
            GameManager.Instance.runRestart();
            died = true;
        }
    }

    public void reset()
    {
        currentHealth = defaultHealth;
        healthBar.GetComponent<HealthBar>().setHealth(currentHealth);
        died = false;
    }
}
