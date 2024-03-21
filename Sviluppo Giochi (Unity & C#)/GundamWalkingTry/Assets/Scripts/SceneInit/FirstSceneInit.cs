using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;

public class FirstSceneInit : MonoBehaviour
{
    [SerializeField] Transform spawnPoint;
    PauseMenuManager pauseMenu;

    private void Start()
    {
        Init();
    }

    public void Init()
    {
        if (GameManager.Instance.loadData) 
        {
            SaveManager.Instance.load();
            GameManager.Instance.loadData = false;
        } 
        PlayerManager.Instance.GetComponent<PlayerShieldManager>().reset();
        PlayerManager.Instance.GetComponent<PlayerHealthManager>().reset();
        //if(GameManager.Instance.localData == false) SaveManager.Instance.load();
        //Debug.Log("SceneInit...");
        //Debug.Log("PlayerPos: " + PlayerManager.Instance.transform.position);
        pauseMenu = GameObject.FindObjectOfType<PauseMenuManager>(true);
        pauseMenu.gameObject.SetActive(true);
        pauseMenu.gameObject.SetActive(false);
        PlayerManager.Instance.gameObject.SetActive(true);
        PlayerManager.Instance.GetComponent<Shooting>().initBulletArray();
        PlayerManager.Instance.GetComponent<CharacterController>().enabled = false;
        PlayerManager.Instance.gameObject.transform.position = spawnPoint.position;
        PlayerManager.Instance.gameObject.transform.rotation = spawnPoint.rotation;
        PlayerManager.Instance.GetComponent<CharacterController>().enabled = true;
        PlayerManager.Instance.gameObject.GetComponent<PlayerInput>().enabled = true;
        PlayerManager.Instance.gameObject.GetComponent<PlayerController>().CheckCommands();
        //Debug.Log("SceneInitialized.");
    }

}
