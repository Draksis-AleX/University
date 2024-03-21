using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;
public abstract class Window : MonoBehaviour
{

    public void Update() {

        if (Keyboard.current.escapeKey.wasPressedThisFrame && this.gameObject.activeSelf == true)
        {
            this.gameObject.SetActive(false);
            other();
            //TimeStop(true);
            //Debug.Log("pause update dentro");
        }

    }


    private void OnEnable()
    {
        AudioMenager.Instance.PlayEffect("OpenUI");
        WindowManager.Instance.setDiplayEmpty(false);
        PlayerManager.Instance.GetComponent<PlayerInput>().enabled = false;
        Time.timeScale = 0f;
    }


    private void OnDisable()
    {
        WindowManager.Instance.setDiplayEmpty(true);
        Time.timeScale = 1f;
        PlayerManager.Instance.GetComponent<PlayerInput>().enabled = true;
        PlayerManager.Instance.GetComponent<PlayerController>().CheckCommands();
    }

    abstract public void other();

    public void TimeStop(bool stopped) {
        if(stopped) Time.timeScale = 0f;
        else Time.timeScale = 1f;
    }
   
}
