using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;
using UnityEngine.SceneManagement;

public class Shooting : MonoBehaviour
{
    [SerializeField] Transform firePointSX;
    [SerializeField] Transform firePointDX;
    Transform firePoint;
    [SerializeField] GameObject bulletPrefab;

    [SerializeField] GameObject[] bulletList;
    [SerializeField] int bulletLength;
    int bulletCounter = 0;

    [SerializeField] float bulletForce = 20f;
    [SerializeField] float coolDown = 1;
    [SerializeField] float despawnTime = 5;
    bool canShoot = true;

    [SerializeField] int playerDamage = 0;
    [SerializeField] int playerCurrentDamage = 50;
    [SerializeField] float vampirismPercentage = 0f;

    

    private void Awake()
    {
        firePoint = firePointSX;
        initBulletArray();
    }

    private void OnEnable()
    {
        //Debug.Log("InitBulletArray");
        initBulletArray();
    }

    public void Shoot(InputAction.CallbackContext context)
    {
        if (context.started && canShoot && this.GetComponent<PlayerInput>().actions["Aiming"].IsPressed())
        {
            //Debug.Log("Shoot");
            AudioMenager.Instance.PlayEffect("Blaster");
            for (int i = bulletCounter; i < bulletLength; i++)
            {
                if (!bulletList[i].activeInHierarchy)
                {
                    bulletList[i].transform.Spawn(firePoint);
                    Rigidbody rb = bulletList[i].GetComponent<Rigidbody>();
                    rb.AddForce(firePoint.up * bulletForce, ForceMode.Impulse);
                    StartCoroutine(despawnCoroutine(i));
                    bulletCounter = i + 1;
                    if (bulletCounter >= bulletLength) bulletCounter = 0;
                    switchFirePoint();
                    break;
                }
            }
            StartCoroutine("coolDownCoroutine");
        }
    }

    public void initBulletArray()
    {
        bulletList = new GameObject[bulletLength];
        for (int i = 0; i < bulletLength; i++)
        {
            bulletList[i] = Instantiate(bulletPrefab, firePoint.position, firePoint.rotation);
            bulletList[i].SetActive(false);
        }
        canShoot = true;
    }

    public IEnumerator despawnCoroutine(int i)
    {
        yield return new WaitForSeconds(despawnTime);
        if (bulletList[i].activeInHierarchy)
        {
            bulletReset(i);
        }
    }

    public IEnumerator coolDownCoroutine()
    {
        canShoot = false;
        yield return new WaitForSeconds(coolDown);
        canShoot = true;      
    }

    void bulletReset(int i)
    {
        bulletList[i].SetActive(false);
        bulletList[i].GetComponent<Rigidbody>().velocity = Vector3.zero;
        bulletList[i].GetComponent<Rigidbody>().angularVelocity = Vector3.zero;
    }

    void switchFirePoint()
    {
        if (firePoint == firePointSX)
            firePoint = firePointDX;
        else firePoint = firePointSX;
    }

    public void addDamage(int amount) { this.playerDamage += amount; save(); }
    public void addCurrentDamage(int amount) { this.playerCurrentDamage += amount; save();  }

    public int getDamage() { return this.playerCurrentDamage; }

    public void reduceCooldown(float percentage){ coolDown -= coolDown * percentage; save(); }

    public float getVampirismPercentage() { return this.vampirismPercentage; }

    public void addVampirismPercentage(float percentage) { this.vampirismPercentage += percentage; save(); }

    private void loadAll()
    {

        BulletData d = new BulletData();

        if (d.loadData("bullet") != null)
        {
          d = JsonUtility.FromJson<BulletData>(d.loadData("bullet"));

          bulletForce = d.bulletForce;
          coolDown = d.coolDown;

          playerDamage = d.playerDamage;
          playerCurrentDamage = d.playerCurrentDamage;
          vampirismPercentage = d.vampirismPercentage;

        }
        else playerCurrentDamage = playerDamage;
    }


    private void loadPerm()
    {
        BulletData d = new BulletData();

        if (d.loadData("bullet") != null)
        {
            d = JsonUtility.FromJson<BulletData>(d.loadData("bullet"));

            bulletForce = d.bulletForce;
            coolDown = d.coolDown;
            playerDamage = d.playerDamage;
            vampirismPercentage = d.vampirismPercentage;

        }
        playerCurrentDamage = playerDamage;

    }
    public void load()
    {
        if (GameManager.Instance.gameData.scene == "Corridoio #1") loadAll();
        else loadPerm();
    }


    public void save()
    {
        BulletData d = new BulletData();

        d.bulletForce = bulletForce;
        d.coolDown = coolDown;

        d.playerDamage = playerDamage;
        d.playerCurrentDamage = playerCurrentDamage;
        d.vampirismPercentage = vampirismPercentage;

        d.saveData("bullet");
    }

    public void resetDamage() { playerCurrentDamage = playerDamage;  }
}
