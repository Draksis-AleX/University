using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class SaveUI : MonoBehaviour
{
    [SerializeField] CanvasGroup mygroup;

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
            if (mygroup.alpha < 1)
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

    public void Show()
    {
        StartCoroutine(showSaving());
    }

    private IEnumerator showSaving()
    {
        ShowUI();
        yield return new WaitForSeconds(3);
        HideUI();
    }

}
