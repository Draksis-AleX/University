using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using TMPro;

public class PlayerDeath : Window
{
    [SerializeField] GameObject blur;

    public void Die()
    {
        GameManager.Instance.runRestart();
    }

    public void ShowUI(int score, float run_time)
    {
        this.gameObject.SetActive(true);
        blur.GetComponent<CanvasGroup>().alpha = 1;
        HUDManager.Instance.gameObject.SetActive(false);
        this.gameObject.transform.GetChild(0).GetChild(0).Find("RunInfo").Find("Values").Find("Score").GetComponent<TextMeshProUGUI>().text = score.ToString("000000000");
        this.gameObject.transform.GetChild(0).GetChild(0).Find("RunInfo").Find("Values").Find("TimePlayed").GetComponent<TextMeshProUGUI>().text = FormatTime(run_time); 
    }

    string FormatTime(float time)
    {
        int minutes = (int)time / 60;
        int seconds = (int)time - 60 * minutes;
        return string.Format("{0:00}:{1:00}", minutes, seconds);
    }

    public void Restart()
    {
        HUDManager.Instance.gameObject.SetActive(true);
        blur.GetComponent<CanvasGroup>().alpha = 0;
        this.gameObject.SetActive(false);
    }

    public void Quit()
    {
        HUDManager.Instance.gameObject.SetActive(true);
        blur.GetComponent<CanvasGroup>().alpha = 0;
        SceneManager.LoadScene("Menu");
        PlayerManager.Instance.StopAllCoroutines();
        PlayerManager.Instance.gameObject.SetActive(false);
        this.gameObject.SetActive(false);
        WindowManager.Instance.setDiplayEmpty(false);
    }

    public override void other()
    {
        blur.GetComponent<CanvasGroup>().alpha = 0;
    }
}
