using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerShieldManager : MonoBehaviour
{

    [SerializeField] int maxShield = 50;
    [SerializeField] int bonusShield = 0;
    [SerializeField] int currentShield;
    [SerializeField] float shieldCooldownTime = 5f;
    [SerializeField] float regenerationTime = 1f;
    [SerializeField] GameObject shieldBar;
    Coroutine latestShieldCooldown;
    [SerializeField] bool isRegenerating = false;

    private void Awake()
    {
        Debug.Log("PlayerShieldManager Awake");
    }

    private void loadAll()
    {

        ShieldData d = new ShieldData();

        if (d.loadData("shield") != null)
        {
            d = JsonUtility.FromJson<ShieldData>(d.loadData("shield"));

            maxShield  = d.maxShield;
            bonusShield = d.bonusShield;
            shieldCooldownTime =  d.shieldCooldownTime;
            regenerationTime =  d.regenerationTime;

        }
        maxShield += bonusShield;
        reset();
    }


    private void loadPerm()
    {
        ShieldData d = new ShieldData();

        if (d.loadData("shield") != null)
        {
            d = JsonUtility.FromJson<ShieldData>(d.loadData("shield"));

            maxShield = d.maxShield;
            shieldCooldownTime = d.shieldCooldownTime;
            regenerationTime = d.regenerationTime;

        }
        bonusShield = 0;
        reset();

    }

    public void load()
    {
        if (GameManager.Instance.gameData.scene == "Corridoio #1") loadAll();
        else loadPerm();
        shieldBar.GetComponent<ShieldBar>().setMaxShield(maxShield);
        shieldBar.GetComponent<ShieldBar>().setShield(maxShield);
    }

    public void save()
    {
        ShieldData d = new ShieldData();

        d.maxShield = maxShield - bonusShield;
        d.bonusShield = bonusShield;
        d.shieldCooldownTime = shieldCooldownTime;
        d.regenerationTime = regenerationTime;

        d.saveData("shield");
    }

    private void Start()
    {
        shieldBar = HUDManager.Instance.gameObject.transform.Find("Shield Bar").gameObject;
        //if (GameManager.Instance.gameData.scene == "Checkpoints") loadAll();
        //else loadPerm();
    }

    public void reset()
    {
        currentShield = maxShield;
        shieldBar.GetComponent<ShieldBar>().setShield(maxShield);
        Debug.Log("ShieldReset");
    }

    public void resetMaxShield() { maxShield -= bonusShield; shieldBar.GetComponent<ShieldBar>().setMaxShield(maxShield); }

    public void addMaxShield(int amount)
    {
        maxShield += amount;

        shieldBar.GetComponent<ShieldBar>().setMaxShield(maxShield);
        if (latestShieldCooldown != null) StopCoroutine(latestShieldCooldown);
        latestShieldCooldown = StartCoroutine(shieldCooldown());
        save();
    }

    public void addBonusShield(int amount)
    {
        bonusShield += amount;
        maxShield += bonusShield;

        shieldBar.GetComponent<ShieldBar>().setMaxShield(maxShield);
        if (latestShieldCooldown != null) StopCoroutine(latestShieldCooldown);
        latestShieldCooldown = StartCoroutine(shieldCooldown());
        save();
    }

    public void takeDamage(int damage)
    {
        if (currentShield > 0)
        {
            currentShield -= damage;
            if (currentShield <= 0)
            {
                if (currentShield < 0)
                {
                    this.GetComponent<PlayerHealthManager>().takeDamage(Mathf.Abs(currentShield));
                    currentShield = 0;
                }
            }
        }
        else
        {
            this.GetComponent<PlayerHealthManager>().takeDamage(damage);
        }
        shieldBar.GetComponent<ShieldBar>().setShield(currentShield);
        if (latestShieldCooldown != null) StopCoroutine(latestShieldCooldown);
        latestShieldCooldown = StartCoroutine(shieldCooldown());
    }

    //============================== SKILLS PARAMETERS ======================================

    public void reduceRegenerationTime(float percentage)
    {
        regenerationTime = regenerationTime - (regenerationTime * percentage);
        save();
    }

    public void reduceCooldownTime(float percentage)
    {
        shieldCooldownTime = shieldCooldownTime - (shieldCooldownTime * percentage);
        save();
    }

    //============================ REGEN COROUTINES ===========================================

    public IEnumerator shieldCooldown()
    {
        isRegenerating = false;
        //Debug.Log("Started Shield Cooldown");
        yield return new WaitForSecondsRealtime(shieldCooldownTime);
        //Debug.Log("Ended Shield Cooldown");
        isRegenerating = true;
        StartCoroutine(regenerateShield());
    }

    public IEnumerator regenerateShield()
    {
        if (isRegenerating)
        {
            currentShield += 5;
            shieldBar.GetComponent<ShieldBar>().setShield(currentShield);
            if (currentShield > maxShield) currentShield = maxShield;
            yield return new WaitForSecondsRealtime(regenerationTime);
            if (currentShield < maxShield) StartCoroutine(regenerateShield());
        }
        else yield return null;
    }

}
