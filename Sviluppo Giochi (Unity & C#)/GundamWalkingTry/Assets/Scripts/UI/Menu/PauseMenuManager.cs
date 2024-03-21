using System.Collections;
using System.Collections.Generic;
using UnityEngine.SceneManagement;
using UnityEngine;
using UnityEngine.InputSystem;

public class PauseMenuManager : MonoBehaviour
{
    [SerializeField] private static PauseMenuManager _instance;

    public bool active => false;

    public static PauseMenuManager Instance
    {
        get
        {
            if (_instance == null)
            {
                _instance = GameObject.FindObjectOfType<PauseMenuManager>(true);
                if (_instance == null) Debug.LogError("No PauseMenu in scene");
            }
            return _instance;
        }
    }

    private void Awake()
    {
        if (_instance == null)
        {
            _instance = this;
            //Debug.Log("SetInstance");
            GameObject.DontDestroyOnLoad(this.gameObject);
        }
        else
        {
            GameObject.Destroy(this.gameObject);
        }
    }

    public void Pause()
    {
        Debug.Log("Pause");
        WindowManager.Instance.setDiplayEmpty(false);
        this.gameObject.SetActive(true);
        Time.timeScale = 0f;
        PlayerManager.Instance.GetComponent<PlayerInput>().enabled = false;
    }

    public void Resume()
    {
        Debug.Log("Resume");
        WindowManager.Instance.setDiplayEmpty(true);
        this.gameObject.SetActive(false);
        Time.timeScale = 1f;
        PlayerManager.Instance.GetComponent<PlayerInput>().enabled = true;
        PlayerManager.Instance.GetComponent<PlayerController>().CheckCommands();
    }

    public void goMenu()
    {
        SceneManager.LoadScene("Menu");
        Time.timeScale = 1f;
        PlayerManager.Instance.StopAllCoroutines();
        PlayerManager.Instance.gameObject.SetActive(false);
        this.gameObject.SetActive(false);
        WindowManager.Instance.setDiplayEmpty(false);
    }


    public void Escape()
    {

        //Debug.Log(WindowManager.Instance.canShow() + " " + this.gameObject.activeSelf + " " + context.started);

        if (WindowManager.Instance.canShow() && this.gameObject.activeSelf == false)
        {
            Pause();
        }
        else if (this.gameObject.activeSelf == true) {
            Resume();
        }

    }
}
