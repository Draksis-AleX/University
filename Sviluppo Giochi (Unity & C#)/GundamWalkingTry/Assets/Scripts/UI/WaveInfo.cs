using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using UnityEngine.SceneManagement;

public class WaveInfo : MonoBehaviour
{
    [SerializeField] TextMeshProUGUI text;
    [SerializeField] CanvasGroup mygroup;
    int wave, maxWave;

    [SerializeField] private bool fadeIn = false;
    [SerializeField] private bool fadeOut = false;

    private void Start()
    {
        SceneManager.activeSceneChanged += ChangedActiveScene;
    }

    void ChangedActiveScene(Scene current, Scene next)
    {
        fadeIn = false;
        fadeOut = true;
    }

    public void ShowUI()
    {
        fadeIn = true;
    }

    public void HideUI()
    {
        fadeOut = true;
    }

    private void Update()
    {
        if (fadeIn)
        {
            if(mygroup.alpha < 1)
            {
                mygroup.alpha += Time.deltaTime;
                if (mygroup.alpha >= 1) fadeIn = false;
            }
        }

        if (fadeOut)
        {
            if (mygroup.alpha >= 0)
            {
                mygroup.alpha -= Time.deltaTime;
                if (mygroup.alpha <= 0) fadeOut = false;
            }
        }
    }

    public IEnumerator setWave(int wave)
    {
        text.color = Color.white;
        this.wave = wave;
        if(this.wave == maxWave)
        {
            text.color = Color.green;
            text.text = wave + " Waves Completed";
        }
        else text.text = "Wave " + (this.wave + 1) + " / " + this.maxWave;
        ShowUI();
        yield return new WaitForSeconds(3);
        HideUI();
    }

    public void setMaxWave(int wave)
    {
        this.maxWave = wave;
    }


}
