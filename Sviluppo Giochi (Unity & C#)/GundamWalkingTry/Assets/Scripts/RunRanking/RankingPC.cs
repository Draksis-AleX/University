using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RankingPC : MonoBehaviour, IInteractable
{
    public string InteractionPrompt => "Press E";
    [SerializeField] protected GameObject panel;
    [SerializeField] protected GameObject blurPanel;

    public void Action()
    {
        OpenRankingPanel();
    }

    public void OpenRankingPanel()
    {
        panel.SetActive(true);
        blurPanel.GetComponent<CanvasGroup>().alpha = 1;
    }

    public bool Interact(Interactor interactor)
    {
        interactor.OpenRankingPanel(this);
        return true;
    }
}
