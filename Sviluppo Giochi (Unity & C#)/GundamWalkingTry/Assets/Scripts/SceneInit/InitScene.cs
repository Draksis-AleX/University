using System.Collections;
using UnityEngine.SceneManagement;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;
using UnityEngine.AI;

public class InitScene : MonoBehaviour
{

    [SerializeField] protected Animator upperDoor;
    [SerializeField] protected Animator lowerDoor;
    WaveInfo waveInfo;
    [SerializeField] GameObject pauseMenu;

    public void Start()
    {
        //Debug.Log("ChangeSceneCoroutine::Start");
        StartCoroutine("Init");
        ResetShield();
        if(GameManager.Instance.localData == false) SaveManager.Instance.load();
        if (SceneManager.GetActiveScene().name == "Magazzino") GameManager.Instance.gameData.tookPowerUp = true;
    }

    public IEnumerator Init()
    {
        //Debug.Log("Started Init Coroutine");
        if (pauseMenu != null)
        {
            pauseMenu.gameObject.SetActive(true);
            pauseMenu.gameObject.SetActive(false);
        }
        AudioMenager.Instance.PlayEffect("CloseDoor");
        upperDoor.Play("UpperClose");
        lowerDoor.Play("LowerClose");
        PlayerManager.Instance.gameObject.SetActive(true);
        yield return new WaitForSeconds(upperDoor.runtimeAnimatorController.animationClips[1].length);
        PlayerManager.Instance.gameObject.GetComponent<PlayerInput>().enabled = true;
        PlayerManager.Instance.gameObject.GetComponent<PlayerController>().CheckCommands();
        //Debug.Log("Ended Init Coroutine");
    }

    void ResetShield()
    {
        PlayerManager.Instance.GetComponent<PlayerShieldManager>().reset();
    }

}
