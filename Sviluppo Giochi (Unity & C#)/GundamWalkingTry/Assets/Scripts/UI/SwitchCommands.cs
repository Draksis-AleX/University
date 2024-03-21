using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;

public class SwitchCommands : MonoBehaviour
{
    [SerializeField] GameObject SelectedWASD;
    [SerializeField] GameObject SelectedArrows;

    private void OnEnable()
    {
        DisplaySelected();
    }

    public void SwitchArrows()
    {
        GameManager.Instance.gameData.CommandsArrow = true;
        GameManager.Instance.save();
        DisplaySelected();
    }

    public void SwitchWASD()
    {
        GameManager.Instance.gameData.CommandsArrow = false;
        GameManager.Instance.save();
        DisplaySelected();
    }

    private void DisplaySelected()
    {
        if (GameManager.Instance.gameData.CommandsArrow == true)
        {
            SelectedArrows.SetActive(true);
            SelectedWASD.SetActive(false);
        }
        else
        {
            SelectedArrows.SetActive(false);
            SelectedWASD.SetActive(true);
        }
    }
}
