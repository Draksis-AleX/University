using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PowerUpManager : MonoBehaviour
{
    [SerializeField] GameObject armorPU;
    [SerializeField] GameObject healPU;
    [SerializeField] GameObject bulletPU;

    [SerializeField] Material offMat;


    private static PowerUpManager _instance;

    public static PowerUpManager Instance
    {
        get
        {
            if (_instance == null)
            {
                _instance = GameObject.FindObjectOfType<PowerUpManager>();
                if (_instance == null) Debug.LogError("No Player in scene");
            }
            return _instance;
        }
    }

    private void Awake()
    {
        if (_instance == null)
        {
            _instance = this;
            //GameObject.DontDestroyOnLoad(this.gameObject);
        }
        else
        {
            GameObject.Destroy(this.gameObject);
        }
    }


    public void LockPowerUp() {

        SetOffPowerUp(armorPU); //armorPU.SetActive(false);
        SetOffPowerUp(healPU); //healPU.SetActive(false);
        SetOffPowerUp(bulletPU); //bulletPU.SetActive(false);

    }

    private void SetOffPowerUp(GameObject powerUp) {

        powerUp.GetComponent<Animator>().enabled = false;
        powerUp.GetComponent<Renderer>().material = offMat;
        powerUp.layer = 0;
    }
}
